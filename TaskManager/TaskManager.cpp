// TaskManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Console.h"
#include "AuthenticationService.h"
#include <iostream>
#include "TaskManagementView.h"
#include "AdministrationView.h"
#include "UserManagementView.h"

using namespace std;

int main()
{
	while (AuthenticationService::getLoggedUser() == NULL)
	{
		system("cls");

		char* username;
		char* password;
		
		try 
		{
			while (AuthenticationService::getLoggedUser() == NULL) 
			{
				system("cls");
				cout << "## Login ##" << endl
					<< "Username: ";
				username = Console::ReadLine(20);

				cout << "Password: ";
				password = Console::ReadLine(20);
				AuthenticationService::Authenticate(username, password);
			}
		}
		catch(invalid_argument e)
		{
			cout << e.what() << endl;
			system("pause");
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
	
}

