#include "Crow_all.h"

#include "./controllers/UserController.h"

using namespace std;
using namespace crow;
using namespace controllers;

int main() {

    App<CORSHandler>    app;
    UserController      userController;

    auto& cors = app.get_middleware<CORSHandler>();

    cors
      .global()
        .methods("POST"_method, "GET"_method)
      .prefix("*")
        .ignore();

    CROW_ROUTE(app, "/")([]() { return "Hello, world!"; });
    
    CROW_ROUTE(app, "/bomdia").methods("GET"_method)(&userController.Print);
    CROW_ROUTE(app, "/signUp").methods("POST"_method)(&userController.SignUp);

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen([&](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "websocket connection is open: ";
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason){
            CROW_LOG_INFO << "websocket connection closed: " << reason;
        })
        .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary){
            CROW_LOG_INFO << data << "< message data";
        });

    app.port(8080)
        .multithreaded()
        .run();

    return 0;
}