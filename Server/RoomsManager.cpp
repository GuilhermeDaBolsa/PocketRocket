#include <list>
#include "Room.cpp"

using namespace std;

class RoomsManager {

private:
	list<Room> rooms;			//THIS IS NOW A LIST INSTEAD OF VECTOR BECAUSE https://www.reddit.com/r/cpp/comments/3xmpz9/holding_reference_or_pointer_of_a_vector_element/
	unsigned int nextRoomId;	//THIS WAY OF MANAGE ID IS BAD

	//TODO: CREATE A QUEUE FOR THE FUNCTIONS THAT THE ROOMSMANAGER SHOULD EXECUTE? (THINKING OF A MORE THREAD SAFE THING)

public:

	RoomsManager() 
		: nextRoomId(1) {} //1 is important ( 0 is none )

	Room* createRoom(const char* roomName) {
		this->rooms.emplace_back(this->nextRoomId, roomName, 4);
		this->nextRoomId += 1;

		return &this->rooms.back();
	}

	Room* getRoom(const unsigned int roomId) {
		for (auto& room : this->rooms) {
			if (room.id == roomId)
				return &room;
		}

		return nullptr;
	}

	const list<Room>& roomsList() const {
		return this->rooms;
	}

};