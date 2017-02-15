#include "stdafx.h"
#include "iostream"
#include "Console.h"
#include <time.h>

#include "TaskManagementView.h"
#include "AuthenticationService.h"
#include "TaskRepository.h"
#include "CommentManagementView.h"
#include "TimeReportManagementView.h"


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

TaskManagementMenuItems TaskManagementView::RenderTaskMenu(Task* task)
{
	system("cls");

	TaskManagementView::RenderTask(task, AuthenticationService::getLoggedUser()->getId());
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

void TaskManagementView::RenderTask(Task* task, int loggedUserId)
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
		<< (executitive->getId() == loggedUserId ? "|You|" : "") << endl;

	cout << "Creator: " << creator->getFirstName() << " " << creator->getLastName()
		<< "(" << creator->getId() << ") "
		<< (creator->getId() == loggedUserId ? "|You|" : "") << endl;

	cout << "Created on: " << task->getTimeOfCreation() << endl
		<< "Last edited on: " << task->getTimeOfLastUpdate() << endl
		<< "Status: " << (task->getStatus() ? "Done" : "In process") << endl;

	delete userRepo;
	delete executitive;
	delete creator;
}


void TaskManagementView::Add()
{
	system("cls");

	Task* newTask = new Task;
	char* buffer;

	cout << "## Create a task ##" << endl
		<< "Header: ";
	try
	{
		buffer = Console::ReadLine(50, nameMinLength);
		newTask->setHeader(buffer);

		cout << "Descirption: ";
		buffer = Console::ReadLine(200, nameMinLength);
		newTask->setDescription(buffer);

		cout << "Measurement(How many hours?): ";
		newTask->setMeasurement(Console::ReadNumber());

		cout << "Executitive's index(Who is going to do it?): ";
		newTask->setExecutitiveId(Console::ReadNumber());
		
		UserRepository* repo = new UserRepository("users.txt");
		if(repo->GetById(newTask->getExecutitiveId()) == NULL)
		{
			cout << "This user doesn't exist." << endl;
			system("pause");
			return;
		}
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	
	newTask->setCreatorId(AuthenticationService::getLoggedUser()->getId());
	newTask->setTimeOfCreation(time(0));
	newTask->setTimeOfLastUpdate(time(0));
	newTask->setStatus(false);

	TaskRepository* repo = new TaskRepository("tasks.txt");

	repo->Add(newTask);


	delete repo;
	delete newTask;

	system("pause");
}

void TaskManagementView::List()
{
	system("cls");

	TaskRepository* repo = new TaskRepository("tasks.txt");
	UserRepository* userRepo = new UserRepository("users.txt");
	LinkedList<Task>* allTasks = repo->GetAll(AuthenticationService::getLoggedUser()->getId());

	int usersCount = allTasks->Count();

	cout << "## All tasks that include you ##" << endl << endl;
	for (int i = 0; i < usersCount; i++)
	{
		cout << "# # # # # # # # # # # #" << endl;
		TaskManagementView::RenderTask(allTasks->getItemAt(i), AuthenticationService::getLoggedUser()->getId());
	}

	delete userRepo;
	delete repo;
	delete allTasks;

	system("pause");
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
		if (target->getCreatorId() == AuthenticationService::getLoggedUser()->getId()
			|| target->getExecutitiveId() == AuthenticationService::getLoggedUser()->getId())
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
					break;
				}
				case TaskManagementMenuItems::TimeReportManagement:
				{
					TimeReportManagementView* repView = new TimeReportManagementView(target->getId());
					repView->Run();
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
	system("cls");

	Task* updated = new Task;
	Task* outdated = new Task;
	char buffer[200];

	cout << "## Update task ##" << endl
		<< "Index of the task: ";
	try
	{
		int index = Console::ReadNumber();
		updated->setId(Console::ReadNumber());

		TaskRepository* repo = new TaskRepository("tasks.txt");
		outdated = repo->GetById(index);
		if (outdated != NULL)
		{
			if (AuthenticationService::getLoggedUser()->getId() == outdated->getCreatorId()) {
				cout << "* Header *" << endl
					<< outdated->getHeader() << endl
					<< "> ";
				Console::ReadLine(50, nameMinLength);
				updated->setHeader(buffer);

				cout << "* Description *" << endl
					<< outdated->getDescription() << endl
					<< "> ";
				Console::ReadLine(200, nameMinLength);
				updated->setDescription(buffer);

				cout << "Measurment |" << outdated->getMeasurement() << "| : ";
				updated->setMeasurement(Console::ReadNumber());

				cout << "Executitive's index |" << outdated->getExecutitiveId() << "| : ";
				updated->setExecutitiveId(Console::ReadNumber());

				updated->setCreatorId(outdated->getCreatorId());
				updated->setTimeOfCreation(outdated->getRawTimeOfCreation());
				updated->setTimeOfLastUpdate(time(0));
				updated->setStatus(outdated->getStatus());

				repo->Update(updated);
			}
			else
			{
				cout << "You cannot edit this task." << endl;
			}
		}
		else
		{
			cout << "This task doesn't exist." << endl;
		}
		delete repo;
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	

	delete updated;
	delete outdated;

	system("pause");
}

void TaskManagementView::Delete()
{
	system("cls");

	TaskRepository* repo = new TaskRepository("tasks.txt");
	cout << "## Delete task ##" << endl
		<< "Index of the task: ";
	Task* removed;
	try
	{
		removed = repo->GetById(Console::ReadNumber());
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	if (removed != NULL) 
	{
		if (AuthenticationService::getLoggedUser()->getId() == removed->getCreatorId())
		{
			repo->Delete(removed);
			cout << "Task removed." << endl;
		}
		else
		{
			cout << "You cannot delete this task." << endl;
		}
	}
	else
	{
		cout << "This task doesn't exist" << endl;
	}
	
	delete repo;
	delete removed;

	system("pause");
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


