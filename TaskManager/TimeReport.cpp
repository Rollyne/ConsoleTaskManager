#include "stdafx.h"
#include <ctime>
#include <string>

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
	this->rawTimeOfReport = time;

	struct tm timeinfo;
	localtime_s(&timeinfo, &time);

	char timeOfCreation[80];
	strftime(timeOfCreation, 80, "%d/%m/%Y %I:%M:%S %p", &timeinfo);
	strcpy_s(this->timeOfReport, timeOfCreation);
}

time_t TimeReport::getRawTimeOfReport()
{
	return this->rawTimeOfReport;
}

char * TimeReport::getTimeOfReport()
{
	return this->timeOfReport;
}
