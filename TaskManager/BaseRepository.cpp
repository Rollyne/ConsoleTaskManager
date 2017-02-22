#include "stdafx.h"
#include "BaseRepository.h"

using namespace std;
template <class T>
int BaseRepository<T>::getNextId()
{
	int nextId = 0;

	ifstream in(this->filepath);

	T* current = NULL;
	while (!in.eof())
	{
		current = readItem(&in);

		if (current->getId() > nextId)
		{
			nextId = current->getId();
		}
	}
	in.close();
	return nextId + 1;
}

template <class T>
void BaseRepository<T>::Add(T* item)
{
	ofstream out(this->filepath, ios::app);

	writeItem(item, &out);
	out.close();
}

template <class T>
T* BaseRepository<T>::GetById(int id)
{
	ifstream in(this->filepath);

	T* result = NULL;
	T* current = NULL;

	while (!in.eof())
	{
		current = readItem(&in);

		if (!in.eof() && current->getId() == id)
		{
			result = current;
			break;
		}
	}
	return result;
}

template <class T>
LinkedList<T>* BaseRepository<T>::GetAll()
{
	LinkedList<T>* result = new LinkedList<T>();
	ifstream in(this->filepath);

	while (!in.eof())
	{
		result->Add(readItem(&in));
	}

	int resultCount = result->Count();
	if (resultCount > 0)
		result->RemoveAt(resultCount - 1);

	return result;
}

template <class T>
void BaseRepository<T>::Update(T* item)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);


		T* current = NULL;
		while (!oldFile.eof())
		{
			current = readItem(&oldFile);

			if (!oldFile.eof() && current->getId() != item->getId())
			{
				writeItem(current, &newFile);
			}
			else if (!oldFile.eof() && current->getId() == item->getId())
			{
				writeItem(item, newFile);
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
	
}

template<class T>
void BaseRepository<T>::Delete(T* item)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		T* current = NULL;
		while (!oldFile.eof())
		{
			current = readItem(&oldFile);

			if (!oldFile.eof() && current->getId() != item->getId())
			{
				writeItem(current, newFile);
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}

template <class T>
BaseRepository<T>::BaseRepository(char filepath[50])
{
	strcpy_s(this->filepath, 50, filepath);
}

template <class T>
BaseRepository<T>::~BaseRepository()
{
}


