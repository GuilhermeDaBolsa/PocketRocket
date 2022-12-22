#pragma once
#include <thread>
#include <chrono>
#include <vector>

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
	}

	void gameLoop() {
		std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
		std::chrono::steady_clock::time_point end;
		double elapsed_time;
		unsigned long long tick = 0;
		unsigned long requestTick = 0;

		while (true) {
			end = std::chrono::high_resolution_clock::now();
			elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

			//"UPDATE" stuff
			for (int i = 0; i < this->users->size(); i++) {
				this->users->at(i)->player.update(elapsed_time);
			}

			start = std::chrono::high_resolution_clock::now();

			//"RENDER" stuff
			if (requestTick >= 2) {
				requestTick = 0;

				std::string frameResponse;
				for (int i = 0; i < this->users->size(); i++) {
					User* user = this->users->at(i);

					frameResponse.append(
						to_string(user->id) + ',' +
						to_string(user->player.x) + ',' +
						to_string(user->player.y) + ';'
					);
				}

				for (int i = 0; i < this->users->size(); i++) {
					auto& userConnection = this->users->at(i)->userConnection;

					if (userConnection.status == ConnectionStatus::Connected &&
					userConnection.connection != nullptr) {

						userConnection.connection->send_text(frameResponse);
					}
				}
			}

			this_thread::sleep_for(chrono::milliseconds(10));
			tick += 1;
			requestTick += 1;
		}
	}
};