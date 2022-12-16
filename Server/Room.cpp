#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class Room {
public:

	unsigned int id;
	char* name;
	unsigned int maxUsers;
	char* connectionRoute;
	vector<User*> users;

	Room(unsigned int id, const char* name, unsigned int maxUsers, const char* connectionRoute)
		: id(id), name((char*)name), maxUsers(maxUsers), connectionRoute((char*)connectionRoute){

		this->users.reserve(maxUsers); //prevents vector realocation... idk if helps with someting in this case
	}

	void addUser(User& user) {
		user.currentRoom = this->id;
		this->users.push_back(&user);
	}

	bool isFull() {
		return this->users.size() >= this->maxUsers;
	}

	const vector<User*>& usersList() const {
		return this->users;
	}
};