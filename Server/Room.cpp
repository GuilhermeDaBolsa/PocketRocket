#pragma once
#include <vector>
#include "User.cpp"

using namespace std;

class Room {
public:

	unsigned int id;
	size_t max_users;
	vector<User> *users;
	char* socketURI;		//THIS IS THE SOCKET URI THAT IS LISTENING... WHERE THE PLAYERS SHOULD CONNECT

	//TODO: OPEN SOCKET CONNECTION HERE IN THE ROOM???

	Room(unsigned int id, size_t max_users, char* socketURI) {
		this->id = id;
		this->max_users = max_users;
		this->socketURI = socketURI;
		this->users = new vector<User>();
	}

	void addUser(const User& user) {
		this->users->push_back(user);
	}
};