#include "topleveldecoration.h"

using namespace ZXDG;

TopLevelDecoration::TopLevelDecoration(zxdg_toplevel_decoration_v1 *c_pointer)
    : c_pointer(c_pointer)
{

}

TopLevelDecoration::~TopLevelDecoration()
{
    zxdg_toplevel_decoration_v1_destroy(c_pointer);
}

void ZXDG::TopLevelDecoration::set_mode(TopLevelDecoration::Mode mode)
{
    zxdg_toplevel_decoration_v1_set_mode(c_pointer, mode);
}
