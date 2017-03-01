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
	TaskManagementView view;
	view.printItem(repo->GetById(this->taskId));
	delete repo;
	
	return BaseView<Comment>::RenderMenu();
}

bool CommentManagementView::hasAccess(class Comment* item)
{
	if (item->getAuthorId() == AuthenticationService::getLoggedUser()->getId())
		return true;
	return false;
}
bool CommentManagementView::doesBelong(Comment* item)
{
	if (item->getTaskId() == taskId)
		return true;
	return false;
}

Comment* CommentManagementView::inputItem()
{
	Comment* newComment = new Comment;
	char* buffer;

		cout << "Body: ";
	try
	{
		buffer = Console::ReadLine(200, textFieldMinLength);
		newComment->setBody(buffer);
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
	}

	newComment->setTaskId(this->taskId);
	newComment->setAuthorId(AuthenticationService::getLoggedUser()->getId());

	return newComment; // should we delete the pointer somehow ?
}

void CommentManagementView::updateItem(Comment* item)
{
	char* buffer;
	cout << "* Body *" << endl
		<< item->getBody() << endl
		<< "> ";
	try
	{
		buffer = Console::ReadLine(200, textFieldMinLength);
		item->setBody(buffer);
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
	}
}

void CommentManagementView::printItem(class Comment* item)
{
	UserRepository* userRepo = new UserRepository("users.txt");
	User* author = userRepo->GetById(item->getAuthorId());

	cout << "Index: " << item->getId() << endl
		<< "Author: " << author->getFirstName() << " " << author->getLastName()
		<< "(" << author->getId() << ") "
		<< (author->getId() == AuthenticationService::getLoggedUser()->getId() ? "|You|" : "") << endl
		<< item->getBody() << endl;

	delete author;
	delete userRepo;
}

void CommentManagementView::Add()
{
	CommentRepository* repo = new CommentRepository("comments.txt");
	_add(repo);
	delete repo;
}

void CommentManagementView::List()
{
	CommentRepository* repo = new CommentRepository("comments.txt");
	_list(repo);
	delete repo;
}

void CommentManagementView::Edit()
{
	CommentRepository* repo = new CommentRepository("comments.txt");
	_edit(repo);
	delete repo;
}

void CommentManagementView::Delete()
{
	CommentRepository* repo = new CommentRepository("comments.txt");
	_delete(repo);
	delete repo;
}
