#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class UsersManager {
	vector<User> users;
	unsigned int nextUserId;	//THIS WAY OF MANAGE ID IS BAD

public:
	UsersManager() 
		: nextUserId(1) {} //1 is important ( 0 is none )

	User* createUser(const char* nickname) {
		this->users.emplace_back(this->nextUserId, nickname);						//TODO SEE IF THIS WAY IS PERFORMANT (I THINK IT IS GETTING COPIED!!!!)
		this->nextUserId += 1;

		return &this->users[this->users.size() - 1];
	}

	User* getUser(const unsigned int userId) {
		for (int i = 0; i < this->users.size(); i++) {
			if (this->users[i].id == userId)
				return &this->users[i];
		}

		return nullptr;
	}

	const vector<User>& usersList() const {
		return this->users;
	}
	
};