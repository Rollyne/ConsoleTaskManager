#pragma once
#include "User.h"
#include "BaseView.cpp" //How to include this everywhere without getting errors ?

class UserManagementView :public BaseView<User>
{
protected:
	User* inputItem() override;
	void updateItem(User* item) override;
	void printItem(User* item) override;

	void Add() override;
	void List() override;
	void Edit() override;
	void Delete() override;
public:
	UserManagementView();
	~UserManagementView();
};

