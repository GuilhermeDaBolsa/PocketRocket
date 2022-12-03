#pragma once
#include "Crow_all.h"

class User {
public:
	const unsigned int id;
	char* nickname;

	unsigned int currentRoom;
	crow::websocket::connection* connection;

	User(const unsigned int id, const char* nickname)
		: id(id), nickname((char*)nickname), currentRoom(0){ }

	void setConnection(crow::websocket::connection& conn) {
		this->connection = &conn;
	}
};