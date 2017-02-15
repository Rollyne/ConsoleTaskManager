#include "stdafx.h"
#include "string.h"
#include <ctime>

#include "Task.h"


Task::Task()
{
}


Task::~Task()
{
}

void Task::setId(int id)
{
	this->id = id;
}

int Task::getId()
{
	return this->id;
}

void Task::setHeader(char header[50])
{
	strcpy_s(this->header,50, header);
}

char * Task::getHeader()
{
	return this->header;
}

void Task::setDescription(char description[200])
{
	strcpy_s(this->description,200, description);
}

char * Task::getDescription()
{
	return this->description;
}

void Task::setMeasurement(int measurement)
{
	this->measurement = measurement;
}

int Task::getMeasurement()
{
	return this->measurement;
}

void Task::setExecutitiveId(int id)
{
	this->executitiveId = id;
}

int Task::getExecutitiveId()
{
	return this->executitiveId;
}

void Task::setCreatorId(int id)
{
	this->creatorId = id;
}

int Task::getCreatorId()
{
	return this->creatorId;
}

void Task::setTimeOfCreation(time_t time)
{
	this->rawTimeOfCreation = time;

	struct tm timeinfo;
	localtime_s(&timeinfo, &time);

	char timeOfCreation[80];
	strftime(timeOfCreation, 80, "%d/%m/%Y %I:%M:%S %p", &timeinfo);
	strcpy_s(this->timeOfCreation, timeOfCreation);
}

time_t Task::getRawTimeOfCreation()
{
	return this->rawTimeOfCreation;
}

char * Task::getTimeOfCreation()
{
	return this->timeOfCreation;
}

void Task::setTimeOfLastUpdate(time_t time)
{
	this->rawTimeOfLastUpdate = time;

	struct tm timeinfo;
	localtime_s(&timeinfo, &time);

	char timeOfLastUpdate[80];
	strftime(timeOfLastUpdate, 80, "%d/%m/%Y %I:%M:%S %p", &timeinfo);
	strcpy_s(this->timeOfLastUpdate, timeOfLastUpdate);
}

time_t Task::getRawTimeOfLastUpdate()
{
	return this->rawTimeOfLastUpdate;
}

char * Task::getTimeOfLastUpdate()
{
	return this->timeOfLastUpdate;
}

void Task::setStatus(bool isDone)
{
	this->isDone = isDone;
}

bool Task::getStatus()
{
	return this->isDone;
}
