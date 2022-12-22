#include <cstdlib>
#include <ctime>

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

    queue<User*>        usersToBindConnection;

    srand(static_cast <unsigned> (time(0)));

    auto& cors = app.get_middleware<CORSHandler>();
    cors.global().methods("POST"_method, "GET"_method).prefix("*").ignore();

    CROW_ROUTE(app, "/")([]() { return "Hello, world!"; });

    CROW_ROUTE(app, "/get_rooms").methods("GET"_method)([&roomsManager](const crow::request& req) {
        auto rooms = roomsManager.roomsList();

        auto roomsJson = vector<json::wvalue>();
        for (auto& room : rooms)
            roomsJson.emplace_back(Converter::basicRoomToJson(room));

        return crow::response(status::OK, json::wvalue({ {"rooms", roomsJson} }));
    });

    CROW_ROUTE(app, "/create_user").methods("POST"_method)([&usersManager](const crow::request& req) {
        User* user = usersManager.createUser(new char[8] {'o', 's', 'w', 'a', 'l', 'd', 'o', 0});
        return crow::response(status::OK, Converter::basicUserToJson(*user));
    });

    CROW_ROUTE(app, "/exit_room").methods("POST"_method)([&usersManager](const crow::request& req) {

        auto reqJson = json::load(req.body);

        // 1 - Validate request body
        if (!reqJson)
            return response(status::BAD_REQUEST, "Missing request body");

        if (!reqJson.has("userId"))
            return response(status::BAD_REQUEST, "Missing user");

        if(reqJson["userId"].t() != json::type::Number)
            return response(status::UNAUTHORIZED, "Not logged in");

        // 2 - Get user
        User* user = usersManager.getUser(reqJson["userId"].i());

        if (user == nullptr)
            return response(status::UNAUTHORIZED, "User does not exist");

        if (user->currentRoom == nullptr)
            return response(status::CONFLICT, "User is not in a room");

        user->currentRoom->removeUser(*user);

        return crow::response(status::OK, json::wvalue());
    });

    CROW_ROUTE(app, "/join_room").methods("POST"_method)([&usersManager, &roomsManager](const crow::request& req) {

        auto reqJson = json::load(req.body);


        // 1 - Validate request body
        if (!reqJson)
            return response(status::BAD_REQUEST, "Missing request body");

        if (!reqJson.has("userId"))
            return response(status::BAD_REQUEST, "Missing user");

        if (reqJson["userId"].t() != json::type::Number)
            return response(status::UNAUTHORIZED, "Not logged in");

        if (!reqJson.has("roomId") || reqJson["roomId"].t() != json::type::Number)
            return response(status::BAD_REQUEST, "Missing room");


        // 2 - Get user
        User* user = usersManager.getUser(reqJson["userId"].i());

        if (user == nullptr)
            return response(status::UNAUTHORIZED, "User does not exist");

        if (user->currentRoom != nullptr)
            return response(status::CONFLICT, "User is already in a room");


        // 3 - Get room
        Room* room = roomsManager.getRoom(reqJson["roomId"].i());

        if (room == nullptr)
            return response(status::NOT_FOUND, "Room does not exist");

        if (room->isFull())
            return response(status::FORBIDDEN, "Room is full");


        // 4 - Put user in room
        room->addUser(*user);


        // 5 - Return room info
        return crow::response(status::OK, Converter::roomToJson(*room));
    });

    CROW_ROUTE(app, "/create_room").methods("POST"_method)([&usersManager, &roomsManager](const crow::request& req) {

        auto reqJson = json::load(req.body);

        // 1 - Validate request body
        if (!reqJson)
            return response(status::BAD_REQUEST, "Missing request body");

        if (!reqJson.has("userId"))
            return response(status::BAD_REQUEST, "Missing user");

        if (reqJson["userId"].t() != json::type::Number)
            return response(status::UNAUTHORIZED, "Not logged in");


        // 2 - Get user
        User* user = usersManager.getUser(reqJson["userId"].i());

        if (user == nullptr)
            return response(status::UNAUTHORIZED, "User does not exist");

        if ((*user).currentRoom != 0)
            return response(status::CONFLICT, "User is already in a room");


        // 3 - Create new room
        Room* newRoom = roomsManager.createRoom(new char[8] {'s', 'a', 'l', 'i', 'n', 'h', 'a', 0});

        if (newRoom->isFull())
            return response(status::FORBIDDEN, "Room is full");


        // 4 - Put user in room
        newRoom->addUser(*user);


        // 5 - Return room info
        return crow::response(status::OK, Converter::roomToJson(*newRoom));
    });

    //CROW_ROUTE(app, "/signUp").methods("POST"_method)(&userController.SignUp);

    CROW_WEBSOCKET_ROUTE(app, "/ws")
    .onaccept([&](const crow::request& req, void** userdata) {

        char* strUserId = req.url_params.get("userId");

        if(strUserId == nullptr)
            return false;

        int userId = Converter::toInt(strUserId);

        User* user = usersManager.getUser(userId);

        if (user == nullptr)
            return false;

        /*
        this usersToBindConnection was created hoping that there is no way that onaccept -> onopen
        can finish faster than another onaccept -> onopen that was started earlier (TODO MAYBE THERE IS A BETTER WAY TO ASSIGN A CONNECTION TO A USER... BUT IDK)
        */
        usersToBindConnection.push(user); //BY FVCK LEOZ

        return true;
        })
    .onopen([&](crow::websocket::connection& conn) {
        usersToBindConnection.front()->userConnection.connect(conn);
        usersToBindConnection.pop();
        CROW_LOG_INFO << "websocket connection established";
    })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason){
        //TODO NÃO FUNCIONA ISSO AQUI ABAIXO E TAMBÈM CONFLITA COM A ROTA DO EXIT_ROOM (A CONNECTION VAI ESTAR NULLPTR)
        /*auto& users = usersManager.usersList();

        for (User& user : users) {
            if (user.userConnection.connection->get_remote_ip() == conn.get_remote_ip()) {
                user.currentRoom->removeUser(user);
                break;
            }
        }*/

        // TODO: remover conexão da lista de conexões da sala
        CROW_LOG_INFO << "websocket connection closed: " << reason;
    })
    .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
        auto& users = usersManager.usersList();

        for (User& user : users) {
            if (user.userConnection.connection != nullptr 
            && user.userConnection.connection->get_remote_ip() == conn.get_remote_ip()) {
                
                user.player.setInput(&data);
                break;
            }
        }
    });

    app.port(8080).run();

    return 0;
}