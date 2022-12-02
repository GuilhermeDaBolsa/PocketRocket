#pragma once

#include "Crow_all.h"

#include <vector>
#include "./User.cpp"
#include "./Room.cpp"

using namespace crow;

class Converter {
public:
	//NOTE: CROW JSON SEEMS TO BE EXTREMELY POOR PERFORMANT AT FIRST GLANCE... IT MAY NOT BE

	static json::wvalue toJson(User& user) {
		return json::wvalue({ {"id", user.id}, {"nickname", user.nickname}, {"currentRoom", user.currentRoom} });
	}

	static json::wvalue toJson(Room& room) {
		auto users = vector<json::wvalue>();

		for (int i = 0; i < room.users.size(); i++)
			users.emplace_back(toJson(*room.users[i]));

		return json::wvalue({ {"id", room.id}, {"name", room.name}, {"maxUsers", room.maxUsers}, {"users", users}});
	}
};