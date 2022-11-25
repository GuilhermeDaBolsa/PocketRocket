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
		this->rooms.emplace_back(this->nextRoomId, roomName, 4);					//TODO SEE IF THIS WAY IS PERFORMANT (I THINK IT IS GETTING COPIED!!!!)
		this->nextRoomId += 1;

		return &this->rooms[this->rooms.size() - 1];
	}

	//TODO i feel like there is something wrong with this method... idk... maybe it does a lot of things... maybe it shouldnt be here.. idk
	//TODO SEARCH MORE ABOUT IF RETURNING CONST CHAR* IS OK FOR 'ERROR' VERIFYING OR IF IT SHOULD BE AN ENUM OR SOMETHING ELSE... (i dont like throwing things when its not a true error)
	const char* addUserInRoom(User& user, Room& room) {
		
		if (room.isFull())
			return "There is no more room in this room :T";

		room.addUser(user);
		return "";
	}

	const vector<Room>& roomsList() const {
		return this->rooms;
	}

};