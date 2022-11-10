#include "Crow_all.h"
#include <vector>
#include <string>

using namespace std;
using namespace crow;

int main() {
    vector<int> numbers = vector<int>();
    
    SimpleApp app;




    CROW_ROUTE(app, "/")([&numbers]() {
        numbers.emplace_back(numbers.size());

        string t = "Hello World ";
        for (int i = 0; i < numbers.size(); i++)
            t.append(std::to_string(numbers[i]) + ", ");

        return t;
    });





    CROW_ROUTE(app, "/signUp").methods("POST"_method)([](const request& req) {
        auto reqJson = json::load(req.body);

        if (!reqJson)
            return response(status::BAD_REQUEST, "Missing request body");
        if (!reqJson.has("login") || reqJson["login"].t() != json::type::String)
            return response(status::BAD_REQUEST, "Missing login");
        if (!reqJson.has("password") || reqJson["password"].t() != json::type::String)
            return response(status::BAD_REQUEST, "Missing password");

        string login = reqJson["login"].s();
        string password = reqJson["password"].s();
        
        return response(status::CREATED, "User not yet created with login " + login + " and password " + password);
    });

    app.port(18080).multithreaded().run();

    return 0;
}