#pragma once
#include "MenuItems.h"
#include "ConsoleValidator.h"
class UserManagementView
{
private:
	const int nameMinLength = 3;
	ConsoleValidator* validate;

	void Add();
	void List();
	void Edit();
	void Delete();

	CRUDMenuItems RenderMenu();
public:
	UserManagementView();
	~UserManagementView();

	void Run();
};

