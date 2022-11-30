#include "Crow_all.h"

#include "./controllers/UserController.h"
#include "./UsersManager.cpp"
#include "./RoomsManager.cpp"
#include "./Converter.cpp"

using namespace std;
using namespace crow;
using namespace controllers;

int main() {

    App<CORSHandler>    app;
    UserController      userController;
    UsersManager        usersManager;
    RoomsManager        roomsManager;

    auto& cors = app.get_middleware<CORSHandler>();

    cors
      .global()
        .methods("POST"_method, "GET"_method)
      .prefix("*")
        .ignore();

    CROW_ROUTE(app, "/")([]() { return "Hello, world!"; });

    CROW_ROUTE(app, "/host_room").methods("POST"_method)([&usersManager, &roomsManager](const crow::request& req) {

        auto reqJson = json::load(req.body);

        if (!reqJson)
            return response(status::BAD_REQUEST, "Missing request body");


        // 1 - get / create user
        User* user;

        if (reqJson.has("userId") && reqJson["userId"].t() == json::type::Number) {

            user = usersManager.getUser(reqJson["userId"].i());

            if (user == nullptr)
                return response(status::BAD_REQUEST, "User does not exist");

            if ((*user).currentRoom != 0)
                return response(status::BAD_REQUEST, "User is already in room");

        } else {

            user = usersManager.createUser("oswaldo");
        }


        //2 - create new room
        Room* newRoom = roomsManager.createRoom("salinha");

        //3 - put user in room
        roomsManager.addUserInRoom(*user, *newRoom);

        //4 - OPEN SOCKET CONNECTION FOR THIS USER

        //5 - RETURN USER DATA (EX. ID), ROOM DATA??, SCOKET CONNECTION
        
        return crow::response(status::OK, Converter::toJson(*newRoom));
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