#ifndef WL_SHELLSURFACE_H
#define WL_SHELLSURFACE_H

#include <wayland-client.h>

namespace wl {

class Shell;

/**
 * @todo write docs
 */
class ShellSurface
{
public:
    ShellSurface(const ShellSurface&) = delete;
    ~ShellSurface();

    void set_toplevel();

    void _ping(uint32_t serial);
    void _configure(uint32_t edges,
                    int32_t width,
                    int32_t height);
    void _popup_done();

private:
    ShellSurface(wl_shell_surface *raw);

private:
    wl_shell_surface *raw = nullptr;
    wl_shell_surface_listener listener;

friend class wl::Shell;
};

}

#endif // WL_SHELLSURFACE_H
