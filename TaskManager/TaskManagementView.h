#pragma once
#include "MenuItems.h"
#include "Task.h"
#include "UserManagementView.h"

class TaskManagementView : public BaseView<Task>
{
protected:

	Task* inputItem() override;
	void updateItem(Task* outdated) override;
	

	bool hasAccess(Task* item) override;

	void Add() override;
	void List() override;
	void View();
	void Edit() override;
	void Delete() override;
	void UpdateStatus();

	CRUDMenuItems RenderMenu() override;
	TaskManagementMenuItems RenderTaskMenu(Task* task);
public:
	TaskManagementView();
	~TaskManagementView();

	void printItem(Task* item) override;
	void Run();
};

