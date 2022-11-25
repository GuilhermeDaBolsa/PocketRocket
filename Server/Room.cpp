#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class Room {
public:

	unsigned int id;
	const char* name;
	unsigned int maxUsers;
	vector<User> users;

	Room(unsigned int id, const char* name, unsigned int maxUsers)
		: id(id), name(name), maxUsers(maxUsers) { }

	void addUser(User& user) {
		user.currentRoom = this->id;
		this->users.push_back(user); //TODO SEE IF THIS WAY IS PERFORMANT (I THINK IT IS GETTING COPIED!!!!)
	}

	bool isFull() {
		return this->users.size() == this->maxUsers;
	}

	const vector<User>& usersList() const {
		return this->users;
	}
};