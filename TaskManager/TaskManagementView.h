#pragma once
#include "MenuItems.h"
#include "ConsoleValidator.h"
class TaskManagementView
{
private:
	const int nameMinLength = 3;
	ConsoleValidator* validate;

	void Create();
	void List();
	void View();
	void Edit();
	void Delete();

	int loggedUserId;
	CRUDMenuItems RenderMenu();
public:
	TaskManagementView();
	~TaskManagementView();

	void Run();
};

