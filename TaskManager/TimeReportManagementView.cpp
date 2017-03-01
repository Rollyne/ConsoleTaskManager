#include "stdafx.h"
#include "iostream"
#include "Console.h"
#include <time.h>

#include "TimeReportManagementView.h"
#include "TimeReportRepository.h"
#include "AuthenticationService.h"
#include "TaskManagementView.h"
#include "TaskRepository.h"


using namespace std;

TimeReportManagementView::TimeReportManagementView(int taskId)
{
	this->taskId = taskId;
}


TimeReportManagementView::~TimeReportManagementView()
{
}

CRUDMenuItems TimeReportManagementView::RenderMenu() // The same as CommentView's function. How to inherit it ?
{
	system("cls");

	TaskRepository* repo = new TaskRepository("tasks.txt");
	TaskManagementView view;
	view.printItem(repo->GetById(this->taskId));
	delete repo;

	return BaseView<TimeReport>::RenderMenu();
}

void TimeReportManagementView::printItem(TimeReport* item)
{
	UserRepository* userRepo = new UserRepository("users.txt");
	User* reporter = userRepo->GetById(item->getReporterId());


	cout << "Index: " << item->getId() << endl
		<< "Reporter: " << reporter->getFirstName() << " " << reporter->getLastName()
		<< "(" << reporter->getId() << ") "
		<< (reporter->getId() == AuthenticationService::getLoggedUser()->getId() ? "|You|" : "") << endl
		<< "Time reported: ";
	if (item->getHoursSpent() == 1)
		cout << "1 hour" << endl;
	else
		cout << item->getHoursSpent() << " hours" << endl;
	cout << "Date of report: " << item->getTimeOfReport() << endl;

	delete reporter;
	delete userRepo;
}

bool TimeReportManagementView::hasAccess(TimeReport* item)
{
	if (item->getReporterId() == AuthenticationService::getLoggedUser()->getId())
		return true;
	return false;
}
bool TimeReportManagementView::doesBelong(TimeReport* item)
{
	if (item->getTaskId() == taskId)
		return true;
	return false;
}

TimeReport* TimeReportManagementView::inputItem()
{
	TimeReport* newReport = new TimeReport;

	cout << "## Report time spent on task id: " << this->taskId << " ##" << endl
		<< "Time in hours: ";

	newReport->setHoursSpent(Console::ReadNumber());

	newReport->setTaskId(this->taskId);
	newReport->setRepotrterId(AuthenticationService::getLoggedUser()->getId());
	newReport->setTimeOfReport(time(0));

	return newReport;
}

void TimeReportManagementView::updateItem(TimeReport* item)
{
	cout << "Time spent |" << item->getHoursSpent() << "| : ";

	item->setHoursSpent(Console::ReadNumber());

	item->setTimeOfReport(time(0));
}

void TimeReportManagementView::Add()
{
	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");
	_add(repo);
	delete repo;
}

void TimeReportManagementView::List()
{
	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");
	_list(repo);
	delete repo;
}

void TimeReportManagementView::Edit()
{
	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");
	_edit(repo);
	delete repo;
}

void TimeReportManagementView::Delete()
{
	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");
	_delete(repo);
	delete repo;
}
