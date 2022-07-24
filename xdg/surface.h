#ifndef XDG_SURFACE_H
#define XDG_SURFACE_H

#include "xdg-shell.h"
#include "xdg/toplevel.h"

namespace XDG {

class WMBase;

/**
 * @todo write docs
 */
class Surface
{
public:
    Surface(const Surface&) = delete;
    ~Surface();

    XDG::TopLevel get_toplevel();

    void ack_configure(uint32_t serial);

private:
    Surface(xdg_surface* raw);

private:
    xdg_surface* raw = nullptr;
    xdg_surface_listener listener;

friend class XDG::WMBase;
};

}

#endif // XDG_SURFACE_H
