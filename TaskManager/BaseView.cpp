#include "stdafx.h"
#include "BaseView.h"
#include "iostream"
#include "Console.h"

using namespace std;

template <class T>
char* BaseView<T>::className(bool toLower)
{
	char* result = new char;
	char* temp;
	
	strcpy_s(result, 20, typeid(T).name());
	temp = strtok_s(NULL, " ",&result);

	return result;
}

template <class T>
bool BaseView<T>::hasAccess(T* item)
{
	return true;
}
template <class T>
bool BaseView<T>::doesBelong(T* item)
{
	return true;
}




template<class T>
CRUDMenuItems BaseView<T>::RenderMenu()
{
	system("cls");
	

	cout << "## " << "" << " Management ##" << endl
		<< "[A]dd" << endl
		<< "[L]ist" << endl
		<< "[E]dit" << endl
		<< "[D]elete" << endl
		<< "E[x]it" << endl
		<< "> ";
	char* buffer;
	try
	{
		buffer = Console::ReadLineMin(1);
	}
	catch (invalid_argument e)
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
	default:
		return CRUDMenuItems::Invalid;
	}
}

template<class T>
void BaseView<T>::_add(BaseRepository<T>* repo)
{
	system("cls");

	cout << "## Create a new item ##" << endl;
	try
	{
		repo->Add(inputItem());
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}

	system("pause");
}

template <class T>
void BaseView<T>::_list(BaseRepository<T>* repo)
{
	system("cls");

	LinkedList<T>* allItems = repo->GetAll();

	int itemsCount = allItems->Count();

	cout << "## All items ##" << endl << endl;
	for (int i = 0; i < itemsCount; i++)
	{
		T* item = allItems->getItemAt(i);
		if (doesBelong(item))
		{
			cout << "# # # # # # # # # # #" << endl;
			printItem(item);
		}
	}

	delete allItems;

	system("pause");
}

template <class T>
void BaseView<T>::_edit(BaseRepository<T>* repo)
{
	system("cls");

	cout << "## Update item ##" << endl
		<< "Index of the item: ";
	try
	{
		int index = Console::ReadNumber();

		auto item = repo->GetById(index);
		if (item != NULL)
		{
			if (hasAccess(item))
			{
				updateItem(item);
				repo->Update(item);

				delete item;
			}
			else
				cout << "You cannot edit this item." << endl;
		}
		else
		{
			cout << "This item doesn't exist." << endl;
		}
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
	}

	system("pause");
}

template <class T>
void BaseView<T>::_delete(BaseRepository<T>* repo)
{
	system("cls");

	cout << "## Delete item ##" << endl
		<< "Index of the item: ";
	T* removed;
	try
	{
		removed = repo->GetById(Console::ReadNumber());
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
		system("pause");
		return;
	}
	if (removed != NULL)
	{
		if (hasAccess(removed))
		{
			repo->Delete(removed);
			cout << "Item removed." << endl;
		}
		else
			cout << "You cannot delete this item" << endl;
	}
	else
	{
		cout << "This item doesn't exist" << endl;
	}

	delete removed;

	system("pause");
}

template<class T>
void BaseView<T>::Run()
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

template <class T>
BaseView<T>::BaseView()
{
}

template<class T>
BaseView<T>::~BaseView()
{
}