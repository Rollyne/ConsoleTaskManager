#include "stdafx.h"
#include "iostream"

#include "CommentManagementView.h"
#include "CommentRepository.h"
#include "AuthenticationService.h"
#include "TaskManagementView.h"
#include "TaskRepository.h"


using namespace std;

CommentManagementView::CommentManagementView(int taskId)
{
	this->taskId = taskId;
	this->loggedUserId = AuthenticationService::getLoggedUser()->getId();
}


CommentManagementView::~CommentManagementView()
{
}

CRUDMenuItems CommentManagementView::RenderMenu()
{
	system("cls");

	TaskRepository* repo = new TaskRepository("tasks.txt");	
	TaskManagementView::RenderTask(repo->GetById(this->taskId), this->loggedUserId);
	delete repo;
	
	cout << endl << "## Comments Management ##" << endl
		<< "[A]dd" << endl
		<< "[L]ist" << endl
		<< "[E]dit" << endl
		<< "[D]elete" << endl
		<< "E[x]it" << endl
		<< "> " ;
	char buffer[2];
	cin.getline(buffer, 2);

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
	char buffer[200];

	cout << "## Add a comment ##" << endl
		<< "Body: ";
	cin.getline(buffer, 200, '\n');
	if (!validate->IsMinLength(buffer, nameMinLength))
		return;
	newComment->setBody(buffer);

	newComment->setTaskId(this->taskId);
	newComment->setAuthorId(this->loggedUserId);

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
			<< (author->getId() == this->loggedUserId ? "|You|" : "") << endl
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
	Comment* outdated = new Comment;
	char buffer[20];

	cout << "## Update comment ##" << endl
		<< "Index of the comment: ";
	cin.getline(buffer, 20);
	updated->setId(atoi(buffer));

	CommentRepository* repo = new CommentRepository("comments.txt");
	

	outdated = repo->GetById(atoi(buffer));
	if (outdated != NULL) 
	{
		if (outdated->getTaskId() == this->taskId)
		{
			if (outdated->getAuthorId() == this->loggedUserId) 
			{
				char buffer[200];
				cout << "* Body *" << endl
					<< outdated->getBody() << endl
					<< "> ";
				cin.getline(buffer, 200);
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

	char buffer[20];

	

	CommentRepository* repo = new CommentRepository("comments.txt");
	cout << "## Delete comment ##" << endl
		<< "Index of the comment: ";
	cin.getline(buffer, 20);
	Comment* removed = repo->GetById(atoi(buffer));
	if (removed != NULL)
	{
		if (removed->getTaskId() == this->taskId)
		{
			if (removed->getAuthorId() == this->loggedUserId)
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
