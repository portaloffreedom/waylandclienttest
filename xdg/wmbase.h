#ifndef XDG_WMBASE_H
#define XDG_WMBASE_H

#include "xdg-shell.h"
#include "wl/surface.h"

namespace wl {
    class Registry;
    class Surface;
}

namespace XDG {

class Surface;

/**
 * @todo write docs
 */
class WMBase
{
public:
    WMBase(const WMBase&) = delete;
    ~WMBase();

    XDG::Surface get_xdg_surface(::wl::Surface &surface);

    void pong(uint32_t serial);

private:
    WMBase(xdg_wm_base *xdg_wm_base);
private:
    xdg_wm_base *raw_xdg_wm_base = nullptr;
    xdg_wm_base_listener listener;

    friend class wl::Registry;
};

}

#endif // XDG_WMBASE_H
