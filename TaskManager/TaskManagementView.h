#pragma once
#include "MenuItems.h"
#include "Task.h"
class TaskManagementView
{
private:
	const int nameMinLength = 3;

	void Add();
	void List();
	void View();
	void Edit();
	void Delete();
	void UpdateStatus();

	CRUDMenuItems RenderMenu();
	TaskManagementMenuItems RenderTaskMenu(Task* task);
public:
	TaskManagementView();
	~TaskManagementView();

	void Run();
	static void RenderTask(Task* task, int loggedUserId);
};

