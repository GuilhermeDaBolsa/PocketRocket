#include <vector>
#include "Room.cpp"

using namespace std;

class RoomsManager {

private:
	vector<Room> *rooms;

	//TODO: CREATE A QUEUE FOR THE FUNCTIONS THAT THE ROOMSMANAGER SHOULD EXECUTE? (THINKING OF A MORE THREAD SAFE THING)

public:

	RoomsManager() {
		this->rooms = new vector<Room>();
	}

	//TODO SEARCH MORE ABOUT IF RETURNING CONST CHAR* IS OK FOR 'ERROR' VERIFYING OR IF IT SHOULD BE AN ENUM OR SOMETHING ELSE... (i dont like throwing things when its not a true error)
	const char* addUserInRoom(const User& user, Room& room) {
		if (room.users->size() == room.max_users)
			return "A sala está cheia";

		room.addUser(user);
		return "";
	}

};