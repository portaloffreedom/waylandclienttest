#ifndef WL_BUFFER_H
#define WL_BUFFER_H

#include <wayland-client.h>
#include <cassert>

namespace wl {

/**
 * @todo write docs
 */
class Buffer
{
public:
    /**
     * Default constructor
     */
    Buffer(wl_buffer* c_pointer, void* data, int width, int height, wl_shm_format format);
    Buffer(const Buffer&) = delete;

    /**
     * Destructor
     */
    ~Buffer();

    size_t size_of_pixel() const;

    template<typename T>
    void write_all(T cell_value = 0xffffff) {
        assert(sizeof(T) == size_of_pixel()/8);
        T* pixel = static_cast<T*>(data);
        for(int i=0; i<width*height; i++) {
            *pixel++ = cell_value;
        }
    }

    inline wl_buffer* c_repr() const { return raw; }

private:
    wl_buffer *raw = nullptr;
    void *data = nullptr;
    const int width, height;
    wl_shm_format format;
};

}

#endif // WL_BUFFER_H
