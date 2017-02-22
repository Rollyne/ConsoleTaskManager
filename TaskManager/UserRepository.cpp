#include "stdafx.h"
#include "string.h"

#include "UserRepository.h"

using namespace std;

void UserRepository::writeItem( User* item, ofstream* file)
{

	if (file->is_open())
	{
		*file << this->getNextId() << endl
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
		User* current = NULL;
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
			char buffer[20];
			current = new User();

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 20);
			current->setUsername(buffer);

			in.getline(buffer, 20);
			current->setPassword(buffer);

			in.getline(buffer, 20);
			current->setFirstName(buffer);

			in.getline(buffer, 20);
			current->setLastName(buffer);

			in.getline(buffer, 20);
			current->setIsAdmin(atoi(buffer));

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


