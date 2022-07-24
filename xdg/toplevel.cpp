#include "toplevel.h"

#include "xdg-shell-client-protocol.h"

using namespace XDG;

void static_close(void *data, xdg_toplevel *xdg_toplevel)
{
    static_cast<XDG::TopLevel*>(data)->_close();
}

void static_configure(void *data,
                      xdg_toplevel *xdg_toplevel,
                      int32_t width,
                      int32_t height,
                      wl_array *states)
{
    static_cast<XDG::TopLevel*>(data)->_configure(width, height, states);
}

void static_configure_bounds(void *data,
                             xdg_toplevel *xdg_toplevel,
                             int32_t width,
                             int32_t height)
{
    static_cast<XDG::TopLevel*>(data)->_configure_bounds(width, height);
}

void XDG::TopLevel::_close()
{
    if (on_close)
        on_close(*this);
}

void XDG::TopLevel::_configure(int32_t width, int32_t height, wl_array* states)
{
}

void XDG::TopLevel::_configure_bounds(int32_t width, int32_t height)
{
}

TopLevel::TopLevel(xdg_toplevel *raw)
    : raw(raw)
{
    listener.close = &static_close;
    listener.configure = &static_configure;
    listener.configure_bounds = &static_configure_bounds;
    xdg_toplevel_add_listener(raw, &this->listener, this);
}

TopLevel::~TopLevel()
{
    xdg_toplevel_destroy(raw);
}

void XDG::TopLevel::set_title(const char* title)
{
    xdg_toplevel_set_title(raw, title);
}
