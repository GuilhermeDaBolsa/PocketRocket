#include <vector>
#include "Room.cpp"

using namespace std;

class RoomsManager {

private:
	vector<Room> rooms;
	unsigned int nextRoomId;	//THIS WAY OF MANAGE ID IS BAD

	//TODO: CREATE A QUEUE FOR THE FUNCTIONS THAT THE ROOMSMANAGER SHOULD EXECUTE? (THINKING OF A MORE THREAD SAFE THING)

public:

	RoomsManager() 
		: nextRoomId(1) {} //1 is important ( 0 is none )

	Room* createRoom(const char* roomName) {
		this->rooms.emplace_back(this->nextRoomId, roomName, 4);
		this->nextRoomId += 1;

		return &this->rooms[this->rooms.size() - 1];
	}

	Room* getRoom(const unsigned int roomId) {
		for (int i = 0; i < this->rooms.size(); i++) {
			if (this->rooms[i].id == roomId)
				return &this->rooms[i];
		}

		return nullptr;
	}

	const vector<Room>& roomsList() const {
		return this->rooms;
	}

};