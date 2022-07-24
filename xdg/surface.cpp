#include "surface.h"
#include "wl_exception.h"

using namespace XDG;

static void global_configure(void* data, xdg_surface* raw, uint32_t serial)
{
    XDG::Surface *surface = static_cast<XDG::Surface*>(data);
    surface->ack_configure(serial);
}

void XDG::Surface::ack_configure(uint32_t serial)
{
    xdg_surface_ack_configure(raw, serial);
}


Surface::Surface(xdg_surface* raw)
    : raw(raw)
{
    listener.configure = &global_configure;
    xdg_surface_add_listener(raw, &this->listener, this);
}

Surface::~Surface()
{
    xdg_surface_destroy(raw);
}

XDG::TopLevel XDG::Surface::get_toplevel()
{
    xdg_toplevel* raw = xdg_surface_get_toplevel(this->raw);
    return XDG::TopLevel(wl::expect_not_null(raw,"Error getting XDG Surface top level"));
}
