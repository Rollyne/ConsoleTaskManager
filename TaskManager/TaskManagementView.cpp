#include "stdafx.h"
#include "iostream"

#include "TaskManagementView.h"
#include "AuthenticationService.h"
#include "TaskRepository.h"

using namespace std;

TaskManagementView::TaskManagementView()
{
	this->loggedUserId = AuthenticationService::getLoggedUser()->getId();
}


TaskManagementView::~TaskManagementView()
{
}

CRUDMenuItems TaskManagementView::RenderMenu()
{
	system("cls");

	cout << "## Tasks Management ##" << endl
		<< "[C]reate" << endl
		<< "[L]ist" << endl
		//<< "[V]iew" << endl
		<< "[E]dit" << endl
		<< "[D]elete" << endl
		<< "E[x]it" << endl
		<< "> ";
	char buffer[2];
	cin.getline(buffer, 2);

	switch (toupper(buffer[0]))
	{
	case 'C':
		return CRUDMenuItems::Create;
	case 'L':
		return CRUDMenuItems::List;
	//case 'V':
		//return CRUDMenuItems::View;
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


void TaskManagementView::Create()
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
	LinkedList<Task>* allUsers = repo->GetAll(this->loggedUserId);

	int usersCount = allUsers->Count();

	cout << "## All tasks that include you ##" << endl << endl;
	for (int i = 0; i < usersCount; i++)
	{
		Task* current = allUsers->getItemAt(i);
		User* executitive = userRepo->GetById(current->getExecutitiveId());
		User* creator = userRepo->GetById(current->getCreatorId());

		cout.setf(ios::boolalpha);
		cout << "# # # # # # # # # # #" << endl
			<< "Index: " << current->getId() << endl
			<< "Header: " << current->getHeader() << endl
			<< "Description: " << current->getDescription() << endl
			<< "Measurment: ";
		if (current->getMeasurement() == 1)
			cout << "1 hour" << endl;
		else
			cout << current->getMeasurement() << " hours" << endl;

		cout << "Executitive: " << executitive->getFirstName() << " " << executitive->getLastName()
			<< "(" << executitive->getId() << ") "
			<< (executitive->getId() == this->loggedUserId ? "|You|" : "") << endl;

		cout << "Creator: " << creator->getFirstName() << " " << creator->getLastName()
			<< "(" << creator->getId() << ") "
			<< (creator->getId() == this->loggedUserId ? "|You|" : "") << endl;

		char* test = current->getTimeOfCreation();
		cout << test << endl;
		cout << "Created on: " << current->getTimeOfCreation() << endl
			<< "Last edited on: " << current->getTimeOfLastUpdate() << endl
			<< "Status: " << (current->getStatus() ? "Done" : "In process") << endl;

	}

	delete userRepo;
	delete repo;
	delete allUsers;

	system("pause");
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

	if (this->loggedUserId == outdated->getCreatorId()) {
		cout << "* Header *" << endl
			<< outdated->getHeader() << endl
			<< "> ";
		cin.getline(buffer, 50);
		updated->setHeader(buffer);

		cout << "* Description *" << endl
			<< outdated->getDescription() << endl
			<< "> ";
		cin.getline(buffer, 200);
		updated->setDescription(buffer);

		cout << "Measurment |" << outdated->getMeasurement() << "| : ";
		cin.getline(buffer, 20);
		updated->setMeasurement(atoi(buffer));

		cout << "Executitive's index |" << outdated->getExecutitiveId() << "| : ";
		cin.getline(buffer, 20);
		updated->setExecutitiveId(atoi(buffer));

		cout.setf(ios::boolalpha);
		cout << "Is it completed |" << outdated->getStatus() << "| (Y/N): ";
		cin.getline(buffer, 20);
		if (toupper(buffer[0]) == 'Y')
			updated->setStatus(true);
		else
			updated->setStatus(false);

		updated->setCreatorId(outdated->getCreatorId());
		updated->setTimeOfCreation(outdated->getRawTimeOfCreation());
		updated->setTimeOfLastUpdate(time(0));

		repo->Update(updated);
	}
	else 
	{
		cout << "You cannot edit this task." << endl;
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
	if (this->loggedUserId == removed->getCreatorId())
	{
		repo->Delete(removed);
		cout << "Task removed." << endl;
	}
	else 
	{
		cout << "You cannot delete this task." << endl;
	}
	
	delete repo;
	delete removed;

	system("pause");
}

void TaskManagementView::Run()
{
	while (true)
	{
		CRUDMenuItems choice = RenderMenu();
		switch (choice)
		{
		case CRUDMenuItems::Create:
			Create();
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
