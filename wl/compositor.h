#ifndef WL_COMPOSITOR_H
#define WL_COMPOSITOR_H

#include <wayland-client.h>
#include "surface.h"

namespace wl {

class Registry;

/**
 * @todo write docs
 */
class Compositor
{
public:
    Compositor(const Compositor&) = delete;

    /**
     * Destructor
     */
    ~Compositor();

    wl::Surface create_surface();

private:
    Compositor(wl_compositor* raw_compositor);

private:
    wl_compositor *raw_compositor = nullptr;

    friend class wl::Registry;
};

}

#endif // WL_COMPOSITOR_H
