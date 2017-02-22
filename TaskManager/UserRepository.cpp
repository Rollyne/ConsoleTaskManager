#include "stdafx.h"
#include "string.h"

#include "UserRepository.h"

using namespace std;

void UserRepository::writeItem( User* item, ofstream* file)
{

	if (file->is_open())
	{
		if (item->getId() < 0) // If it is less than zero it is undefined
			item->setId(this->getNextId());
		*file << item->getId() << endl
			<< item->getUsername() << endl
			<< item->getPassword() << endl
			<< item->getFirstName() << endl
			<< item->getLastName() << endl
			<< item->getIsAdmin() << endl;
	}
}

User* UserRepository::readItem(ifstream* file)
{
	User* result = NULL;

	if (file->is_open())
	{
		User* current = new User;
		char buffer[20];

		file->getline(buffer, 20);
		current->setId(atoi(buffer));

		file->getline(buffer, 20);
		current->setUsername(buffer);

		file->getline(buffer, 20);
		current->setPassword(buffer);

		file->getline(buffer, 20);
		current->setFirstName(buffer);

		file->getline(buffer, 20);
		current->setLastName(buffer);

		file->getline(buffer, 20);
		current->setIsAdmin(atoi(buffer));

		result = current;

	}
	return result;
}

User * UserRepository::GetByUsernameAndPassword(char username[20], char password[20])
{
	ifstream in(this->filepath);
	User* result = NULL;

	if (in.is_open())
	{
		User* current = NULL;
		while (!in.eof())
		{
			
			current = readItem(&in);

			if (!in.eof() && strcmp(current->getPassword(), password) == 0 &&
				strcmp(current->getUsername(), username) == 0)
			{
				result = current;
				break;
			}
		}
	}
	return result;
}


