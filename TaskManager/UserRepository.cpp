#include "stdafx.h"
#include "string.h"
#include "fstream"

#include "UserRepository.h"

using namespace std;

UserRepository::UserRepository(char filepath[50])
{
	strcpy_s(this->filepath, 50, filepath);
}

UserRepository::~UserRepository()
{
}

int UserRepository::getNextId()
{
	int nextId = 0;
	
	ifstream in(this->filepath);

	if (in.is_open())
	{
		User* current = NULL;
		while (!in.eof())
		{
			char buffer[20];
			current = new User;
			
			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);

			if (current->getId() > nextId)
			{
				nextId = current->getId();
			}
		}
		in.close();
		return nextId + 1;
	}
	
	return -1;
}

void UserRepository::Add(User * user)
{
	ofstream out(this->filepath, ios::app);

	if (out.is_open())
	{
		out << this->getNextId() << endl
			<< user->getUsername() << endl
			<< user->getPassword() << endl
			<< user->getFirstName() << endl
			<< user->getLastName() << endl
			<< user->getIsAdmin() << endl;

		out.close();
		return;
	}
	
}

User * UserRepository::GetById(int id)
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

			if (!in.eof() && current->getId() == id)
			{
				result = current;
				break;
			}
		}
	}
	return result;
}

LinkedList<User>* UserRepository::GetAll()
{
	LinkedList<User>* result = new LinkedList<User>();
	ifstream in(this->filepath);

	if (in.is_open())
	{
		User* current = NULL;
		while (!in.eof())
		{
			char buffer[20];
			current = new User;

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

			result->Add(current);
		}
	}
	
	int resultCount = result->Count();
	if (resultCount > 0)
		result->RemoveAt(resultCount - 1);

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

			if (strcmp(current->getPassword(), password) == 0 &&
				strcmp(current->getUsername(), username) == 0)
			{
				result = current;
				break;
			}
		}
	}
	return result;
}

void UserRepository::Update(User * user)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		User* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[20];
			current = new User();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setUsername(buffer);

			oldFile.getline(buffer, 20);
			current->setPassword(buffer);

			oldFile.getline(buffer, 20);
			current->setFirstName(buffer);

			oldFile.getline(buffer, 20);
			current->setLastName(buffer);

			oldFile.getline(buffer, 20);
			current->setIsAdmin(atoi(buffer));

			if (!oldFile.eof() && current->getId() != user->getId())
			{
				newFile << current->getId() << endl
					<< current->getUsername() << endl
					<< current->getPassword() << endl
					<< current->getFirstName() << endl
					<< current->getLastName() << endl
					<< current->getIsAdmin() << endl;
			}
			else if (!oldFile.eof() && current->getId() == user->getId())
			{
				newFile << user->getId() << endl
					<< user->getUsername() << endl
					<< user->getPassword() << endl
					<< user->getFirstName() << endl
					<< user->getLastName() << endl
					<< user->getIsAdmin() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}

void UserRepository::Delete(User * user)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		User* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[20];
			current = new User();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setUsername(buffer);

			oldFile.getline(buffer, 20);
			current->setPassword(buffer);

			oldFile.getline(buffer, 20);
			current->setFirstName(buffer);

			oldFile.getline(buffer, 20);
			current->setLastName(buffer);

			oldFile.getline(buffer, 20);
			current->setIsAdmin(atoi(buffer));

			if (!oldFile.eof() && current->getId() != user->getId())
			{
				newFile << current->getId() << endl
					<< current->getUsername() << endl
					<< current->getPassword() << endl
					<< current->getFirstName() << endl
					<< current->getLastName() << endl
					<< current->getIsAdmin() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}
