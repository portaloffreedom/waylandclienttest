#ifndef EGLWINDOW_H
#define EGLWINDOW_H

#include <wayland-egl.h>
#include <EGL/egl.h>

class EGL;

/**
 * @todo write docs
 */
class EGLWindow
{
public:
    /**
     * Default constructor
     */
    EGLWindow(wl_egl_window* c_pointer, const EGL &egl);

    /**
     * Copy constructor deleted
     */
    EGLWindow(const EGLWindow& other) = delete;

    /**
     * Destructor
     */
    ~EGLWindow();

    void make_current(const EGL &egl);

    void swap_buffers();

private:
    wl_egl_window* c_pointer = nullptr;
    EGLSurface egl_surface;
    EGLDisplay egl_display;
};

#endif // EGLWINDOW_H
