#include "stdafx.h"
#include "iostream"

#include "AdministrationView.h"
#include "UserManagementView.h"
#include "TaskManagementView.h"

using namespace std;

AdminMenuItems AdministrationView::RenderMenu()
{
	system("cls");
	cout << "## Administration menu ##" << endl
		<< "[U]ser management" << endl
		<< "[T]ask management" << endl
		<< "E[x]it" << endl
		<< "> ";
	char buffer[2];
	cin.getline(buffer, 2);

	switch (toupper(buffer[0]))
	{
	case 'U' :
		return AdminMenuItems::UserManagement;
	case 'T' :
		return AdminMenuItems::TaskManagement;
	case 'X' :
		return AdminMenuItems::AdminExit;
	default :
		return AdminMenuItems::AdminInvalid;
	}
}

void AdministrationView::Run()
{
	while(true)
	{
		AdminMenuItems choice = RenderMenu();

		switch (choice)
		{
		case AdminMenuItems::UserManagement:
		{
			UserManagementView view;
			view.Run();
			break;
		}
		case AdminMenuItems::TaskManagement:
		{
			TaskManagementView view;
			view.Run();
			break;
		}
		case AdminMenuItems::AdminExit:
			return;
		default:
			break;
		}
	}
}

AdministrationView::AdministrationView()
{
}


AdministrationView::~AdministrationView()
{
}

