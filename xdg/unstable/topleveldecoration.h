#ifndef ZXDG_TOPLEVELDECORATION_H
#define ZXDG_TOPLEVELDECORATION_H

#include "xdg-decoration-unstable-v1.h"

namespace ZXDG {

/**
 * @todo write docs
 */
class TopLevelDecoration
{
public:
    /**
     * Default constructor
     */
    TopLevelDecoration(zxdg_toplevel_decoration_v1 *c_pointer );

    /**
     * Copy constructor deleted
     */
    TopLevelDecoration(const TopLevelDecoration& other) = delete;

    /**
     * Destructor
     */
    ~TopLevelDecoration();

    enum Mode {
        ClientSide = ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE,
        ServerSide = ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE,
    };

    void set_mode(TopLevelDecoration::Mode mode);

private:
    zxdg_toplevel_decoration_v1 *c_pointer = nullptr;
};

}

#endif // ZXDG_TOPLEVELDECORATION_H
