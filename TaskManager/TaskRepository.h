#pragma once
#include "Task.h"
#include "CommentRepository.h"
class TaskRepository
{
private:
	int getNextId();
	char filepath[50];
public:
	void Add(Task* task);

	Task* GetById(int id);
	LinkedList<Task>* GetAll(int parentId);
	LinkedList<Task>* GetAll();

	void Update(Task* task);
	void Delete(Task* task);

	TaskRepository(char filepath[50]);
	~TaskRepository();
};

