cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(waylandclient)

find_package(PkgConfig)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
pkg_check_modules(WAYLAND_EGL REQUIRED wayland-egl)
pkg_check_modules(WAYLAND_CURSOR REQUIRED wayland-cursor)
pkg_check_modules(WAYLAND_SCANNER REQUIRED wayland-scanner)
pkg_check_modules(WAYLAND_PROTOCOLS REQUIRED wayland-protocols)
pkg_check_modules(EGL REQUIRED egl)

# Get variables
pkg_get_variable(WAYLAND_SCANNER_BIN wayland-scanner wayland_scanner)
pkg_get_variable(WAYLAND_PROTOCOLS_DATADIR wayland-protocols pkgdatadir)

# GENERATE XDG PROTOCOLS SOURCES
add_custom_command(COMMAND ${WAYLAND_SCANNER_BIN} 
    ARGS private-code "${WAYLAND_PROTOCOLS_DATADIR}/stable/xdg-shell/xdg-shell.xml" "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c"
    DEPENDS "${WAYLAND_PROTOCOLS_DATADIR}/stable/xdg-shell/xdg-shell.xml"
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c"
    COMMENT "Generating xdg protocol private code."
    )

add_custom_command(COMMAND ${WAYLAND_SCANNER_BIN}
    ARGS client-header "${WAYLAND_PROTOCOLS_DATADIR}/stable/xdg-shell/xdg-shell.xml" "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h"
    DEPENDS "${WAYLAND_PROTOCOLS_DATADIR}/stable/xdg-shell/xdg-shell.xml"
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h"
    COMMENT "Generating xdg protocol header."
    )

# Main code
add_executable(waylandclient
    main.cpp
    wl_exception.h
    wl/display.cpp wl/display.h
    wl/registry.cpp wl/registry.h
    wl/compositor.cpp wl/compositor.h
    wl/surface.cpp wl/surface.h
    wl/shell.cpp wl/shell.h
    wl/shellsurface.cpp wl/shellsurface.h
    wl/sharedmemory.cpp wl/sharedmemory.h
    wl/buffer.cpp wl/buffer.h
    xdg/wmbase.cpp xdg/wmbase.h
    xdg/surface.cpp xdg/surface.h
    xdg/toplevel.cpp xdg/toplevel.h
    myegl/egl.cpp myegl/egl.h
    myegl/eglwindow.cpp myegl/eglwindow.h
    "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c"
    xdg-shell-client-protocol.h)

target_include_directories(waylandclient
    PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS}
    PRIVATE ${WAYLAND_CURSOR_INCLUDE_DIRS}
    PRIVATE ${WAYLAND_EGL_INCLUDE_DIRS}
    PRIVATE ${EGL_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE ${CMAKE_SOURCE_DIR}
    )

target_link_libraries(waylandclient
    PRIVATE ${WAYLAND_CLIENT_LIBRARIES}
    PRIVATE ${WAYLAND_CURSOR_LIBRARIES}
    PRIVATE ${WAYLAND_EGL_LIBRARIES}
    PRIVATE ${EGL_LIBRARIES}
    )

install(TARGETS waylandclient RUNTIME DESTINATION bin)

add_subdirectory(examples)
