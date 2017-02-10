#pragma once
#include "MenuItems.h"
#include "ConsoleValidator.h"
class TimeReportManagementView
{
private:
	const int nameMinLength = 3;
	ConsoleValidator* validate;
	int loggedUserId;

	int taskId;

	void Add();
	void List();
	void Edit();
	void Delete();

	CRUDMenuItems RenderMenu();
public:
	TimeReportManagementView(int taskId);
	~TimeReportManagementView();

	void Run();
};

