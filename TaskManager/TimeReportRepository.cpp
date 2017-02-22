#include "stdafx.h"
#include "string.h"
#include "fstream"
#include <sstream>

#include "TimeReportRepository.h"
#include "DateTime.h"

using namespace std;


void TimeReportRepository::writeItem(TimeReport* item, std::ofstream* file)
{
	if (file->is_open())
	{
		if (item->getId() < 0) // If it is less than zero it is undefined
			item->setId(this->getNextId());

		*file << item->getId() << endl
			<< item->getTaskId() << endl
			<< item->getReporterId() << endl
			<< item->getHoursSpent() << endl
			<< item->getRawTimeOfReport() << endl;
	}
}

TimeReport* TimeReportRepository::readItem(std::ifstream* file)
{
	TimeReport* result = NULL;
	if (file->is_open()) {
		char buffer[80];
		TimeReport* current = new TimeReport;

		file->getline(buffer, 20);
		current->setId(atoi(buffer));

		file->getline(buffer, 20);
		current->setTaskId(atoi(buffer));

		file->getline(buffer, 20);
		current->setRepotrterId(atoi(buffer));

		file->getline(buffer, 20);
		current->setHoursSpent(atoi(buffer));

		file->getline(buffer, 80);
		if (strlen(buffer) > 0)
			current->setTimeOfReport(DateTime::CharToTime(buffer));

		result = current;
	}
	return result;
}

LinkedList<TimeReport>* TimeReportRepository::GetAll(int taskId)
{
	LinkedList<TimeReport>* result = new LinkedList<TimeReport>();
	ifstream in(this->filepath);

	if (in.is_open())
	{
		while (!in.eof())
		{
			char buffer[80];
			TimeReport* current = readItem(&in);

			if (current->getTaskId() == taskId)
				result->Add(current);
		}
	}

	return result;
}

