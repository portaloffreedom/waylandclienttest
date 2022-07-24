#ifndef EGL_H
#define EGL_H

#include <EGL/egl.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include "wl/surface.h"
#include "myegl/eglwindow.h"

/**
 * @todo write docs
 */
class EGL
{
public:
    /**
     * Default constructor
     */
    EGL(wl_display *display);
    EGL(const EGL&) = delete;

    /**
     * Destructor
     */
    ~EGL();

     EGLWindow create_window(wl::Surface &surface, int width, int height);

private:
    EGLint major, minor;
    EGLConfig *configs;
    EGLDisplay egl_display;
    EGLConfig egl_conf;
    EGLContext egl_context;

    friend class EGLWindow;
};

#endif // EGL_H
