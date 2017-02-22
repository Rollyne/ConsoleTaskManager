#include "stdafx.h"
#include "iostream"
#include "Console.h"

#include "UserManagementView.h"
#include "UserRepository.h"

using namespace std;

UserManagementView::UserManagementView()
{
}


UserManagementView::~UserManagementView()
{
}

CRUDMenuItems UserManagementView::RenderMenu()
{
	system("cls");

	cout << "## Users Management ##" << endl
		<< "[A]dd" << endl
		<< "[L]ist" << endl
		<< "[E]dit" << endl
		<< "[D]elete" << endl
		<< "E[x]it" << endl
		<< "> " ;
	char* buffer;
	try
	{
		buffer = Console::ReadLineMin(1);
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return CRUDMenuItems::Fail;
	}
	

	switch (toupper(buffer[0]))
	{
	case 'A':
		return CRUDMenuItems::Add;
	case 'L':
		return CRUDMenuItems::List;
	case 'E':
		return CRUDMenuItems::Edit;
	case 'D':
		return CRUDMenuItems::Delete;
	case 'X':
		return CRUDMenuItems::Exit;
	default :
		return CRUDMenuItems::Invalid;
	}
}


void UserManagementView::Add()
{
	system("cls");

	User* newUser = new User;
	char* buffer;
	try
	{
		cout << "## Create a user ##" << endl
			<< "Username: ";
		buffer = Console::ReadLineMin(nameMinLength);
		newUser->setUsername(buffer);

		cout << "Password: ";
		buffer = Console::ReadLineMin(nameMinLength);
		newUser->setPassword(buffer);

		cout << "First name: ";
		buffer = Console::ReadLineMin(nameMinLength);
		newUser->setFirstName(buffer);

		cout << "Last name: ";
		buffer = Console::ReadLineMin(nameMinLength);
		newUser->setLastName(buffer);

		cout << "Is admin (Y/N): ";
		buffer = Console::ReadLineMin(1);
		if (toupper(buffer[0]) == 'Y')
			newUser->setIsAdmin(true);
		else
			newUser->setIsAdmin(false);

		UserRepository* repo = new UserRepository("users.txt");

		repo->Add(newUser);
		delete repo;
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	delete newUser;

	system("pause");
}

void UserManagementView::List()
{
	system("cls");

	UserRepository* repo = new UserRepository("users.txt");
	LinkedList<User>* allUsers = repo->GetAll();

	int usersCount = allUsers->Count();

	cout << "## All users ##" << endl << endl;
	for (int i = 0; i < usersCount; i++)
	{
		User* current = allUsers->getItemAt(i);

		cout.setf(ios::boolalpha);
		cout << "# # # # # # # # # # #" << endl
			<< "Index: " << current->getId() << endl
			<< "Username: " << current->getUsername() << endl
			<< "First name: " << current->getFirstName() << endl
			<< "Last name: " << current->getLastName() << endl
			<< "Is admin: " << current->getIsAdmin() << endl;
	}

	delete repo;
	delete allUsers;
	
	system("pause");
}

void UserManagementView::Edit()
{
	system("cls");

	cout << "## Update user ##" << endl
		<< "Index of the user: ";
	try
	{
		User* updated = new User;
		
		char* buffer;
		updated->setId(Console::ReadNumber());

		UserRepository* repo = new UserRepository("users.txt");

		 auto outdated = repo->GetById(updated->getId());
		if (outdated != NULL)
		{
			cout << "Username |" << outdated->getUsername() << "| : ";
			buffer = Console::ReadLine(20, nameMinLength);
			updated->setUsername(buffer);

			cout << "Password |" << outdated->getPassword() << "| : ";
			buffer = Console::ReadLine(20, nameMinLength);
			updated->setPassword(buffer);

			cout << "First name |" << outdated->getFirstName() << "| : ";
			buffer = Console::ReadLine(20, nameMinLength);
			updated->setFirstName(buffer);

			cout << "Last name |" << outdated->getLastName() << "| : ";
			buffer = Console::ReadLine(20, nameMinLength);
			updated->setLastName(buffer);

			cout.setf(ios::boolalpha);
			cout << "Is admin |" << outdated->getIsAdmin() << "| (Y/N): ";
			buffer = Console::ReadLineMin(1);
			if (toupper(buffer[0]) == 'Y')
				updated->setIsAdmin(true);
			else
				updated->setIsAdmin(false);

			repo->Update(updated);

			delete repo;
			delete updated;
			delete outdated;
		}
		else
		{
			cout << "This user doesn't exist." << endl;
		}
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
	}

	system("pause");
}

void UserManagementView::Delete()
{
	system("cls");

	UserRepository* repo = new UserRepository("users.txt");
	cout << "## Delete user ##" << endl
		<< "Index of the user: ";
	User* removed;
	try
	{
		removed = repo->GetById(Console::ReadNumber());
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	if (removed != NULL)
	{
		repo->Delete(removed);

		cout << "User removed." << endl;
	}
	else
	{
		cout << "This user doesn't exist" << endl;
	}

	delete repo;
	delete removed;

	system("pause");
}

void UserManagementView::Run()
{
	while (true)
	{
		CRUDMenuItems choice = RenderMenu();
		switch (choice)
		{
		case CRUDMenuItems::Add:
			Add();
			break;
		case CRUDMenuItems::List:
			List();
			break;
		case CRUDMenuItems::Edit:
			Edit();
			break;
		case CRUDMenuItems::Delete:
			Delete();
			break;
		case CRUDMenuItems::Exit:
			return;
		case CRUDMenuItems::Invalid:
			cout << "Invalid choice" << endl;
			system("pause");
			break;
		}
	}
}
