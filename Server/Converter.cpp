#pragma once

#include "Crow_all.h"

#include <vector>
#include "./User.cpp"
#include "./Room.cpp"

using namespace crow;

class Converter {
public:

	static json::wvalue& toJson(User& user) {
		auto json = new json::wvalue({ {"id", user.id}, {"nickname", user.nickname}, {"currentRoom", user.currentRoom} });
		return *json; //TODO I THINK THIS JSON IS NEVER FREED FROM MEM (MAYBE SMART POINTERS CAN BE USED WHERE THIS FUNC IS CALLED)
	}

	static json::wvalue& toJson(Room& room) {
		auto users = vector<json::wvalue>();

		for (int i = 0; i < room.users.size(); i++)
			users.push_back(toJson(*room.users[i]));

		auto json = new json::wvalue({ {"id", room.id}, {"name", room.name}, {"maxUsers", room.maxUsers}, {"users", users}});

		return *json; //TODO I THINK THIS JSON IS NEVER FREED FROM MEM (MAYBE SMART POINTERS CAN BE USED WHERE THIS FUNC IS CALLED)
	}
};