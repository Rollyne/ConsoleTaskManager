#pragma once
#include "MenuItems.h"
#include "ConsoleValidator.h"
class CommentManagementView
{
private:
	const int nameMinLength = 3;
	ConsoleValidator* validate;
	int loggedUserId;

	int taskId;

	void Add();
	void List();
	void Edit();
	void Delete();

	CRUDMenuItems RenderMenu();
public:
	CommentManagementView(int taskId);
	~CommentManagementView();

	void Run();
};

