#pragma once
#include "Task.h"
#include "UserRepository.h"
class TaskRepository :public BaseRepository<Task>
{
protected:
	void writeItem(Task* item, std::ofstream* file) override;
	Task* readItem(std::ifstream* file) override;
public:
	LinkedList<Task>* GetAll(int parentId);
	explicit TaskRepository(char filepath[50]) : BaseRepository<Task>(filepath) {}
};

