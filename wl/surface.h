#ifndef WL_SURFACE_H
#define WL_SURFACE_H

#include <wayland-client.h>
#include <functional>

namespace wl {

class Compositor;
class Buffer;

/**
 * @todo write docs
 */
class Surface
{
public:
    Surface(const Surface&) = delete;
    ~Surface();

    wl_surface* operator*() { return raw_surface; }

    void attach(const wl::Buffer &buffer);
    void commit();
    void damage(int x, int y, int width, int height);

    void request_redraw();
    void redraw();

    void _on_enter(wl_output *output);
    void _on_leave(wl_output *output);
    void _on_redraw(wl_callback *wl_callback, uint32_t time);

    std::function<void(Surface *surface)> on_redraw;

private:
    Surface(wl_surface* raw_surface);

private:
    wl_surface *raw_surface = nullptr;
    wl_callback *frame_callback = nullptr;
    wl_surface_listener listener;
    wl_callback_listener frame_listener;

    friend class wl::Compositor;
};

}

#endif // WL_SURFACE_H
