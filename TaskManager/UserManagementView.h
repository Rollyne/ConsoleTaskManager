#pragma once
#include "MenuItems.h"
#include "ConsoleValidator.h"
class UserManagementView
{
private:
	const int nameMinLength = 3;
	ConsoleValidator* validate;

	void Create();
	void List();
	void Update();
	void Delete();

	CRUDMenuItems RenderMenu();
public:
	UserManagementView();
	~UserManagementView();

	void Run();
};

