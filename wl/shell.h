#ifndef WL_SHELL_H
#define WL_SHELL_H

#include "wl/shellsurface.h"
#include "wl/surface.h"
#include <wayland-client.h>

namespace wl {

class Registry;

/**
 * @todo write docs
 */
class Shell
{
public:
    Shell(const Shell&) = delete;
    ~Shell();

    wl::ShellSurface get_shell_surface(wl::Surface &surface);

private:
    Shell(wl_shell* raw_shell);

private:
    wl_shell* raw_shell = nullptr;

    friend class wl::Registry;
};

}

#endif // WL_SHELL_H
