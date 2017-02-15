#pragma once
#include "MenuItems.h"
class TimeReportManagementView
{
private:
	const int nameMinLength = 3;

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

