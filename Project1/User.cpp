class User {
public:
	int id;
	char* nickname;
	char* login;
	char* encrypted_password;

	User(char* nickname, char* login, char* encrypted_password)
		: nickname(nickname), login(login), encrypted_password(encrypted_password){}
};