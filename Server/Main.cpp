#include "Crow_all.h"
#include <vector>
#include <string>

#include "./controllers/UserController.h"

using namespace std;
using namespace crow;
using namespace controllers;

int main() {
    SimpleApp       app;
    UserController  userController;

    CROW_ROUTE(app, "/")([]() { return "Hello, world!"; });
    
    CROW_ROUTE(app, "/bomdia").methods("GET"_method)(&userController.Print);
    CROW_ROUTE(app, "/signUp").methods("POST"_method)(&userController.SignUp);
    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen([&](crow::websocket::connection& conn){
            //
            cout << "close" << std::endl;
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason){
            // do_something();
            cout << "close" << std::endl;
        })
        .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary){
            cout << "bomdia" << std::endl;
        });

    app.port(8080).multithreaded().run();

    return 0;
}