#pragma once
#include "User.h"
#include "BaseView.cpp"

class UserManagementView :public BaseView<User>
{
protected:
	User* inputItem() override;
	User* updateItem(User* outdated) override;
	void printItem(User* item) override;

	void Add() override;
	void List() override;
	void Edit() override;
	void Delete() override;
public:
	UserManagementView();
	~UserManagementView();
};

