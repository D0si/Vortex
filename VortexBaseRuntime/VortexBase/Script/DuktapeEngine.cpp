#include <VortexBase/Script/DuktapeEngine.h>
#ifdef HAS_FEATURE_DUKTAPE
#include <duktape-cpp/DuktapeCpp.h>
#endif
#include <Core/GlobalRuntime.h>

using Vortex::Core::RuntimeInterface;

#ifdef HAS_FEATURE_DUKTAPE

namespace DuktapeBindings {

    class View {
    public:
        View() {}

        View(RuntimeInterface* runtime)
            : _runtime(runtime) {}

        void echo(std::string content) {
            _runtime->view()->echo(content);
        }

        void set_content_type(std::string content_type) {
            _runtime->view()->set_content_type(content_type);
        }

        void set_status_code(int status_code) {
            _runtime->view()->set_status_code(status_code);
        }

        void set_cookie(const std::string& cookie_string) {
            _runtime->view()->set_cookie(cookie_string);
        }

        void set_template(std::string name) {
            _runtime->view()->set_template(name);
        }

        void set_page(std::string name) {
            _runtime->view()->set_page(name);
        }

        std::string parse_page() {
            return _runtime->view()->parse_page();
        }

        void finish() {
            return _runtime->view()->finish();
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<View>);
            i.method("echo", &View::echo);
            i.method("set_content_type", &View::set_content_type);
            i.method("set_status_code", &View::set_status_code);
            i.method("set_cookie", &View::set_cookie);
            i.method("set_template", &View::set_template);
            i.method("set_page", &View::set_page);
            i.method("parse_page", &View::parse_page);
            i.method("finish", &View::finish);
        }

    private:
        RuntimeInterface* _runtime;
    };


    class Router {
    public:
        Router() {}

        Router(RuntimeInterface* runtime)
            : _runtime(runtime) {}

        std::string get_hostname() const {
            return _runtime->router()->hostname();
        }

        std::string get_lang() const {
            return _runtime->router()->lang();
        }

        std::string get_controller() const {
            return _runtime->router()->controller();
        }

        std::vector<std::string> get_args() const {
            return _runtime->router()->args();
        }

        std::string get_post() const {
            return _runtime->router()->request_post_body();
        }

        std::string get_cookie(const std::string& cookie_name) const {
            return _runtime->router()->cookie(cookie_name);
        }

        std::string get_cookies_json() const {
            auto cookies = _runtime->router()->cookies();
            Maze::Element cookies_obj(Maze::Type::Object);

            for (const auto& cookie : cookies) {
                cookies_obj.set(cookie.first, cookie.second);
            }

            return cookies_obj.to_json();
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<Router>);
            i.property("hostname", &Router::get_hostname);
            i.method("get_hostname", &Router::get_hostname);
            i.property("lang", &Router::get_lang);
            i.method("get_lang", &Router::get_lang);
            i.property("controller", &Router::get_controller);
            i.method("get_controller", &Router::get_controller);
            i.property("args", &Router::get_args);
            i.method("get_args", &Router::get_args);
            i.property("post", &Router::get_post);
            i.method("get_post", &Router::get_post);
            i.method("get_cookie", &Router::get_cookie);
            i.method("get_cookies_json", &Router::get_cookies_json);
        }

    private:
        RuntimeInterface* _runtime;
    };


    class Application {
    public:
        Application() {}

        Application(RuntimeInterface* runtime)
            : _runtime(runtime) {}

        std::string get_id() {
            return _runtime->application()->id();
        }

        std::string get_title() {
            return _runtime->application()->title();
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<Application>);
            i.method("get_id", &Application::get_id);
            i.method("get_title", &Application::get_title);
        }

    private:
        RuntimeInterface* _runtime;
    };


    class Storage {
    public:
        Storage() {}

        void simple_insert(const std::string& database, const std::string& collection, const std::string& json_value) {
            Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->simple_insert(database, collection, json_value);
        }

        std::string simple_find_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            return Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->simple_find_all(database, collection, json_simple_query);
        }

        std::string simple_find_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            return Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->simple_find_first(database, collection, json_simple_query);
        }

        void simple_replace_first(const std::string& database, const std::string& collection, const std::string& json_simple_query, const std::string& replacement_json_value) {
            Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->simple_replace_first(database, collection, json_simple_query, replacement_json_value);
        }

        void simple_delete_all(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->simple_delete_all(database, collection, json_simple_query);
        }

        void simple_delete_first(const std::string& database, const std::string& collection, const std::string& json_simple_query) {
            return Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->simple_delete_first(database, collection, json_simple_query);
        }

        std::vector<std::string> get_database_list() {
            return Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->get_database_list();
        }

        std::vector<std::string> get_collection_list(const std::string& database) {
            return Vortex::Core::GlobalRuntime::instance().storage().get_backend()
                ->get_collection_list(database);
        }

        template<class Inspector>
        static void inspect(Inspector& i) {
            i.construct(&std::make_shared<Storage>);
            i.method("simple_insert", &Storage::simple_insert);
            i.method("simple_find_all", &Storage::simple_find_all);
            i.method("simple_find_first", &Storage::simple_find_first);
            i.method("simple_replace_first", &Storage::simple_replace_first);
            i.method("simple_delete_all", &Storage::simple_delete_all);
            i.method("simple_delete_first", &Storage::simple_delete_first);
            i.method("get_database_list", &Storage::get_database_list);
            i.method("get_collection_list", &Storage::get_collection_list);
        }
    };

}  // namespace DuktapeBindings


DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::View);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Router);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Application);
DUK_CPP_DEF_CLASS_NAME(DuktapeBindings::Storage);

#endif  // HAS_FEATURE_DUKTAPE

namespace VortexBase::Script {

    DuktapeEngine::DuktapeEngine() {
#ifdef HAS_FEATURE_DUKTAPE
        _ctx = new duk::Context();
#endif
    }

    DuktapeEngine::~DuktapeEngine() {
#ifdef HAS_FEATURE_DUKTAPE
        if (_ctx != nullptr) {
            delete _ctx;
        }
#endif
    }

    void DuktapeEngine::init(RuntimeInterface* runtime) {
        _runtime = runtime;

#ifdef HAS_FEATURE_DUKTAPE
        _ctx->registerClass<DuktapeBindings::View>();
        auto view = std::make_shared<DuktapeBindings::View>(_runtime);
        _ctx->registerClass<DuktapeBindings::Router>();
        auto router = std::make_shared<DuktapeBindings::Router>(_runtime);
        _ctx->registerClass<DuktapeBindings::Application>();
        auto application = std::make_shared<DuktapeBindings::Application>(_runtime);
        _ctx->registerClass<DuktapeBindings::Storage>();
        auto storage = std::make_shared<DuktapeBindings::Storage>();

        _ctx->addGlobal("__view", view);
        _ctx->addGlobal("__router", router);
        _ctx->addGlobal("__application", application);
        _ctx->addGlobal("__storage", storage);

        exec("view=__view;router=__router;application=__application;storage=__storage;");
#endif
    }

    void DuktapeEngine::exec(const std::string& script) {
#ifdef HAS_FEATURE_DUKTAPE
        if (script.length() > 0) {
            try {
                _ctx->evalStringNoRes(script.c_str());
            }
            catch (duk::DuktapeException& e) {
                std::string message = e.what();
                _runtime->view()->echo("<i>Script error (duktape engine):</i><pre>" + message + "</pre>");
                _runtime->view()->respond();
                _runtime->exit();
            }
            catch (...) {
                _runtime->view()->echo("<i>Script error (duktape engine)</i>");
                _runtime->view()->respond();
                _runtime->exit();
            }
        }
#else
        _runtime->view()->echo("Duktape script engine is unavailable.");
        _runtime->view()->respond();
        _runtime->exit();
#endif
    }

    ScriptEngineInterface* get_new_duktape_engine() {
        return new DuktapeEngine();
    }

}
