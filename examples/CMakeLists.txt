

add_executable(waylandclient_c_tutorial
    "${CMAKE_BINARY_DIR}/xdg-shell-protocol.c"
    damage.c
)
target_include_directories(waylandclient_c_tutorial
    PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS}
    PRIVATE ${WAYLAND_EGL_INCLUDE_DIRS}
    PRIVATE ${WAYLAND_CURSOR_INCLUDE_DIRS}
    PRIVATE ${CMAKE_BINARY_DIR}
    PRIVATE ${CMAKE_SOURCE_DIR}
    )

target_link_libraries(waylandclient_c_tutorial
    PRIVATE ${WAYLAND_CLIENT_LIBRARIES}
    PRIVATE ${WAYLAND_EGL_LIBRARIES}
    PRIVATE ${WAYLAND_CURSOR_LIBRARIES}
    )
