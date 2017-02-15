#include "stdafx.h"
#include "iostream"
#include "Console.h"

#include "CommentManagementView.h"
#include "CommentRepository.h"
#include "AuthenticationService.h"
#include "TaskManagementView.h"
#include "TaskRepository.h"


using namespace std;

CommentManagementView::CommentManagementView(int taskId)
{
	this->taskId = taskId;
}


CommentManagementView::~CommentManagementView()
{
}

CRUDMenuItems CommentManagementView::RenderMenu()
{
	system("cls");

	TaskRepository* repo = new TaskRepository("tasks.txt");	
	TaskManagementView::RenderTask(repo->GetById(this->taskId), AuthenticationService::getLoggedUser()->getId());
	delete repo;
	
	cout << endl << "## Comments Management ##" << endl
		<< "[A]dd" << endl
		<< "[L]ist" << endl
		<< "[E]dit" << endl
		<< "[D]elete" << endl
		<< "E[x]it" << endl
		<< "> " ;
	char* buffer;
	try
	{
		buffer = Console::ReadLineMin(1);
	}
	catch(invalid_argument e)
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
	default :
		return CRUDMenuItems::Invalid;
	}
}


void CommentManagementView::Add()
{
	system("cls");

	Comment* newComment = new Comment;
	char* buffer;

	cout << "## Add a comment ##" << endl
		<< "Body: ";
	try
	{
		buffer = Console::ReadLine(200, nameMinLength);
	}
	catch(invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	newComment->setBody(buffer);

	newComment->setTaskId(this->taskId);
	newComment->setAuthorId(AuthenticationService::getLoggedUser()->getId());

	CommentRepository* repo = new CommentRepository("comments.txt");
	
	repo->Add(newComment);


	delete repo;
	delete newComment;

	system("pause");
}

void CommentManagementView::List()
{
	system("cls");

	CommentRepository* repo = new CommentRepository("comments.txt");
	UserRepository* userRepo = new UserRepository("users.txt");
	LinkedList<Comment>* allComments = repo->GetAll(this->taskId);

	int commentsCount = allComments->Count();

	cout << "## All comments ##" << endl << endl;
	for (int i = 0; i < commentsCount; i++)
	{
		Comment* current = allComments->getItemAt(i);
		User* author = userRepo->GetById(current->getAuthorId());

		cout << "# # # # # # # # # # #" << endl
			<< "Index: " << current->getId() << endl
			<< "Author: " << author->getFirstName() << " " << author->getLastName()
			<< "(" << author->getId() << ") "
			<< (author->getId() == AuthenticationService::getLoggedUser()->getId() ? "|You|" : "") << endl
			<< current->getBody() << endl;
	}

	delete repo;
	delete userRepo;
	delete allComments;
	
	system("pause");
}

void CommentManagementView::Edit()
{
	system("cls");
	
	Comment* updated = new Comment;

	cout << "## Update comment ##" << endl
		<< "Index of the comment: ";
	int index;
	try
	{
		index = Console::ReadNumber();
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	updated->setId(index);

	CommentRepository* repo = new CommentRepository("comments.txt");
	

	Comment* outdated = repo->GetById(index);
	if (outdated != NULL) 
	{
		if (outdated->getTaskId() == this->taskId)
		{
			if (outdated->getAuthorId() == AuthenticationService::getLoggedUser()->getId())
			{
				char* buffer;
				cout << "* Body *" << endl
					<< outdated->getBody() << endl
					<< "> ";
				try
				{
					buffer = Console::ReadLine(200, nameMinLength);
				}
				catch (invalid_argument e)
				{
					cout << e.what() << endl;
					system("pause");
					return;
				}
				updated->setBody(buffer);

				updated->setTaskId(outdated->getTaskId());
				updated->setAuthorId(outdated->getAuthorId());

				repo->Update(updated);
			}
			else
			{
				cout << "You cannot edit this comment." << endl;
			}
		}
		else
		{
			cout << "This comment doesn't belong to this task." << endl;
		}
	}
	else
	{
		cout << "This comment doesn't exist." << endl;
	}

	delete repo;
	delete updated;
	delete outdated;

	system("pause");
}

void CommentManagementView::Delete()
{
	system("cls");

	CommentRepository* repo = new CommentRepository("comments.txt");
	cout << "## Delete comment ##" << endl
		<< "Index of the comment: ";
	int index;
	try
	{
		index = Console::ReadNumber();
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	Comment* removed = repo->GetById(index);
	if (removed != NULL)
	{
		if (removed->getTaskId() == this->taskId)
		{
			if (removed->getAuthorId() == AuthenticationService::getLoggedUser()->getId())
			{
				repo->Delete(removed);

				cout << "Comment removed." << endl;
			}
			else
				cout << "You cannot delete this comment." << endl;
		}
		else
			cout << "This comment doesn't belong to this task." << endl;
	}
	else
	{
		cout << "This comment doesn't exist" << endl;
	}

	delete repo;
	delete removed;

	system("pause");
}

void CommentManagementView::Run()
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
