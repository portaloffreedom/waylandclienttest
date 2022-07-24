#ifndef WL_REGISTRY_H
#define WL_REGISTRY_H

#include <wayland-client.h>
#include <map>
#include <string>
#include "compositor.h"
#include "shell.h"
#include "xdg/wmbase.h"
#include "wl_exception.h"
#include "xdg/unstable/decorationmanager.h"

namespace wl {

class Display;
class SharedMemory;

/**
 * @todo write docs
 */
class Registry
{
public:
    Registry(const Registry&) = delete;
    ~Registry();
    void destroy();

    wl::Compositor bind_compositor();
    wl::Shell bind_shell();
    wl::SharedMemory bind_shm();
    XDG::WMBase bind_xdg_wm_base();
    ZXDG::DecorationManager bind_decoration_manager();

    template<typename T>
    T* bind(const char* interface_name, const struct wl_interface *interface, uint32_t version = -1)
    {
        std::pair<uint32_t, uint32_t> reg = registry_map.at(interface_name);
        if (version < 0) {
            version = reg.second;
        } else {
            version = 1;
        }
        void* r = wl_registry_bind(raw_registry, reg.first, interface, version);
        if (r == nullptr) {
            throw wl::exception("ERROR loading interface \"") << interface_name << '"';
        }
        return static_cast<T*>(r);
    }

    bool has(const char* interface_name) const
    {
        return registry_map.find(interface_name) != registry_map.end();
    }

    //TODO move them private
    void event_add(uint32_t id, const char* interface, uint32_t version);
    void event_remove(uint32_t id);

protected:
    Registry(wl_registry* raw_registry);

private:
    wl_registry* raw_registry;
    wl_registry_listener registry_listener;

    // interface name -> id, version
    std::map<std::string, std::pair<uint32_t, uint32_t>> registry_map;

    friend class wl::Display;
};

}

#endif // WL_REGISTRY_H
