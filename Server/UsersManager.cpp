#pragma once
#include <list>
#include "User.cpp"

using namespace std;

class UsersManager {
	list<User> users;			//THIS IS NOW A LIST INSTEAD OF VECTOR BECAUSE https://www.reddit.com/r/cpp/comments/3xmpz9/holding_reference_or_pointer_of_a_vector_element/
	unsigned int nextUserId;	//THIS WAY OF MANAGE ID IS BAD

public:
	UsersManager() 
		: nextUserId(1) {} //1 is important ( 0 is none )

	User* createUser(const char* nickname) {
		this->users.emplace_back(this->nextUserId, nickname);
		this->nextUserId += 1;

		return &this->users.back();
	}

	User* getUser(const unsigned int userId) {
		for (auto& user : this->users) {
			if (user.id == userId)
				return &user;
		}

		return nullptr;
	}

	list<User>& usersList() {
		return this->users;
	}
	
};