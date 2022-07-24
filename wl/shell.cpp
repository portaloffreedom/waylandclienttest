#include "shell.h"
#include "wl_exception.h"

using namespace wl;

Shell::Shell(wl_shell* raw_shell)
    :raw_shell(raw_shell)
{}

Shell::~Shell()
{
    wl_shell_destroy(raw_shell);
}

wl::ShellSurface wl::Shell::get_shell_surface(wl::Surface &surface)
{
    wl_shell_surface *raw = wl_shell_get_shell_surface(this->raw_shell, *surface);
    return wl::ShellSurface(wl::expect_not_null(raw, "Error creating shell surface"));
}
