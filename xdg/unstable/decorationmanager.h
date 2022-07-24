#ifndef ZXDG_DECORATIONMANAGER_H
#define ZXDG_DECORATIONMANAGER_H

#include "xdg-decoration-unstable-v1.h"
#include "xdg/toplevel.h"
#include "xdg/unstable/topleveldecoration.h"

namespace ZXDG {

class TopLevelDecoration;

/**
 * @todo write docs
 */
class DecorationManager
{
public:
    /**
     * Default constructor
     */
    DecorationManager(zxdg_decoration_manager_v1 *c_pointer);

    /**
     * Copy constructor deleted
     */
    DecorationManager(const DecorationManager& other) = delete;

    /**
     * Destructor
     */
    ~DecorationManager();

    ZXDG::TopLevelDecoration get_toplevel_decoration(XDG::TopLevel &toplevel);

private:
    zxdg_decoration_manager_v1 *c_pointer = nullptr;
};

}

#endif // ZXDG_DECORATIONMANAGER_H
