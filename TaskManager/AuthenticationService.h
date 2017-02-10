#pragma once
#include "User.h"

class AuthenticationService
{
private:
	static User* loggedUser;
public:
	AuthenticationService();
	~AuthenticationService();

	static void Authenticate(char username[20], char password[20]);
	
	static User* getLoggedUser();
};

