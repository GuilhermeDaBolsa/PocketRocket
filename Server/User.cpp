class User {
public:
	unsigned int id;
	char* nickname;

	User(unsigned int id, char* nickname)
		: id(id), nickname(nickname){}
};