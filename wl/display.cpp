#include "display.h"
#include "wl_exception.h"
#include <wayland-client.h>
#include <iostream>

using namespace wl;

Display::Display(const char* name)
    : raw_display(wl::expect_not_null<wl_display>(wl_display_connect(name), "wl_display_connect failed"))
    , _registry(wl::expect_not_null<wl_registry>(wl_display_get_registry(raw_display), "wl_display_get_registry failed"))
{
}

Display::~Display()
{
    _registry.destroy(); // otherwise registry will be killed after, which crashes the application
    wl_display_disconnect(raw_display);
}

int Display::dispatch()
{
    return wl_display_dispatch(raw_display);
}

int Display::roundtrip()
{
    return wl_display_roundtrip(raw_display);
}
