#include "stdafx.h"
#include "iostream"

#include "UserManagementView.h"
#include "UserRepository.h"
#include "User.h"

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
	char buffer[2];
	cin.getline(buffer, 2);

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
	char buffer[20];

	cout << "## Create a user ##" << endl
		<< "Username: ";
	cin.getline(buffer, 20, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newUser->setUsername(buffer);

	cout << "Password: ";
	cin.getline(buffer, 20, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newUser->setPassword(buffer);

	cout << "First name: ";
	cin.getline(buffer, 20, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newUser->setFirstName(buffer);

	cout << "Last name: ";
	cin.getline(buffer, 20, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newUser->setLastName(buffer);

	cout << "Is admin (Y/N): ";
	cin.getline(buffer, 20, '\n');
	if (toupper(buffer[0]) == 'Y')
		newUser->setIsAdmin(true);
	else
		newUser->setIsAdmin(false);

	UserRepository* repo = new UserRepository("users.txt");
	
	repo->Add(newUser);


	delete repo;
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
	
	User* updated = new User;
	User* outdated = new User;
	char buffer[20];

	cout << "## Update user ##" << endl
		<< "Index of the user: ";
	cin.getline(buffer, 20);
	updated->setId(atoi(buffer));

	UserRepository* repo = new UserRepository("users.txt");
	
	outdated = repo->GetById(atoi(buffer));
	if (outdated != NULL) 
	{
		cout << "Username |" << outdated->getUsername() << "| : ";
		cin.getline(buffer, 20);
		if (!validate->IsMinLength(buffer, nameMinLength))
			return;
		updated->setUsername(buffer);

		cout << "Password |" << outdated->getPassword() << "| : ";
		cin.getline(buffer, 20);
		if (!validate->IsMinLength(buffer, nameMinLength))
			return;
		updated->setPassword(buffer);

		cout << "First name |" << outdated->getFirstName() << "| : ";
		cin.getline(buffer, 20);
		if (!validate->IsMinLength(buffer, nameMinLength))
			return;
		updated->setFirstName(buffer);

		cout << "Last name |" << outdated->getLastName() << "| : ";
		cin.getline(buffer, 20);
		if (!validate->IsMinLength(buffer, nameMinLength))
			return;
		updated->setLastName(buffer);

		cout.setf(ios::boolalpha);
		cout << "Is admin |" << outdated->getIsAdmin() << "| (Y/N): ";
		cin.getline(buffer, 20);
		if (toupper(buffer[0]) == 'Y')
			updated->setIsAdmin(true);
		else
			updated->setIsAdmin(false);

		repo->Update(updated);
	}
	else
	{
		cout << "This user doesn't exist." << endl;
	}

	delete repo;
	delete updated;
	delete outdated;

	system("pause");
}

void UserManagementView::Delete()
{
	system("cls");

	char buffer[20];

	

	UserRepository* repo = new UserRepository("users.txt");
	cout << "## Delete user ##" << endl
		<< "Index of the user: ";
	cin.getline(buffer, 20);
	User* removed = repo->GetById(atoi(buffer));
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
