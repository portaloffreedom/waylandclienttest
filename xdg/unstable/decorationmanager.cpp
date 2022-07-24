#include "decorationmanager.h"
#include "./topleveldecoration.h"
#include "xdg/toplevel.h"

using namespace ZXDG;

DecorationManager::DecorationManager(zxdg_decoration_manager_v1 *c_pointer)
    : c_pointer(c_pointer)
{

}

DecorationManager::~DecorationManager()
{
    zxdg_decoration_manager_v1_destroy(c_pointer);
}

ZXDG::TopLevelDecoration ZXDG::DecorationManager::get_toplevel_decoration(XDG::TopLevel& toplevel)
{
    zxdg_toplevel_decoration_v1 *raw = zxdg_decoration_manager_v1_get_toplevel_decoration(c_pointer, *toplevel);
    return TopLevelDecoration(raw);
}
