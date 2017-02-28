#pragma once
#include "MenuItems.h"
#include "UserRepository.h"

template <class T>
class BaseView
{
protected:
	const int textFieldMinLength = 3;
	char filename[50];

	virtual T* inputItem() = 0;
	virtual T* updateItem(T* outdated) = 0;
	virtual void printItem(T* item) = 0;
	
	virtual bool hasAccess(T* item);

	char* className(bool toLower);
	//void getFileName();

	void _add(BaseRepository<T>* repo);
	void _list(BaseRepository<T>* repo);
	void _edit(BaseRepository<T>* repo);
	void _delete(BaseRepository<T>* repo);

	virtual	void Add() = 0;
	virtual	void List() = 0;
	virtual	void Edit() = 0;
	virtual	void Delete() = 0;

	virtual CRUDMenuItems RenderMenu();
public:

	BaseView();
	~BaseView();

	void Run();
};


