#include <iostream>
#include <cstring>
#include <wayland-client.h>
#include <wayland-egl.h>
#include "xdg-shell-client-protocol.h"
#include "wl/display.h"
#include "xdg/surface.h"
#include "wl/sharedmemory.h"
#include "wl/buffer.h"
#include "myegl/egl.h"

int main(int argc, char **argv)
{
    bool running = true;

    wl::Display display(nullptr);
    std::cout << "connected to display" << std::endl;

    wl::Registry &registry = display.registry();

    display.dispatch();
    display.roundtrip();

    wl::Compositor compositor = registry.bind_compositor();
    wl::Surface surface = compositor.create_surface();

//     if (registry.has("xdg_wm_base")) {
        std::cout << "Found XDG wayland window manager" << std::endl;
        XDG::WMBase window_manager = registry.bind_xdg_wm_base();
        XDG::Surface xdg_surface = window_manager.get_xdg_surface(surface);
        XDG::TopLevel toplevel = xdg_surface.get_toplevel();
        toplevel.set_title("Test Wayland window");
        toplevel.on_close = [&] (const XDG::TopLevel& o) { running = false; };

//     } else if (registry.has("wl_shell")) {
//         std::cout << "Found XDG wayland shell [DEPRECATED]" << std::endl;
//         wl::Shell shell = registry.bind_shell();
//         wl::ShellSurface shell_surface = shell.get_shell_surface(surface);
//         shell_surface.set_toplevel();
//     } else {
//         std::clog << "NO SHELL FOUND" << std::endl;
//         return 1;
//     }


    wl::SharedMemory shm = registry.bind_shm();
    display.dispatch();

    int width = 480, height = 360;
    uint32_t pixel_color = 0x0;

    wl::Buffer surface_buffer = shm.create_buffer(width, height);

    surface.on_redraw = [&](wl::Surface* wlsurface)
    {
        surface.damage(0, 0, width, height);
        pixel_color += 0x010101;
        if (pixel_color > 0xffffff) {
            pixel_color = 0x0;
        }
        surface_buffer.write_all(pixel_color);
        surface.attach(surface_buffer);
        surface.request_redraw();
        surface.commit();
    };

    surface.redraw();
    surface.commit();

//     EGL egl(*display);
//     auto egl_window = egl.create_window(surface, width, height);


    std::clog << "Startup finished" << std::endl;

    while (running && display.dispatch() != -1) {
//         std::clog << "loop" << std::endl;
//         egl_window.swap_buffers();
        //This space deliberately left blank
    }

    std::clog << "Program ended" << std::endl;
    return 0;
}
