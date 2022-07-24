#include "sharedmemory.h"
#include "buffer.h"
#include "wl_exception.h"
#include <sys/mman.h>
#include <fcntl.h>
// #include <cstdio>
// #include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace wl;

extern "C" void static_shm_listener_format(void *data, wl_shm *wl_shm, uint32_t format)
{
    static_cast<wl::SharedMemory*>(data)
        ->_on_format(
            static_cast<wl_shm_format>(format)
        );
}

static int
set_cloexec_or_close(int fd)
{
        long flags;

        if (fd == -1)
                return -1;

        flags = fcntl(fd, F_GETFD);
        if (flags == -1)
                goto err;

        if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1)
                goto err;

        return fd;

err:
        close(fd);
        return -1;
}

#include <iostream>

static int
create_tmpfile_cloexec(char *tmpname)
{
        int fd = -1;

// #ifdef HAVE_MKOSTEMP
        fd = mkostemp(tmpname, O_CLOEXEC);

        if (fd >= 0)
                unlink(tmpname);
// #else
//         fd = mkstemp(tmpname);
//         if (fd >= 0) {
//                 fd = set_cloexec_or_close(fd);
//                 unlink(tmpname);
//         }
// #endif
        if (fd < 0) {
            std::cerr << "ERROR!!! with mkostemp" << std::endl
                      << " attempting to create temporary file at " << tmpname << std::endl
                      << " errno=" << errno << std::endl;
            switch(errno) {
                case EEXIST:
                    std::cerr << "Could not create a unique temporary filename. Now the contents of template are undefined." << std::endl;
                    break;
                case EINVAL:
                    std::cerr << "The last six characters of template were not XXXXXX; now template is unchanged." << std::endl;
                    break;
            }
        }

        return fd;
}

/*
 * Create a new, unique, anonymous file of the given size, and
 * return the file descriptor for it. The file descriptor is set
 * CLOEXEC. The file is immediately suitable for mmap()'ing
 * the given size at offset zero.
 *
 * The file should not have a permanent backing store like a disk,
 * but may have if XDG_RUNTIME_DIR is not properly implemented in OS.
 *
 * The file name is deleted from the file system.
 *
 * The file is suitable for buffer sharing between processes by
 * transmitting the file descriptor over Unix sockets using the
 * SCM_RIGHTS methods.
 */
int os_create_anonymous_file(off_t size)
{
        static const char template_name[] = "/waylandclient-shared-memory-XXXXXX";
        const char *path;
        char *name;
        int fd;

        path = getenv("XDG_RUNTIME_DIR");
        if (path == nullptr) {
            throw wl::exception("XDG_RUNTIME_DIR env var not set");
        }

        name = static_cast<char*>(
            malloc(std::strlen(path) + sizeof(template_name))
        );
        if (name == nullptr)
            throw wl::exception("error allocating memory");
        std::strcpy(name, path);
        std::strcat(name, template_name);

        fd = create_tmpfile_cloexec(name);

        free(name);

        if (fd < 0)
            throw wl::exception("fd < 0");

        if (ftruncate(fd, size) < 0) {
            close(fd);
            throw wl::exception("error truncating file descriptor");
        }

        return fd;
}

SharedMemory::SharedMemory(wl_shm* raw_pointer)
    : raw(raw_pointer)
{
    listener.format = &static_shm_listener_format;
    wl_shm_add_listener(raw, &this->listener, this);
}

SharedMemory::~SharedMemory()
{
    wl_shm_destroy(raw);
}

void wl::SharedMemory::_on_format(wl_shm_format format)
{
    this->supported_formats.emplace(format);

    const char *s;
    switch (format) {
    case WL_SHM_FORMAT_ARGB8888: s = "ARGB8888"; break;
    case WL_SHM_FORMAT_XRGB8888: s = "XRGB8888"; break;
    case WL_SHM_FORMAT_RGB565: s = "RGB565"; break;
    default: s = "other format"; break;
    }
    fprintf(stderr, "Possible shmem format %s\n", s);
}

wl::Buffer wl::SharedMemory::create_buffer(int width, int height, wl_shm_format format)
{
    if (supported_formats.count(format) <= 0) {
        throw wl::exception("Cannot create buffer with unsupported format");
    }
    int stride = width*4; // 4 bytes per pixel
    int size = stride*height;

    int fd = os_create_anonymous_file(size);
    if (fd < 0) {
        throw wl::exception("creating a buffer failed");
    }

    void* shm_data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_data == MAP_FAILED) {
        close(fd);
        throw wl::exception("mmap failed");
    }

    wl_shm_pool *pool = wl_shm_create_pool(raw, fd, size);
    wl_buffer *c_buf = wl_shm_pool_create_buffer(pool, 0, width, height, stride, format);

    wl_shm_pool_destroy(pool);
    return wl::Buffer(c_buf, shm_data, width, height, format);
}

