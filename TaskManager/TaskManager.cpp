// TaskManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "AuthenticationService.h"
#include "AdministrationView.h"
#include "TaskManagementView.h"

using namespace std;

int main()
{
	while (AuthenticationService::getLoggedUser() == NULL)
	{
		system("cls");

		char username[20];
		char password[20];
		cout << "## Login ##" << endl;
		cout << "Username: ";
		cin.getline(username, 20);

		cout << "Password: ";
		cin.getline(password, 20);

		AuthenticationService::Authenticate(username, password);
	}

	if (AuthenticationService::getLoggedUser()->getIsAdmin())
	{
		AdministrationView view;
		view.Run();
		return 0;
	}
	else 
	{
		TaskManagementView view;
		view.Run();
		return 0;
	}
	
}

