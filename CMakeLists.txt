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

function(GENERATE_XDG_PROTOCOLS Name)
    # GENERATE XDG PROTOCOLS SOURCES
    set(XDG_PROTOCOLS_SOURCES)
    set(XDG_PROTOCOLS_HEADERS)
    foreach(XML ${ARGN})
        get_filename_component(XML_NAME "${XML}" NAME_WE)
        MESSAGE("Generating C source code for ${XML} -> ${XML_NAME}")
        add_custom_command(COMMAND ${WAYLAND_SCANNER_BIN}
            ARGS private-code "${XML}" "${CMAKE_CURRENT_BINARY_DIR}/${XML_NAME}.c"
            DEPENDS "${XML}"
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${XML_NAME}.c"
            COMMENT "Generating \"${XML_NAME}\" protocol private code."
            )
        list(APPEND XDG_PROTOCOLS_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/${XML_NAME}.c")

        add_custom_command(COMMAND ${WAYLAND_SCANNER_BIN}
            ARGS client-header "${XML}" "${CMAKE_CURRENT_BINARY_DIR}/${XML_NAME}.h"
            DEPENDS "${XML}"
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${XML_NAME}.h"
            COMMENT "Generating \"${XML_NAME}\" protocol header."
            )
        list(APPEND XDG_PROTOCOLS_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/${XML_NAME}.h")
    endforeach()
endfunction()

GENERATE_XDG_PROTOCOLS( Ciao
    "${WAYLAND_PROTOCOLS_DATADIR}/stable/xdg-shell/xdg-shell.xml"
    "${WAYLAND_PROTOCOLS_DATADIR}/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml"
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
    xdg/unstable/decorationmanager.cpp xdg/unstable/decorationmanager.h
    xdg/unstable/topleveldecoration.cpp xdg/unstable/topleveldecoration.h
    myegl/egl.cpp myegl/egl.h
    myegl/eglwindow.cpp myegl/eglwindow.h
    "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell.c"
    "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell.h"
    "${CMAKE_CURRENT_BINARY_DIR}/xdg-decoration-unstable-v1.c"
    "${CMAKE_CURRENT_BINARY_DIR}/xdg-decoration-unstable-v1.h")

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
