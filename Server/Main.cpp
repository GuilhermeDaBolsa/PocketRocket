#include "Crow_all.h"

#include "./controllers/UserController.h"
#include "./UsersManager.cpp"
#include "./User.cpp"

using namespace std;
using namespace crow;
using namespace controllers;

int main() {

    App<CORSHandler>    app;
    UserController      userController;
    UsersManager        usersManager;

    auto& cors = app.get_middleware<CORSHandler>();

    cors
      .global()
        .methods("POST"_method, "GET"_method)
      .prefix("*")
        .ignore();

    CROW_ROUTE(app, "/")([]() { return "Hello, world!"; });

    CROW_ROUTE(app, "/host_room").methods("POST"_method)([&usersManager](const crow::request& req) {

        auto reqJson = json::load(req.body);

        if (!reqJson)
            return response(status::BAD_REQUEST, "Missing request body");

        
        //1 - CREATE USER IF DOES NOT HAVE ONE YET
        if (!reqJson.has("userId") || reqJson["userId"].t() != json::type::Number) {
            User& newUser = usersManager.createUser("oswaldo");

        } else {
            unsigned int userId = reqJson["userId"].i();

            if(!usersManager.hasUser(userId))
                return response(status::BAD_REQUEST, "User does not exist");
        }


        //2 - CREATE ROOM

        //3 - PUT USER INTO ROOM

        //4 - OPEN SOCKET CONNECTION FOR THIS USER

        //5 - RETURN USER DATA (EX. ID), ROOM DATA??, SCOKET CONNECTION
        
        
        
        json::wvalue response = json::wvalue();
        for (auto user : usersManager.usersList())
            response[user.id] = user.nickname;

        return crow::response(status::OK, response);
    });


    
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

    app.port(8080).run(); // REMOVED MULTITHREAD FOR NOW...

    return 0;
}