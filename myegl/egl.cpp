#include "egl.h"
#include "wl_exception.h"
#include "wl/surface.h"
#include <wayland-egl.h>
#include <iostream>

EGL::EGL(wl_display *display)
{

    EGLint count, n, size;

    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    static const EGLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };


    egl_display = eglGetDisplay((EGLNativeDisplayType) display);
    if (egl_display == EGL_NO_DISPLAY) {
        throw wl::exception("Can't create egl display");
    } else {
        std::clog << "Created egl display" << std::endl;
    }

    if (eglInitialize(egl_display, &major, &minor) != EGL_TRUE) {
        throw wl::exception("Can't initialise egl display");
    }

    std::clog << "EGL major: " << major << ", minor " << minor << std::endl;

    eglGetConfigs(egl_display, NULL, 0, &count);
    std::clog << "EGL has " << count << " configs" << std::endl;

    configs = static_cast<EGLConfig*>(calloc(count, sizeof *configs));

    eglChooseConfig(egl_display, config_attribs,
                    configs, count, &n);

    for (int i = 0; i < n; i++) {
        eglGetConfigAttrib(egl_display,
                configs[i], EGL_BUFFER_SIZE, &size);
        eglGetConfigAttrib(egl_display,
                configs[i], EGL_RED_SIZE, &size);

        // just choose the first one
        egl_conf = configs[i];
        break;
    }

    egl_context = eglCreateContext(egl_display,
                                   egl_conf,
                                   EGL_NO_CONTEXT, context_attribs);

}

EGL::~EGL()
{
    eglDestroyContext(egl_display, egl_context);
}

EGLWindow EGL::create_window(wl::Surface &surface, int width, int height)
{
    wl_egl_window *egl_window = wl_egl_window_create(*surface, width, height);
    if (egl_window == EGL_NO_SURFACE) {
        throw wl::exception("Can't create egl window");
    } else {
        std::clog << "Created egl window" << std::endl;
    }


    return EGLWindow(egl_window, *this);
}
