#include "eglwindow.h"
#include "EGL/egl.h"
#include "myegl/egl.h"
#include <iostream>

EGLWindow::EGLWindow(wl_egl_window* c_pointer, const EGL &egl)
    : c_pointer(c_pointer)
    , egl_display(egl.egl_display)
{
    EGLNativeWindowType egl_window_native = reinterpret_cast<EGLNativeWindowType>(c_pointer);

    egl_surface = eglCreateWindowSurface(egl_display, egl.egl_conf, egl_window_native, nullptr);

    this->make_current(egl);
    this->swap_buffers();
}

EGLWindow::~EGLWindow()
{
    wl_egl_window_destroy(c_pointer);
}

void EGLWindow::make_current(const EGL &egl)
{
    if(eglMakeCurrent(egl_display, egl_surface, egl_surface, egl.egl_context)) {
        std::clog << "Made current" << std::endl;
    } else {
        std::clog << "Made current failed" << std::endl;
    }
}

void EGLWindow::swap_buffers()
{
    if (eglSwapBuffers(egl_display, egl_surface)) {
        std::clog << "Swapped buffers" << std::endl;
    } else {
        std::clog << "Swapped buffers failed" << std::endl;
    }
}
