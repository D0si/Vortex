#pragma once

#include <Core/Modules/Plugin.h>

namespace Vortex::App::Db::Plugins {

    class DbApplicationPlugin : public Vortex::Core::Modules::Plugin {
    public:
        static const std::string s_plugin_name;

        virtual const std::string plugin_name() const override;
        virtual Vortex::Core::Modules::PluginExecutePoint execute_point() override;
    };

}  // namespace Vortex::App::Db::Plugins
