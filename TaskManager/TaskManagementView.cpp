#include "stdafx.h"
#include "iostream"

#include "TaskManagementView.h"
#include "AuthenticationService.h"
#include "TaskRepository.h"
#include "CommentManagementView.h"
#include "TimeReportManagementView.h"


using namespace std;

TaskManagementView::TaskManagementView()
{
	validate = new ConsoleValidator();
	this->loggedUserId = AuthenticationService::getLoggedUser()->getId();
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
	char buffer[2];
	cin.getline(buffer, 2);

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

	TaskManagementView::RenderTask(task, this->loggedUserId);
	cout <<endl<< "## Task Properties ##" << endl
		<< "[C]omments" << endl
		<< "[T]ime Report" << endl
		<< "E[x]it" << endl
		<< "> ";
	char buffer[2];
	cin.getline(buffer, 2);

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

	char* test = task->getTimeOfCreation();
	cout << test << endl;
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
	char buffer[200];

	cout << "## Create a task ##" << endl
		<< "Header: ";
	cin.getline(buffer, 50, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newTask->setHeader(buffer);

	cout << "Descirption: ";
	cin.getline(buffer, 200, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newTask->setDescription(buffer);

	cout << "Measurement(How many hours?): ";
	cin.getline(buffer, 20, '\n');

	newTask->setMeasurement(atoi(buffer));

	cout << "Executitive's index(Who is going to do it?): ";
	cin.getline(buffer, 20, '\n');
	newTask->setExecutitiveId(atoi(buffer));

	newTask->setCreatorId(this->loggedUserId);
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
	LinkedList<Task>* allTasks = repo->GetAll(this->loggedUserId);

	int usersCount = allTasks->Count();

	cout << "## All tasks that include you ##" << endl << endl;
	for (int i = 0; i < usersCount; i++)
	{
		cout << "# # # # # # # # # # # #" << endl;
		TaskManagementView::RenderTask(allTasks->getItemAt(i), this->loggedUserId);
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
	char buffer[20];
	cin.getline(buffer, 20);

	TaskRepository* repo = new TaskRepository("tasks.txt");
	Task* target = repo->GetById(atoi(buffer));
	if (target != NULL)
	{
		if (target->getCreatorId() == this->loggedUserId || target->getExecutitiveId() == this->loggedUserId)
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
	cin.getline(buffer, 20);
	updated->setId(atoi(buffer));
	
	TaskRepository* repo = new TaskRepository("tasks.txt");
	outdated = repo->GetById(atoi(buffer));
	if (outdated != NULL)
	{
		if (this->loggedUserId == outdated->getCreatorId()) {
			cout << "* Header *" << endl
				<< outdated->getHeader() << endl
				<< "> ";
			cin.getline(buffer, 50);
			if (!validate->IsMinLength(buffer, nameMinLength))
				return;
			updated->setHeader(buffer);

			cout << "* Description *" << endl
				<< outdated->getDescription() << endl
				<< "> ";
			cin.getline(buffer, 200);
			if (!validate->IsMinLength(buffer, nameMinLength))
				return;
			updated->setDescription(buffer);

			cout << "Measurment |" << outdated->getMeasurement() << "| : ";
			cin.getline(buffer, 20);
			updated->setMeasurement(atoi(buffer));

			cout << "Executitive's index |" << outdated->getExecutitiveId() << "| : ";
			cin.getline(buffer, 20);
			updated->setExecutitiveId(atoi(buffer));

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
	delete updated;
	delete outdated;

	system("pause");
}

void TaskManagementView::Delete()
{
	system("cls");

	char buffer[20];

	TaskRepository* repo = new TaskRepository("tasks.txt");
	cout << "## Delete task ##" << endl
		<< "Index of the task: ";
	cin.getline(buffer, 20);
	Task* removed = repo->GetById(atoi(buffer));
	if (removed != NULL) 
	{
		if (this->loggedUserId == removed->getCreatorId())
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
	char buffer[20];
	cin.getline(buffer, 20);

	TaskRepository* repo = new TaskRepository("tasks.txt");
	
	Task* task = repo->GetById(atoi(buffer));
	if (task != NULL) {
		if (task->getCreatorId() == this->loggedUserId)
		{
			if (task->getStatus())
			{
				cout << "The task is said to be completed, do you want put it in process (Y/N)?" << endl
					<< "> ";
				cin.getline(buffer, 20);
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
		else if (task->getExecutitiveId() == this->loggedUserId)
		{
			if (!task->getStatus())
			{
				cout << "The task is said to be in process, do you want set it as completed (Y/N)?" << endl
					<< "> ";
				cin.getline(buffer, 20);
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
		cout << "This task doesn't exist.";
		system("pause");
	}

	delete repo;
	delete task;
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


