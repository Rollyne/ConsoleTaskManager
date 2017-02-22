#pragma once
#include "fstream"
#include "LinkedList.cpp"

template <class T>
class BaseRepository
{
protected:
	char filepath[50];

	int getNextId();

	virtual void writeItem(T* item, std::ofstream* file) = 0;
	virtual T* readItem(std::ifstream* file) = 0;
public:
	void Add(T* item);

	T* GetById(int id);
	LinkedList<T>* GetAll();

	void Update(T* item);
	void Delete(T* item);

	explicit BaseRepository(char filepath[50]);
	virtual ~BaseRepository();
};

