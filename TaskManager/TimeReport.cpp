#include "stdafx.h"
#include <ctime>

#include "TimeReport.h"


TimeReport::TimeReport()
{
}


TimeReport::~TimeReport()
{
}

void TimeReport::setId(int id)
{
	this->id = id;
}

int TimeReport::getId()
{
	return this->id;
}

void TimeReport::setTaskId(int taskId)
{
	this->taskId = taskId;
}

int TimeReport::getTaskId()
{
	return this->taskId;
}

void TimeReport::setRepotrterId(int reporterId)
{
	this->reporterId = reporterId;
}

int TimeReport::getReporterId()
{
	return this->reporterId;
}

void TimeReport::setHoursSpent(int hoursSpent)
{
	this->hours = hoursSpent;
}

int TimeReport::getHoursSpent()
{
	return this->hours;
}

void TimeReport::setTimeOfReport(time_t time)
{
	this->timeOfReport = time;
}

time_t TimeReport::getRawTimeOfReport()
{
	return this->timeOfReport;
}

char * TimeReport::getTimeOfReport()
{
	struct tm timeinfo;
	localtime_s(&timeinfo, &this->timeOfReport);

	char result[80];
	strftime(result, 80, "%d/%m/%Y %I:%M:%S", &timeinfo);
	return result;
}
