#pragma once
#include <vector>
#include "Crow_all.h"

#include "./User.cpp"
#include "./Room.cpp"

using namespace crow;

class Converter {
public:
	//NOTE: CROW JSON SEEMS TO BE EXTREMELY POOR PERFORMANT AT FIRST GLANCE... IT MAY NOT BE

	static json::wvalue basicUserToJson(User& user) {
		return json::wvalue({ {"id", user.id}, {"nickname", user.nickname} });
	}

	static json::wvalue userToJson(User& user) {
		return json::wvalue({ {"id", user.id}, {"nickname", user.nickname}, {"currentRoom", user.currentRoom} });
	}

	static json::wvalue basicRoomToJson(Room& room) {
		return json::wvalue({ {"id", room.id}, {"name", room.name}, {"maxUsers", room.maxUsers}, {"usersCount", room.users.size()} });
	}

	static json::wvalue roomToJson(Room& room) {
		auto users = vector<json::wvalue>();

		for (int i = 0; i < room.users.size(); i++)
			users.emplace_back(basicUserToJson(*room.users[i]));

		return json::wvalue({ {"id", room.id}, {"name", room.name}, {"maxUsers", room.maxUsers}, {"connectionRoute", room.connectionRoute}, {"users", users}});
	}

	static unsigned int toInt(const char* str) {
		stringstream stream = stringstream(str);
		int i = 0;
		stream >> i;
		return i;
	}
};