#pragma once
#include "MenuItems.h"
#include "UserManagementView.h"
#include "Comment.h"

class CommentManagementView : public BaseView<Comment>
{
protected:
	int taskId;

	Comment* inputItem() override;
	void updateItem(Comment* item) override;
	void printItem(Comment* item) override;

	bool hasAccess(Comment* item) override;
	bool doesBelong(Comment* item) override;

	void List() override;
	void Edit() override;
	void Delete() override;

	CRUDMenuItems RenderMenu() override;
public:
	void Add() override;
	explicit CommentManagementView(int taskId);
	~CommentManagementView();
};

