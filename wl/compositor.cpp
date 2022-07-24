#include "wl/compositor.h"
#include "wl_exception.h"

using namespace wl;

Compositor::Compositor(wl_compositor* raw_compositor)
    : raw_compositor(raw_compositor)
{

}

Compositor::~Compositor()
{
    wl_compositor_destroy(raw_compositor);
}


wl::Surface wl::Compositor::create_surface()
{
    wl_surface* raw_surface = wl_compositor_create_surface(raw_compositor);
    return wl::Surface(wl::expect_not_null(raw_surface, "Cannot create surface from compositor"));
}
