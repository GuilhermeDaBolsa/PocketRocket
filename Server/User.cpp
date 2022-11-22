#pragma once
class User {
public:
	const unsigned int id;
	const char* nickname;

	User(const unsigned int id)
		: id(id){}

	User(const unsigned int id, const char* nickname)
		: id(id), nickname(nickname){}
};