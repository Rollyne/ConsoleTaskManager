#include "stdafx.h"
#include "string.h"

#include "User.h"


User::User()
{
}


User::~User()
{
}

void User::setId(int id) 
{
	this->id = id;
}
int User::getId()
{
	return this->id;
}

void User::setUsername(char username[20])
{
	strcpy_s(this->username,20, username);
}
char* User::getUsername()
{
	return this->username;
}

void User::setPassword(char password[20])
{
	strcpy_s(this->password, 20, password);
}

char * User::getPassword()
{
	return this->password;
}


void User::setFirstName(char firstName[20])
{
	strcpy_s(this->firstName,20, firstName);
}
char* User::getFirstName()
{
	return this->firstName;
}

void User::setLastName(char lastName[20])
{
	strcpy_s(this->lastName,20, lastName);
}
char* User::getLastName()
{
	return this->lastName;
}

void User::setIsAdmin(bool isAdmin)
{
	this->isAdmin = isAdmin;
}
bool User::getIsAdmin()
{
	return this->isAdmin;
}
