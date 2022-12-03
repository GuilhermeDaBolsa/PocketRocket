#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class Room {
public:

	unsigned int id;
	char* name;
	unsigned int maxUsers;
	//TODO ADD SOCKET CONNECTION HERE? (I THINK IT IS A GOOD IDEA)
	vector<User*> users;

	Room(unsigned int id, const char* name, unsigned int maxUsers)
		: id(id), name((char*)name), maxUsers(maxUsers) {

		this->users.reserve(maxUsers); //prevents vector realocation... idk if helps in this case
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