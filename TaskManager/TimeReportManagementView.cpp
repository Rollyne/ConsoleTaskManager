#include "stdafx.h"
#include "iostream"
#include "Console.h"

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

CRUDMenuItems TimeReportManagementView::RenderMenu()
{
	system("cls");

	TaskRepository* repo = new TaskRepository("tasks.txt");
	TaskManagementView::RenderTask(repo->GetById(this->taskId), AuthenticationService::getLoggedUser()->getId());
	delete repo;

	cout << endl << "## Time Reports Management ##" << endl
		<< "[A]dd" << endl
		<< "[L]ist" << endl
		<< "[E]dit" << endl
		<< "[D]elete" << endl
		<< "E[x]it" << endl
		<< "> ";
	char* buffer;
	try
	{
		buffer = Console::ReadLineMin(1);
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return CRUDMenuItems::Fail;
	}
	

	switch (toupper(buffer[0]))
	{
	case 'A':
		return CRUDMenuItems::Add;
	case 'L':
		return CRUDMenuItems::List;
	case 'E':
		return CRUDMenuItems::Edit;
	case 'D':
		return CRUDMenuItems::Delete;
	case 'X':
		return CRUDMenuItems::Exit;
	default:
		return CRUDMenuItems::Invalid;
	}
}


void TimeReportManagementView::Add()
{
	system("cls");

	TimeReport* newReport = new TimeReport;

	cout << "## Report time spent on task id: " << this->taskId << " ##" << endl
		<< "Time in hours: ";
	
	try
	{
		newReport->setHoursSpent(Console::ReadNumber());
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	newReport->setTaskId(this->taskId);
	newReport->setRepotrterId(AuthenticationService::getLoggedUser()->getId());
	newReport->setTimeOfReport(time(0));

	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");

	repo->Add(newReport);


	delete repo;
	delete newReport;

	system("pause");
}

void TimeReportManagementView::List()
{
	system("cls");

	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");
	UserRepository* userRepo = new UserRepository("users.txt");
	LinkedList<TimeReport>* allReports = repo->GetAll(this->taskId);

	int commentsCount = allReports->Count();

	cout << "## All reports on this task ##" << endl << endl;
	for (int i = 0; i < commentsCount; i++)
	{
		TimeReport* current = allReports->getItemAt(i);
		User* reporter = userRepo->GetById(current->getReporterId());

		cout << "# # # # # # # # # # #" << endl
			<< "Index: " << current->getId() << endl
			<< "Reporter: " << reporter->getFirstName() << " " << reporter->getLastName()
			<< "(" << reporter->getId() << ") "
			<< (reporter->getId() == AuthenticationService::getLoggedUser()->getId() ? "|You|" : "") << endl
			<< "Time reported: ";
		if (current->getHoursSpent() == 1)
			cout << "1 hour" << endl;
		else
			cout << current->getHoursSpent() << " hours" << endl;
		cout << "Date of report: " << current->getTimeOfReport() << endl;
	}

	delete repo;
	delete userRepo;
	delete allReports;

	system("pause");
}

void TimeReportManagementView::Edit()
{
	system("cls");

	TimeReport* updated = new TimeReport();
	TimeReport* outdated = new TimeReport();
	

	cout << "## Update report ##" << endl
		<< "Index of the report: ";
	int buffer;
	try
	{
		buffer = Console::ReadNumber();
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	
	updated->setId(buffer);

	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");


	outdated = repo->GetById(buffer);
	if (outdated != NULL)
	{
		if (outdated->getTaskId() == this->taskId)
		{
			if (outdated->getReporterId() == AuthenticationService::getLoggedUser()->getId())
			{
				
				cout << "Time spent |" << outdated->getHoursSpent() << "| : ";
				try
				{
					buffer = Console::ReadNumber();
				}
				catch (invalid_argument e)
				{
					cout << e.what() << endl;
					system("pause");
					return;
				}

				updated->setHoursSpent(buffer);

				updated->setTaskId(outdated->getTaskId());
				updated->setRepotrterId(outdated->getReporterId());
				updated->setTimeOfReport(time(0));

				repo->Update(updated);
			}
			else
			{
				cout << "You cannot edit this report." << endl;
			}
		}
		else
		{
			cout << "This report doesn't belong to this task." << endl;
		}
	}
	else
	{
		cout << "This report doesn't exist." << endl;
	}

	delete repo;
	delete updated;
	delete outdated;

	system("pause");
}

void TimeReportManagementView::Delete()
{
	system("cls");

	TimeReportRepository* repo = new TimeReportRepository("timereports.txt");
	cout << "## Delete report ##" << endl
		<< "Index of the comment: ";
	int buffer;
	try
	{
		buffer = Console::ReadNumber();
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}

	TimeReport* removed = repo->GetById(buffer);
	if (removed != NULL)
	{
		if (removed->getTaskId() == this->taskId)
		{
			if (removed->getReporterId() == AuthenticationService::getLoggedUser()->getId())
			{
				repo->Delete(removed);

				cout << "Report removed." << endl;
			}
			else
				cout << "You cannot delete this report." << endl;
		}
		else
			cout << "This report doesn't belong to this task." << endl;
	}
	else
	{
		cout << "This report doesn't exist" << endl;
	}

	delete repo;
	delete removed;

	system("pause");
}

void TimeReportManagementView::Run()
{
	while (true)
	{
		CRUDMenuItems choice = RenderMenu();
		switch (choice)
		{
		case CRUDMenuItems::Add:
			Add();
			break;
		case CRUDMenuItems::List:
			List();
			break;
		case CRUDMenuItems::Edit:
			Edit();
			break;
		case CRUDMenuItems::Delete:
			Delete();
			break;
		case CRUDMenuItems::Exit:
			return;
		case CRUDMenuItems::Invalid:
			cout << "Invalid choice" << endl;
			system("pause");
			break;
		}
	}
}
