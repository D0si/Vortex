#include <VortexBase/BaseRuntime.h>
#include <Core/Exceptions/ExitFrameworkException.h>
#include <VortexBase/Router.h>
#include <VortexBase/Host.h>
#include <VortexBase/Application.h>
#include <VortexBase/Controller.h>
#include <VortexBase/View.h>
#include <VortexBase/Script/Script.h>
#include <Core/Modules/DependencyInjection.h>

using Vortex::Core::RuntimeInterface;

namespace VortexBase {

    BaseRuntime::BaseRuntime(
        Vortex::Core::Modules::DependencyInjector* di,
        const Maze::Element& config,
        std::string client_ip,
        boost::beast::http::request<boost::beast::http::string_body>* request,
        boost::beast::http::response<boost::beast::http::string_body>* response)
        : RuntimeInterface(di), _config(config), _client_ip(client_ip), _request(request), _response(response),
        _router(new Router(this)), _host(new Host(this)),
        _application(new Application(this)), _controller(new Controller(this)),
        _view(new View(this)), _script(new Script::Script(this)) {}

    BaseRuntime::~BaseRuntime() {
        delete _router;
        delete _host;
        delete _application;
        delete _controller;
        delete _view;
        delete _script;
    }

    void BaseRuntime::init() {
        if (_di->plugin_manager()->on_runtime_init_before(this))
            return;

        _host->init(_router->hostname());

        _script->init();

        _application->init(_host->application_id());

        _config.apply(_application->config());
        _config.apply(_host->config());

        _router->init();

        _controller->init(
            _application->id(),
            _router->controller(),
            _request->method_string().to_string());

        _di->plugin_manager()->on_runtime_init_after(this);
    }

    void BaseRuntime::run() {
        if (_di->plugin_manager()->on_runtime_run_before(this))
            return;

        _script->exec(_application->script());
        _script->exec(_host->script());
        _script->exec(_controller->script());

        _script->exec(_application->post_script());
        _script->exec(_host->post_script());
        _script->exec(_controller->post_script());

        _view->output();

        _di->plugin_manager()->on_runtime_run_after(this);

        throw Vortex::Core::Exceptions::ExitFrameworkException();
    }

    void BaseRuntime::exit() {
        if (_di->plugin_manager()->on_runtime_exit_before(this))
            return;

        _view->respond();
        
        _di->plugin_manager()->on_runtime_exit_after(this);

        throw Vortex::Core::Exceptions::ExitFrameworkException();
    }

    const std::string& BaseRuntime::client_ip() const {
        return _client_ip;
    }

    boost::beast::http::request<boost::beast::http::string_body>* BaseRuntime::request() {
        return _request;
    }

    boost::beast::http::response<boost::beast::http::string_body>* BaseRuntime::response() {
        return _response;
    }

    Maze::Element* BaseRuntime::config() {
        return &_config;
    }

    Vortex::Core::RouterInterface* BaseRuntime::router() {
        return _router;
    }

    Vortex::Core::HostInterface* BaseRuntime::host() {
        return _host;
    }

    Vortex::Core::ApplicationInterface* BaseRuntime::application() {
        return _application;
    }

    Vortex::Core::ControllerInterface* BaseRuntime::controller() {
        return _controller;
    }

    Vortex::Core::ViewInterface* BaseRuntime::view() {
        return _view;
    }

    Vortex::Core::ScriptInterface* BaseRuntime::script() {
        return _script;
    }
    
    Vortex::Core::Modules::DependencyInjector* BaseRuntime::di() {
        return _di;
    }

}
