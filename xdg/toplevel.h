#ifndef XDG_TOPLEVEL_H
#define XDG_TOPLEVEL_H

#include "xdg-shell.h"
#include <functional>

namespace XDG {

class Surface;

/**
 * @todo write docs
 */
class TopLevel
{
public:
    TopLevel(const TopLevel&) = delete;
    ~TopLevel();

    void set_title(const char* title);

    void _close();
    void _configure(int32_t width, int32_t height, wl_array *states);
    void _configure_bounds(int32_t width, int32_t height);

    std::function<void(const TopLevel&)> on_close;

    xdg_toplevel* operator*() { return raw; }

private:
    TopLevel(xdg_toplevel *raw);

private:
    xdg_toplevel *raw = nullptr;
    xdg_toplevel_listener listener;

    friend class XDG::Surface;
};

}

#endif // XDG_TOPLEVEL_H
