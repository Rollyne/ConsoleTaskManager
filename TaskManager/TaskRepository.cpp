#include "stdafx.h"
#include "fstream"
#include <ctime>
#include <sstream>

#include "TaskRepository.h"

using namespace std;

TaskRepository::TaskRepository(char filepath[50])
{

	strcpy_s(this->filepath, 50, filepath);
}


TaskRepository::~TaskRepository()
{
}

time_t TaskRepository::charToTime(char charArray[200])
{
	istringstream ss(charArray);
	time_t result;
	ss >> result;
	return result;
}

int TaskRepository::getNextId()
{
	int nextId = 0;

	ifstream in(this->filepath);

	if (in.is_open())
	{
		Task* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new Task;

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 50);
			in.getline(buffer, 200);
			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 20);

			if (current->getId() > nextId)
			{
				nextId = current->getId();
			}
		}
		in.close();
		return nextId + 1;
	}

	return -1;
}

void TaskRepository::Add(Task * task)
{
	ofstream out(this->filepath, ios::app);

	if (out.is_open())
	{
		out << this->getNextId() << endl
			<< task->getHeader() << endl
			<< task->getDescription() << endl
			<< task->getMeasurement() << endl
			<< task->getExecutitiveId() << endl
			<< task->getCreatorId() << endl
			<< task->getRawTimeOfCreation() << endl
			<< task->getRawTimeOfLastUpdate() << endl
			<< task->getStatus() << endl;

		out.close();
		return;
	}

}

Task * TaskRepository::GetById(int id)
{
	ifstream in(this->filepath);
	Task* result = NULL;

	if (in.is_open())
	{
		Task* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new Task();

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 50);
			current->setHeader(buffer);

			in.getline(buffer, 200);
			current->setDescription(buffer);

			in.getline(buffer, 20);
			current->setMeasurement(atoi(buffer));

			in.getline(buffer, 20);
			current->setExecutitiveId(atoi(buffer));

			in.getline(buffer, 20);
			current->setCreatorId(atoi(buffer));

			in.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfCreation(charToTime(buffer));

			in.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfLastUpdate(charToTime(buffer));

			in.getline(buffer, 20);
			current->setStatus(atoi(buffer));

			if (!in.eof() && current->getId() == id)
			{
				result = current;
				break;
			}
		}
	}
	return result;
}

LinkedList<Task>* TaskRepository::GetAll(int parentId)
{
	LinkedList<Task>* result = new LinkedList<Task>();
	ifstream in(this->filepath);

	if (in.is_open())
	{
		Task* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new Task();

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 50);
			current->setHeader(buffer);

			in.getline(buffer, 200);
			current->setDescription(buffer);

			in.getline(buffer, 20);
			current->setMeasurement(atoi(buffer));

			in.getline(buffer, 20);
			current->setExecutitiveId(atoi(buffer));

			in.getline(buffer, 20);
			current->setCreatorId(atoi(buffer));

			in.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfCreation(charToTime(buffer));

			in.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfLastUpdate(charToTime(buffer));

			in.getline(buffer, 20);
			current->setStatus(atoi(buffer));

			if (!in.eof() && (current->getCreatorId() == parentId || current->getExecutitiveId() == parentId))
				result->Add(current);
		}
	}

	return result;
}

LinkedList<Task>* TaskRepository::GetAll()
{
	LinkedList<Task>* result = new LinkedList<Task>();
	ifstream in(this->filepath);

	if (in.is_open())
	{
		Task* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new Task();

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 50);
			current->setHeader(buffer);

			in.getline(buffer, 200);
			current->setDescription(buffer);

			in.getline(buffer, 20);
			current->setMeasurement(atoi(buffer));

			in.getline(buffer, 20);
			current->setExecutitiveId(atoi(buffer));

			in.getline(buffer, 20);
			current->setCreatorId(atoi(buffer));

			in.getline(buffer, 200);
			if(strlen(buffer) > 0)
				current->setTimeOfCreation(charToTime(buffer));

			in.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfLastUpdate(charToTime(buffer));

			in.getline(buffer, 20);
			current->setStatus(atoi(buffer));

			result->Add(current);
		}
	}

	int resultCount = result->Count();
	if (resultCount > 0)
		result->RemoveAt(resultCount - 1);

	return result;
}

void TaskRepository::Update(Task * task)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		Task* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[200];
			current = new Task();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 50);
			current->setHeader(buffer);

			oldFile.getline(buffer, 200);
			current->setDescription(buffer);

			oldFile.getline(buffer, 20);
			current->setMeasurement(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setExecutitiveId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setCreatorId(atoi(buffer));

			oldFile.getline(buffer, 200);
			if(strlen(buffer) > 0)
				current->setTimeOfCreation(charToTime(buffer));

			oldFile.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfLastUpdate(charToTime(buffer));

			oldFile.getline(buffer, 20);;
			current->setStatus(atoi(buffer));

			if (!oldFile.eof() && current->getId() != task->getId())
			{
				newFile << current->getId() << endl
					<< current->getHeader() << endl
					<< current->getDescription() << endl
					<< current->getMeasurement() << endl
					<< current->getExecutitiveId() << endl
					<< current->getCreatorId() << endl
					<< current->getRawTimeOfCreation() << endl
					<< current->getRawTimeOfLastUpdate() << endl
					<< current->getStatus() << endl;
			}
			else if (!oldFile.eof() && current->getId() == task->getId())
			{
				newFile << task->getId() << endl
					<< task->getHeader() << endl
					<< task->getDescription() << endl
					<< task->getMeasurement() << endl
					<< task->getExecutitiveId() << endl
					<< task->getCreatorId() << endl
					<< task->getRawTimeOfCreation() << endl
					<< task->getRawTimeOfLastUpdate() << endl
					<< task->getStatus() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}

void TaskRepository::Delete(Task * user)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		Task* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[200];
			current = new Task();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 50);
			current->setHeader(buffer);

			oldFile.getline(buffer, 200);
			current->setDescription(buffer);

			oldFile.getline(buffer, 20);
			current->setMeasurement(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setExecutitiveId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setCreatorId(atoi(buffer));

			oldFile.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfCreation(charToTime(buffer));

			oldFile.getline(buffer, 200);
			if (strlen(buffer) > 0)
				current->setTimeOfLastUpdate(charToTime(buffer));

			oldFile.getline(buffer, 20);
			current->setStatus(atoi(buffer));

			if (!oldFile.eof() && current->getId() != user->getId())
			{
				newFile << current->getId() << endl
					<< current->getHeader() << endl
					<< current->getDescription() << endl
					<< current->getMeasurement() << endl
					<< current->getExecutitiveId() << endl
					<< current->getCreatorId() << endl
					<< current->getRawTimeOfCreation() << endl
					<< current->getRawTimeOfLastUpdate() << endl
					<< current->getStatus() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}
