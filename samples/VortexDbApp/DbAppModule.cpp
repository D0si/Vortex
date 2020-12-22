#include "DbAppModule.h"
#include <Core/Modules/DependencyInjection.h>
#include "Plugins/DbRouterPlugin.h"

using namespace Vortex::Core::Modules;

namespace Vortex::App::Db {

    const std::string DbAppModule::s_module_name = "VortexDbApp";

    const std::string DbAppModule::module_name() const {
        return s_module_name;
    }

    const std::vector<std::string> DbAppModule::plugin_names() {
        return std::vector<std::string> {
            Plugins::DbRouterPlugin::s_plugin_name,
        };
    }

    std::shared_ptr<Plugin> DbAppModule::plugin(const std::string& plugin_name) {
        if (plugin_name == Plugins::DbRouterPlugin::s_plugin_name)
            return std::make_shared<Plugins::DbRouterPlugin>();

        return nullptr;
    }

    void DbAppModule::register_di(DependencyInjector* di) {
        di->plugin_manager()->register_plugin(std::make_shared<Plugins::DbRouterPlugin>());
    }
}

VORTEX_APP_API Module* get_vortex_module() {
    return new Vortex::App::Db::DbAppModule;
}

VORTEX_APP_API const char* get_vortex_module_name() {
    return Vortex::App::Db::DbAppModule::s_module_name.c_str();
}
