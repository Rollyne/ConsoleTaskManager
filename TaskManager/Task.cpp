#include "stdafx.h"
#include "string.h"
#include <ctime>
#include "DateTime.h"

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

	strcpy_s(this->timeOfCreation, 80, DateTime::FormatDate(time));
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

	strcpy_s(this->timeOfLastUpdate, 80, DateTime::FormatDate(time));
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
