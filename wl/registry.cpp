#include "registry.h"
#include "wl/sharedmemory.h"
#include <wayland-client.h>
#include <cstring>
#include <iostream>
#include <functional>

using namespace wl;

extern "C" void global_handler(void *data, wl_registry *raw_registry, uint32_t id, const char* interface, uint32_t version)
{
    wl::Registry *registry = static_cast<wl::Registry*>(data);
    registry->event_add(id, interface, version);
}

extern "C" void global_error(void *data, wl_registry *raw_registry, uint32_t id)
{
    wl::Registry *registry = static_cast<wl::Registry*>(data);
    registry->event_remove(id);
}

Registry::Registry(wl_registry* raw_registry)
    : raw_registry(raw_registry)
{
    using namespace std::placeholders;
    registry_listener.global = &::global_handler;
    registry_listener.global_remove = &::global_error;
    wl_registry_add_listener(raw_registry, &this->registry_listener, this);
}

Registry::~Registry()
{
    this->destroy();
}

void wl::Registry::destroy()
{
    if (raw_registry != nullptr) {
        wl_registry_destroy(raw_registry);
        raw_registry = nullptr;
    }
}



void wl::Registry::event_add(uint32_t id, const char* interface, uint32_t version)
{
    std::cout << "Registry has " << interface << std::endl;
    registry_map[interface] = std::make_pair(id, version);
}

void wl::Registry::event_remove(uint32_t id)
{
    for (auto it = registry_map.begin(); it != registry_map.end(); ++it) {
        if (it->second.first == id) {
            registry_map.erase(it);
            return;
        }
    }
    std::clog << "Registry removal failed, not found: " << id << std::endl;
}

wl::Compositor wl::Registry::bind_compositor()
{
    wl_compositor* raw_compositor = this->bind<wl_compositor>("wl_compositor", &wl_compositor_interface);
    return wl::Compositor(raw_compositor);
}

wl::Shell wl::Registry::bind_shell()
{
    wl_shell* raw_shell = this->bind<wl_shell>("wl_shell", &wl_shell_interface);
    return wl::Shell(raw_shell);
}

XDG::WMBase wl::Registry::bind_xdg_wm_base()
{
    xdg_wm_base* raw = this->bind<xdg_wm_base>("xdg_wm_base", &xdg_wm_base_interface);
    return XDG::WMBase(raw);
}

wl::SharedMemory wl::Registry::bind_shm()
{
    wl_shm* raw = this->bind<wl_shm>("wl_shm", &wl_shm_interface);
    return wl::SharedMemory(raw);
}

ZXDG::DecorationManager wl::Registry::bind_decoration_manager()
{
    zxdg_decoration_manager_v1 *raw = this->bind<zxdg_decoration_manager_v1>(
        "zxdg_decoration_manager_v1", &zxdg_decoration_manager_v1_interface);
    return ZXDG::DecorationManager(raw);
}

