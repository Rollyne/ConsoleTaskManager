#include "stdafx.h"
#include "iostream"
#include "Console.h"
#include <time.h>

#include "TaskManagementView.h"
#include "AuthenticationService.h"
#include "TaskRepository.h"
#include "CommentManagementView.h"
#include "TimeReportManagementView.h"
#include "UserRepository.h"


using namespace std;

TaskManagementView::TaskManagementView()
{
}


TaskManagementView::~TaskManagementView()
{
}


CRUDMenuItems TaskManagementView::RenderMenu()
{
	system("cls");

	cout << "## Tasks Management ##" << endl
		<< "[A]dd" << endl
		<< "[L]ist" << endl
		<< "[V]iew" << endl
		<< "[E]dit" << endl
		<< "[U]pdate status" << endl
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
	case 'V':
		return CRUDMenuItems::View;
	case 'E':
		return CRUDMenuItems::Edit;
	case 'U':
		return CRUDMenuItems::UpdateStatus;
	case 'D':
		return CRUDMenuItems::Delete;
	case 'X':
		return CRUDMenuItems::Exit;
	default:
		return CRUDMenuItems::Invalid;
	}
}

void TaskManagementView::printItem(Task* task)
{

	UserRepository* userRepo = new UserRepository("users.txt");

	User* executitive = userRepo->GetById(task->getExecutitiveId());
	User* creator = userRepo->GetById(task->getCreatorId());

	cout.setf(ios::boolalpha);
	cout << "Index: " << task->getId() << endl
		<< "Header: " << task->getHeader() << endl
		<< "Description: " << task->getDescription() << endl
		<< "Measurment: ";
	if (task->getMeasurement() == 1)
		cout << "1 hour" << endl;
	else
		cout << task->getMeasurement() << " hours" << endl;

	cout << "Executitive: " << executitive->getFirstName() << " " << executitive->getLastName()
		<< "(" << executitive->getId() << ") "
		<< (executitive->getId() == AuthenticationService::getLoggedUser()->getId() ? "|You|" : "") << endl;

	cout << "Creator: " << creator->getFirstName() << " " << creator->getLastName()
		<< "(" << creator->getId() << ") "
		<< (creator->getId() == AuthenticationService::getLoggedUser()->getId() ? "|You|" : "") << endl;

	cout << "Created on: " << task->getTimeOfCreation() << endl
		<< "Last edited on: " << task->getTimeOfLastUpdate() << endl
		<< "Status: " << (task->getStatus() ? "Done" : "In process") << endl;

	delete userRepo;
	delete executitive;
	delete creator;
}

bool TaskManagementView::hasAccess(Task* item)
{
	if (AuthenticationService::getLoggedUser()->getId() == item->getCreatorId())
		return true;
	return false;

}

Task* TaskManagementView::inputItem()
{
	system("cls");

	Task* newTask = new Task;
	char* buffer;

	buffer = Console::ReadLine(50, textFieldMinLength);
	newTask->setHeader(buffer);

	cout << "Descirption: ";
	buffer = Console::ReadLine(200, textFieldMinLength);
	newTask->setDescription(buffer);

	cout << "Measurement(How many hours?): ";
	newTask->setMeasurement(Console::ReadNumber());

	cout << "Executitive's index(Who is going to do it?): ";
	newTask->setExecutitiveId(Console::ReadNumber());

	UserRepository* repo = new UserRepository("users.txt");
	if (repo->GetById(newTask->getExecutitiveId()) == NULL)
	{
		cout << "This user doesn't exist." << endl;
		system("pause");
		return NULL;
	}

	newTask->setCreatorId(AuthenticationService::getLoggedUser()->getId());
	newTask->setTimeOfCreation(time(0));
	newTask->setTimeOfLastUpdate(time(0));
	newTask->setStatus(false);

	return newTask;
}

void TaskManagementView::updateItem(Task* item)
{
	char* buffer;

	cout << "* Header *" << endl
		<< item->getHeader() << endl
		<< "> ";
	buffer = Console::ReadLine(50, textFieldMinLength);
	item->setHeader(buffer);

	cout << "* Description *" << endl
		<< item->getDescription() << endl
		<< "> ";
	buffer = Console::ReadLine(200, textFieldMinLength);
	item->setDescription(buffer);

	cout << "Measurment |" << item->getMeasurement() << "| : ";
	item->setMeasurement(Console::ReadNumber());

	cout << "Executitive's index |" << item->getExecutitiveId() << "| : ";
	item->setExecutitiveId(Console::ReadNumber());

	item->setTimeOfLastUpdate(time(0));
}


TaskManagementMenuItems TaskManagementView::RenderTaskMenu(Task* task)
{
	system("cls");

	printItem(task);
	cout <<endl<< "## Task Properties ##" << endl
		<< "[C]omments" << endl
		<< "[T]ime Report" << endl
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
		return TaskManagementMenuItems::TaskManagementFail;
	}

	switch (toupper(buffer[0]))
	{
	case 'C' :
		return TaskManagementMenuItems::CommentManagement;
	case 'T':
		return TaskManagementMenuItems::TimeReportManagement;
	case 'X':
		return TaskManagementMenuItems::TaskManagementExit;
	default :
		break;
	}
}


void TaskManagementView::Add()
{
	auto* repo = new TaskRepository("tasks.txt");
	_add(repo);
	delete repo;
}


void TaskManagementView::List()
{
	auto* repo = new TaskRepository("tasks.txt");
	_list(repo);
	delete repo;
}

void TaskManagementView::View()
{
	system("cls");

	cout << "## View task ##" << endl
		<< "Task index: ";
	int index;
	try
	{
		index = Console::ReadNumber();
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
	}

	TaskRepository* repo = new TaskRepository("tasks.txt");
	Task* target = repo->GetById(index);
	if (target != NULL)
	{
		if (hasAccess(target) || target->getExecutitiveId() == AuthenticationService::getLoggedUser()->getId())
		{
			while (true)
			{
				TaskManagementMenuItems choice = RenderTaskMenu(target);
				switch (choice)
				{
				case TaskManagementMenuItems::CommentManagement:
				{
					CommentManagementView* commView = new CommentManagementView(target->getId());
					commView->Run();
					delete commView;
					break;
				}
				case TaskManagementMenuItems::TimeReportManagement:
				{
					TimeReportManagementView* repView = new TimeReportManagementView(target->getId());
					repView->Run();
					delete repView;
					break;
				}
				case TaskManagementMenuItems::TaskManagementExit:
					return;
				default: 
				{
					cout << "Invalid choice." << endl;
					system("pause");
					break;
				}
				}
			}
		}
		else
		{
			cout << "You cannot view this task." << endl;
			system("pause");
		}
	}
	else
	{
		cout << "This task doesn't exist." << endl;
		system("pause");
	}

	delete repo;
	delete target;
}

void TaskManagementView::Edit()
{
	auto* repo = new TaskRepository("tasks.txt");
	_edit(repo);
	delete repo;
}

void TaskManagementView::Delete()
{
	auto* repo = new TaskRepository("tasks.txt");
	_delete(repo);
	delete repo;
}

void TaskManagementView::UpdateStatus()
{
	system("cls");
	cout << "## Update task's status ##" << endl
		<< "Task's index: ";
	TaskRepository* repo = new TaskRepository("tasks.txt");
	try
	{
		Task* task = repo->GetById(Console::ReadNumber());
		if (task != NULL) {
			if (task->getCreatorId() == AuthenticationService::getLoggedUser()->getId())
			{
				if (task->getStatus())
				{
					char* buffer = Console::ReadLineMin(1);
					cout << "The task is said to be completed, do you want put it in process (Y/N)?" << endl
						<< "> ";
					if (buffer[0] == 'Y')
					{
						task->setStatus(false);
						repo->Update(task);
						cout << "The task is now in process. You have to comment on this change." << endl;
						system("pause");
						CommentManagementView* view = new CommentManagementView(task->getId());
						view->Add();
					}
				}
				else
				{
					cout << "The task is said to be in process so you cannot change its status." << endl;
					system("pause");
				}
			}
			else if (task->getExecutitiveId() == AuthenticationService::getLoggedUser()->getId())
			{
				if (!task->getStatus())
				{
					char* buffer = Console::ReadLineMin(1);
					cout << "The task is said to be in process, do you want set it as completed (Y/N)?" << endl
						<< "> ";
					if (buffer[0] == 'Y')
					{
						task->setStatus(true);
						repo->Update(task);
						cout << "The task is now completed. You have to comment on this change." << endl;
						system("pause");
						CommentManagementView* view = new CommentManagementView(task->getId());
						view->Add();
					}
				}
				else
				{
					cout << "The task is said to be completed so you cannot change its status." << endl;
					system("pause");
				}
			}
			else
			{
				cout << "You cannot change this task's status." << endl;
				system("pause");
			}
		}
		else
		{
			cout << "This task doesn't exist." << endl;
			system("pause");
		}
		delete task;
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	

	delete repo;
}

void TaskManagementView::Run()
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
		case CRUDMenuItems::View:
			View();
			break;
		case CRUDMenuItems::Edit:
			Edit();
			break;
		case CRUDMenuItems::UpdateStatus:
			UpdateStatus();
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
		default : break;
		}
	}
}


