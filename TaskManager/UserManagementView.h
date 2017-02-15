#pragma once
#include "MenuItems.h"
class UserManagementView
{
private:
	const int nameMinLength = 3;

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

