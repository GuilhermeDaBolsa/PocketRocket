#pragma once
#include "UserConnection.cpp"
#include "Player.cpp"

class Room; //Foward declaration so the compiler or pre-processor does not enter in a loop of includes

class User {
public:
	const unsigned int id;
	char* nickname;

	Room* currentRoom;
	UserConnection userConnection;
	Player player;

	User(const unsigned int id, const char* nickname)
		: id(id), nickname((char*)nickname), userConnection(UserConnection()), currentRoom(nullptr){ }
};