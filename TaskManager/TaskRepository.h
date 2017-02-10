#pragma once
#include "Task.h"
#include "UserRepository.h"
#include <ctime>
class TaskRepository
{
private:
	int getNextId();
	char filepath[50];
	time_t charToTime(char charArray[200]);
public:
	void Add(Task* task);

	Task* GetById(int id);
	LinkedList<Task>* GetAll(int parentId);
	LinkedList<Task>* GetAll();

	bool Update(Task* task, int parentId);
	bool UpdateStatus(Task* task, int parentId);
	void Update(Task* task);

	bool Delete(Task* task, int parentId);
	void Delete(Task* task);

	TaskRepository(char filepath[50]);
	~TaskRepository();
};

