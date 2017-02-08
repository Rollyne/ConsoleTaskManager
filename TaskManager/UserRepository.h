#pragma once
#include "User.h"
#include "LinkedList.cpp"

class UserRepository
{
private:
	int getNextId();
	char filepath[50];
public:
	void Add(User* user);

	User* GetById(int id);
	LinkedList<User>* GetAll();
	User* GetByUsernameAndPassword(char username[20], char password[20]);

	void Update(User* user);

	void Delete(User* user);

	UserRepository(char filepath[50]);
	~UserRepository();
};

