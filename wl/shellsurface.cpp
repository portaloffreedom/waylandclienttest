#include "shellsurface.h"

using namespace wl;

static void static_ping(void *data,
                        wl_shell_surface *wl_shell_surface,
                        uint32_t serial)
{
    static_cast<wl::ShellSurface*>(data)->_ping(serial);
}

static void static_configure(void *data,
                             wl_shell_surface *wl_shell_surface,
                             uint32_t edges,
                             int32_t width,
                             int32_t height)
{
    static_cast<wl::ShellSurface*>(data)->_configure(edges, width, height);
}
static void static_popup_done(void *data,
                              wl_shell_surface *wl_shell_surface)
{
    static_cast<wl::ShellSurface*>(data)->_popup_done();
}

ShellSurface::ShellSurface(wl_shell_surface *raw)
    : raw(raw)
{
    listener.ping = &static_ping;
    listener.configure = &static_configure;
    listener.popup_done = &static_popup_done;
    wl_shell_surface_add_listener(raw, &listener, this);
}

ShellSurface::~ShellSurface()
{
    wl_shell_surface_destroy(raw);
}

void wl::ShellSurface::set_toplevel()
{
    wl_shell_surface_set_toplevel(raw);
}

void wl::ShellSurface::_ping(uint32_t serial)
{
    wl_shell_surface_pong(raw, serial);
}

void wl::ShellSurface::_configure(uint32_t edges, int32_t width, int32_t height)
{
}

void wl::ShellSurface::_popup_done()
{
}



