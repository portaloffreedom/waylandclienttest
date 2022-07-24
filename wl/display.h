#ifndef WL_DISPLAY_H
#define WL_DISPLAY_H

#include <wayland-client.h>
#include "registry.h"

namespace wl {

/**
 * @todo write docs
 */
class Display
{
public:
    explicit Display(const char* name = nullptr);
    Display(const Display&) = delete;

    ~Display();

    Registry& registry() { return _registry; }
    int dispatch();
    int roundtrip();


    inline wl_display* operator*() { return raw_display; }

private:
    wl_display* raw_display;
    wl::Registry _registry;
};

}

#endif // WL_DISPLAY_H
