#include "stdafx.h"
#include <string>
#include "DateTime.h"

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

	strcpy_s(this->timeOfReport, 80, DateTime::FormatDate(time));
}

time_t TimeReport::getRawTimeOfReport()
{
	return this->rawTimeOfReport;
}

char * TimeReport::getTimeOfReport()
{
	return this->timeOfReport;
}
