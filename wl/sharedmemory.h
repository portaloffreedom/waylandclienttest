#ifndef WL_SHAREDMEMORY_H
#define WL_SHAREDMEMORY_H

#include <wayland-client.h>
#include <set>

namespace wl {

class Buffer;

/**
 * @todo write docs
 */
class SharedMemory
{
public:
    /**
     * Default constructor
     */
    SharedMemory(wl_shm* raw_pointer);
    SharedMemory(const SharedMemory&) = delete;

    /**
     * Destructor
     */
    ~SharedMemory();

    void _on_format(wl_shm_format format);

    wl::Buffer create_buffer(int width, int height, wl_shm_format format = WL_SHM_FORMAT_XRGB8888);

private:
    wl_shm* raw = nullptr;
    wl_shm_listener listener;
    std::set<wl_shm_format> supported_formats;
};

}

#endif // WL_SHAREDMEMORY_H
