#include "surface.h"
#include "buffer.h"
#include "wl_exception.h"
#include <iostream>

using namespace wl;

extern "C" void _static_on_redraw(void *data,
                       wl_callback *wl_callback,
                       uint32_t time)
{
    static_cast<Surface*>(data)->_on_redraw(wl_callback, time);
}

extern "C" void _static_on_enter(void *data,
                      wl_surface *wl_surface,
                      wl_output *output)
{
    std::clog << "enter" << std::endl;
    static_cast<Surface*>(data)->_on_enter(output);
}

extern "C" void _static_on_leave(void *data,
                      wl_surface *wl_surface,
                      wl_output *output)
{
    std::clog << "leave " << std::endl;
    static_cast<Surface*>(data)->_on_leave(output);
}

Surface::Surface(wl_surface* raw_surface)
    : raw_surface(raw_surface)
{
    listener.enter = &_static_on_enter;
    listener.leave = &_static_on_leave;
    frame_listener.done = &_static_on_redraw;
    wl_surface_add_listener(raw_surface, &listener, this);

    std::cout << "listener.enter=" << (void*)listener.enter << std::endl;
    std::cout << "listener.leave=" << (void*)listener.leave << std::endl;
    std::cout << "frame_listener.done=" << (void*)frame_listener.done << std::endl;
}

Surface::~Surface()
{
    if (frame_callback != nullptr)
        wl_callback_destroy(frame_callback);
    wl_surface_destroy(raw_surface);
}

void wl::Surface::attach(const wl::Buffer& buffer)
{
    wl_surface_attach(raw_surface, buffer.c_repr(), 0, 0);
}

void wl::Surface::commit()
{
    wl_surface_commit(raw_surface);
}

void wl::Surface::damage( int x, int y, int width, int height )
{
    wl_surface_damage(raw_surface, x, y, width, height);
}

void wl::Surface::request_redraw()
{
    if (frame_callback != nullptr) {
        std::clog << "Warning! previous frame callback not cleared" << std::endl;
    }
    frame_callback = wl::expect_not_null(wl_surface_frame(raw_surface), "Could not request surface frame callback");
    wl_callback_add_listener(frame_callback, &this->frame_listener, this);
}

void wl::Surface::redraw()
{
    _on_redraw(nullptr, 0);
}

void wl::Surface::_on_redraw(wl_callback *wl_callback, uint32_t time)
{
    if(frame_callback != nullptr) {
        wl_callback_destroy(frame_callback);
        frame_callback = nullptr;
    }
    if (on_redraw)
        on_redraw(this);
}

void wl::Surface::_on_enter(wl_output* output)
{

}

void wl::Surface::_on_leave(wl_output* output)
{

}


