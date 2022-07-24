#include "wmbase.h"
#include "wl/surface.h"
#include "xdg/surface.h"
#include "wl_exception.h"

using namespace XDG;

static void generic_pong(void *data,
                         struct xdg_wm_base *xdg_wm_base,
                         uint32_t serial)
{
    XDG::WMBase *window_manager = static_cast<XDG::WMBase*>(data);
    window_manager->pong(serial);
}

void XDG::WMBase::pong(uint32_t serial)
{
    xdg_wm_base_pong(raw_xdg_wm_base, serial);
}

XDG::WMBase::WMBase(xdg_wm_base* xdg_wm_base)
    :raw_xdg_wm_base(xdg_wm_base)
{
    this->listener.ping = &generic_pong;
    xdg_wm_base_add_listener(raw_xdg_wm_base, &this->listener, this);
}

XDG::WMBase::~WMBase()
{
    xdg_wm_base_destroy(raw_xdg_wm_base);
}

XDG::Surface XDG::WMBase::get_xdg_surface(::wl::Surface &surface)
{
    xdg_surface* raw = xdg_wm_base_get_xdg_surface(raw_xdg_wm_base, *surface);
    return XDG::Surface(wl::expect_not_null(raw, "Error creating XDG Surface"));
}
