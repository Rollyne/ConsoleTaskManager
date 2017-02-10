#pragma once
#include "MenuItems.h"
#include "ConsoleValidator.h"
#include "Task.h"
class TaskManagementView
{
private:
	const int nameMinLength = 3;
	ConsoleValidator* validate;

	void Add();
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
	static void RenderTask(Task* task, int loggedUserId);
};

