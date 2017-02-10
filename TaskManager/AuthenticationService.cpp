#include "stdafx.h"
#include "AuthenticationService.h"
#include "CommentRepository.h"


AuthenticationService::AuthenticationService()
{
}


AuthenticationService::~AuthenticationService()
{
}

User* AuthenticationService::loggedUser = NULL;

void AuthenticationService::Authenticate(char username[20], char password[20])
{
	UserRepository* repo = new UserRepository("users.txt");
	AuthenticationService::loggedUser = repo->GetByUsernameAndPassword(username, password);
}

User * AuthenticationService::getLoggedUser()
{
	return AuthenticationService::loggedUser;
}
