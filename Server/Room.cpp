#pragma once
#include <vector>
#include "User.cpp"
#include "Game.cpp"

using namespace std;

class Room {
public:

	unsigned int id;
	char* name;
	unsigned int maxUsers;
	char* connectionRoute;
	vector<User*> users;
	Game* game; //TODO FOR SOME REASON, IF GAME IS NOT A POINTER, THE ROOM CLASS BECOMES NOT COPIABLE OR NOT MOVABLE (IDK WHICH ONE)

	Room(unsigned int id, const char* name, unsigned int maxUsers, const char* connectionRoute)
		: id(id), name((char*)name), maxUsers(maxUsers), connectionRoute((char*)connectionRoute){

		this->users.reserve(maxUsers);
		this->game = new Game(&users);
	}

	void addUser(User& user) {
		user.currentRoom = this;
		user.userConnection.waitConnection();
		this->users.push_back(&user);
	}

	bool isFull() {
		return this->users.size() >= this->maxUsers;
	}

	const vector<User*>& usersList() const {
		return this->users;
	}
};