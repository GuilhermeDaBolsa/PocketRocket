#pragma once
#include<thread>
#include <chrono>
#include <vector>

#include <cstdlib>//THESE 2 ARE FOR THE RANDOM STUFF
#include <iostream>

#include "User.cpp"
#include "ConnectionStatus.cpp"

using namespace std;

class Game {
public:
	thread gameThread;
	vector<User*>* users;

	Game(vector<User*>* users)
		: users(users) {

		gameThread = thread(&Game::gameLoop, this);
		srand((unsigned)time(NULL)); //TODO THIS RANDOM THINGY WILL BE REMOVED IN THE FUTURE
	}

	void gameLoop() {
		do {
			const float x = ((float)rand() / (float)RAND_MAX) * 500;
			const float y = ((float)rand() / (float)RAND_MAX) * 500;

			for (int i = 0; i < this->users->size(); i++) {
				auto& userConnection = this->users->at(i)->userConnection;

				if (userConnection.status == ConnectionStatus::Connected && userConnection.connection != nullptr) {
					userConnection.connection->send_text(to_string(x) + "," + to_string(y)); //TODO IF USER DISCONNECTS, THE CONNECTION WILL BE FUCKED UP AND SERVER WILL CRASH
				}
			}

			this_thread::sleep_for(chrono::milliseconds(500));
		} while (true);
	}

};