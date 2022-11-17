#include <iostream>
#include "../Crow_all.h"

using namespace crow;
using namespace std;

namespace controllers {

	class UserController {
	public:
		static string Print() {
			return "bomdia";
		}

		static response SignUp(const request& req) {
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
		}
	};

}