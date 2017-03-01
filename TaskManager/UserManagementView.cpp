#include "stdafx.h"
#include "iostream"
#include "Console.h"

#include "UserManagementView.h"

using namespace std;

UserManagementView::UserManagementView()
{
}


UserManagementView::~UserManagementView()
{
}

User* UserManagementView::inputItem()
{
	User* item = new User;
	char* buffer;

	cout << "Username: ";
	buffer = Console::ReadLineMin(textFieldMinLength);
	item->setUsername(buffer);

	cout << "Password: ";
	buffer = Console::ReadLineMin(textFieldMinLength);
	item->setPassword(buffer);

	cout << "First name: ";
	buffer = Console::ReadLineMin(textFieldMinLength);
	item->setFirstName(buffer);

	cout << "Last name: ";
	buffer = Console::ReadLineMin(textFieldMinLength);
	item->setLastName(buffer);

	cout << "Is admin (Y/N): ";
	buffer = Console::ReadLineMin(1);
	if (toupper(buffer[0]) == 'Y')
		item->setIsAdmin(true);
	else
		item->setIsAdmin(false);

	return item;
}

void UserManagementView::printItem(User* item)
{
	cout.setf(ios::boolalpha);

	cout << "Index: " << item->getId() << endl
		<< "Username: " << item->getUsername() << endl
		<< "First name: " << item->getFirstName() << endl
		<< "Last name: " << item->getLastName() << endl
		<< "Is admin: " << item->getIsAdmin() << endl;
}

void UserManagementView::updateItem(User* item)
{
	char* buffer;

	cout << "Username |" << item->getUsername() << "| : ";
	buffer = Console::ReadLine(20, textFieldMinLength);
	item->setUsername(buffer);

	cout << "Password |" << item->getPassword() << "| : ";
	buffer = Console::ReadLine(20, textFieldMinLength);
	item->setPassword(buffer);

	cout << "First name |" << item->getFirstName() << "| : ";
	buffer = Console::ReadLine(20, textFieldMinLength);
	item->setFirstName(buffer);

	cout << "Last name |" << item->getLastName() << "| : ";
	buffer = Console::ReadLine(20, textFieldMinLength);
	item->setLastName(buffer);

	cout.setf(ios::boolalpha);
	cout << "Is admin |" << item->getIsAdmin() << "| (Y/N): ";
	buffer = Console::ReadLineMin(1);
	if (toupper(buffer[0]) == 'Y')
		item->setIsAdmin(true);
	else
		item->setIsAdmin(false);
}


void UserManagementView::Add()
{
	auto* repo = new UserRepository("users.txt");
	_add(repo);
	delete repo;
}
void UserManagementView::List()
{
	auto* repo = new UserRepository("users.txt");
	_list(repo);
	delete repo;
}
void UserManagementView::Edit()
{
	auto* repo = new UserRepository("users.txt");
	_edit(repo);
	delete repo;
}
void UserManagementView::Delete()
{
	auto* repo = new UserRepository("users.txt");
	_delete(repo);
	delete repo;
}

