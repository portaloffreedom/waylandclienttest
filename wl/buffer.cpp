#include "buffer.h"

using namespace wl;

Buffer::Buffer(wl_buffer* c_pointer, void* data, int width, int height, wl_shm_format format)
    : raw(c_pointer)
    , data(data)
    , width(width)
    , height(height)
    , format(format)
{}

Buffer::~Buffer()
{
    wl_buffer_destroy(raw);
}

size_t wl::Buffer::size_of_pixel() const
{
    switch(format) {
        case WL_SHM_FORMAT_ARGB8888:
        case WL_SHM_FORMAT_XRGB8888:
            return 32;
        case WL_SHM_FORMAT_C8:
        case WL_SHM_FORMAT_RGB332:
        case WL_SHM_FORMAT_BGR233:
            return 8;
        case WL_SHM_FORMAT_XRGB4444:
        case WL_SHM_FORMAT_XBGR4444:
        case WL_SHM_FORMAT_RGBX4444:
        case WL_SHM_FORMAT_BGRX4444:
        case WL_SHM_FORMAT_ARGB4444:
        case WL_SHM_FORMAT_ABGR4444:
        case WL_SHM_FORMAT_RGBA4444:
        case WL_SHM_FORMAT_BGRA4444:
        case WL_SHM_FORMAT_XRGB1555:
        case WL_SHM_FORMAT_XBGR1555:
        case WL_SHM_FORMAT_RGBX5551:
        case WL_SHM_FORMAT_BGRX5551:
        case WL_SHM_FORMAT_ARGB1555:
        case WL_SHM_FORMAT_ABGR1555:
        case WL_SHM_FORMAT_RGBA5551:
        case WL_SHM_FORMAT_BGRA5551:
        case WL_SHM_FORMAT_RGB565:
            return 16;
        case WL_SHM_FORMAT_RGB888:
        case WL_SHM_FORMAT_BGR888:
            return 24;
        case WL_SHM_FORMAT_XBGR8888:
        case WL_SHM_FORMAT_RGBX8888:
        case WL_SHM_FORMAT_BGRX8888:
        case WL_SHM_FORMAT_ABGR8888:
        case WL_SHM_FORMAT_RGBA8888:
        case WL_SHM_FORMAT_BGRA8888:
        case WL_SHM_FORMAT_XRGB2101010:
        case WL_SHM_FORMAT_XBGR2101010:
        case WL_SHM_FORMAT_RGBX1010102:
        case WL_SHM_FORMAT_BGRX1010102:
        case WL_SHM_FORMAT_ARGB2101010:
        case WL_SHM_FORMAT_ABGR2101010:
        case WL_SHM_FORMAT_RGBA1010102:
        case WL_SHM_FORMAT_BGRA1010102:
            return 32;
        // there are other formats that I don't use now, can fill up later ;)
        default:
            assert(false);
    }

}

