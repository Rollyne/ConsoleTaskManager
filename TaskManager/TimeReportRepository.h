#pragma once
#include "TimeReport.h"
#include "UserRepository.h"

class TimeReportRepository
{
private:
	int getNextId();
	char filepath[50];
public:
	void Add(TimeReport* report);

	TimeReport* GetById(int id);
	LinkedList<TimeReport>* GetAll(int taskId);

	void Update(TimeReport* report);

	void Delete(TimeReport* report);

	TimeReportRepository(char filepath[50]);
	~TimeReportRepository();
};

