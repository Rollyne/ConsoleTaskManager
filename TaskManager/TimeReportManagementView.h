#pragma once
#include "MenuItems.h"
#include "TimeReport.h"
#include "UserManagementView.h"

class TimeReportManagementView :public BaseView<TimeReport>
{
protected:
	int taskId;

	TimeReport* inputItem() override;
	void updateItem(TimeReport* item) override;
	void printItem(TimeReport* item) override;

	bool hasAccess(TimeReport* item) override;
	bool doesBelong(TimeReport* item) override;

	void Add() override;
	void List() override;
	void Edit() override;
	void Delete() override;

	CRUDMenuItems RenderMenu() override;
public:
	explicit TimeReportManagementView(int taskId);
	~TimeReportManagementView();
};

