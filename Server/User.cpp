#pragma once
class User {
public:
	const unsigned int id;
	const char* nickname;

	unsigned int currentRoom;


	User(const unsigned int id, const char* nickname)
		: id(id), nickname(nickname), currentRoom(0){ }
};