#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class Room {
public:

	unsigned int id;
	const char* name;
	unsigned int maxUsers;
	vector<User*> users;

	Room(unsigned int id, const char* name, unsigned int maxUsers)
		: id(id), name(name), maxUsers(maxUsers) { }

	void addUser(User& user) {
		user.currentRoom = this->id;
		this->users.push_back(&user);
	}

	bool isFull() {
		return this->users.size() == this->maxUsers;
	}

	const vector<User*>& usersList() const {
		return this->users;
	}
};