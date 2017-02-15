#pragma once
#include "MenuItems.h"
class CommentManagementView
{
private:
	const int nameMinLength = 3;

	int taskId;

	void List();
	void Edit();
	void Delete();

	CRUDMenuItems RenderMenu();
public:
	void Add();
	CommentManagementView(int taskId);
	~CommentManagementView();

	void Run();
};

