#pragma once
#include "TimeReport.h"
#include "UserRepository.h"

class TimeReportRepository : public BaseRepository<TimeReport>
{
protected:
	void writeItem(TimeReport* item, std::ofstream* file) override;
	TimeReport* readItem(std::ifstream* file) override;
public:
	LinkedList<TimeReport>* GetAll(int parentId);
	explicit TimeReportRepository(char filepath[50]) : BaseRepository<TimeReport>(filepath) {}
};

