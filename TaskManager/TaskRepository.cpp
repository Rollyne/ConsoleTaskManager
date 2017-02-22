#include "stdafx.h"
#include "fstream"
#include <ctime>
#include <sstream>
#include "DateTime.h"

#include "TaskRepository.h"

using namespace std;

void TaskRepository::writeItem(Task* item, std::ofstream* file)
{
	if (file->is_open())
	{
		if (item->getId() < 0) // If it is less than zero it is undefined
			item->setId(this->getNextId());

		*file << item->getId() << endl
			<< item->getHeader() << endl
			<< item->getDescription() << endl
			<< item->getMeasurement() << endl
			<< item->getExecutitiveId() << endl
			<< item->getCreatorId() << endl
			<< item->getRawTimeOfCreation() << endl
			<< item->getRawTimeOfLastUpdate() << endl
			<< item->getStatus() << endl;
	}
}

Task* TaskRepository::readItem(std::ifstream* file)
{
	Task* result = NULL;

	if (file->is_open())
	{
		Task* current = new Task;
		char buffer[200];

		file->getline(buffer, 20);
		current->setId(atoi(buffer));

		file->getline(buffer, 50);
		current->setHeader(buffer);

		file->getline(buffer, 200);
		current->setDescription(buffer);

		file->getline(buffer, 20);
		current->setMeasurement(atoi(buffer));

		file->getline(buffer, 20);
		current->setExecutitiveId(atoi(buffer));

		file->getline(buffer, 20);
		current->setCreatorId(atoi(buffer));

		file->getline(buffer, 200);
		if (strlen(buffer) > 0)
			current->setTimeOfCreation(DateTime::CharToTime(buffer));

		file->getline(buffer, 200);
		if (strlen(buffer) > 0)
			current->setTimeOfLastUpdate(DateTime::CharToTime(buffer));

		file->getline(buffer, 20);
		current->setStatus(atoi(buffer));

		result = current;

	}
	return result;
}

LinkedList<Task>* TaskRepository::GetAll(int parentId)
{
	LinkedList<Task>* result = new LinkedList<Task>();
	ifstream in(this->filepath);

	while (!in.eof())
	{
		Task* current = readItem(&in);
		if(!in.eof() && current->getExecutitiveId() == parentId || current->getCreatorId() == parentId)
			result->Add(current);
	}
	return result;
}

