#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class UsersManager {
	vector<User> users;
	unsigned int nextUserId;	//THIS WAY OF MANAGE ID IS BAD

public:
	UsersManager() {
		this->users = vector<User>();
		this->nextUserId = 0;
	}

	User& createUser(const char* nickname) {
		User *newUser = new User(this->nextUserId, nickname);
		this->users.push_back(*newUser);

		this->nextUserId += 1;

		return *newUser;
	}

	bool hasUser(const unsigned int userId) {
		for (int i = 0; i < this->users.size(); i++) {
			if (this->users[i].id == userId)
				return true;
		}

		return false;
	}

	const vector<User>& usersList() const {
		return this->users;
	}
	
};