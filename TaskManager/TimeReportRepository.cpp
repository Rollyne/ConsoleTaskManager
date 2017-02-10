#include "stdafx.h"
#include "string.h"
#include "fstream"

#include "TimeReportRepository.h"

using namespace std;

TimeReportRepository::TimeReportRepository(char filepath[50])
{
	strcpy_s(this->filepath, 50, filepath);
}

TimeReportRepository::~TimeReportRepository()
{
}

int TimeReportRepository::getNextId()
{
	int nextId = 0;

	ifstream in(this->filepath);

	if (in.is_open())
	{
		TimeReport* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new TimeReport;

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 20);
			in.getline(buffer, 20);
			in.getline(buffer, 200);

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

void TimeReportRepository::Add(TimeReport * report)
{
	ofstream out(this->filepath, ios::app);

	if (out.is_open())
	{
		out << this->getNextId() << endl
			<< comment->getTaskId() << endl
			<< comment->getAuthorId() << endl
			<< comment->getBody() << endl;

		out.close();
		return;
	}

}

TimeReport * TimeReportRepository::GetById(int id)
{
	ifstream in(this->filepath);
	TimeReport* result = NULL;

	if (in.is_open())
	{
		TimeReport* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new TimeReport();

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			in.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			in.getline(buffer, 200);
			current->setBody(buffer);

			if (!in.eof() && current->getId() == id)
			{
				result = current;
				break;
			}
		}
	}
	return result;
}

LinkedList<TimeReport>* TimeReportRepository::GetAll(int taskId)
{
	LinkedList<TimeReport>* result = new LinkedList<TimeReport>();
	ifstream in(this->filepath);

	if (in.is_open())
	{
		TimeReport* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new TimeReport;

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			in.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			in.getline(buffer, 200);
			current->setBody(buffer);

			if (current->getTaskId() == taskId)
				result->Add(current);
		}
	}

	return result;
}

void TimeReportRepository::Update(TimeReport * report)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		TimeReport* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[200];
			current = new TimeReport();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			oldFile.getline(buffer, 200);
			current->setBody(buffer);

			if (!oldFile.eof() && current->getId() != report->getId())
			{
				newFile << current->getId() << endl
					<< current->getTaskId() << endl
					<< current->getAuthorId() << endl
					<< current->getBody() << endl;
			}
			else if (!oldFile.eof() && current->getId() == report->getId())
			{
				newFile << report->getId() << endl
					<< report->getTaskId() << endl
					<< report->getAuthorId() << endl
					<< report->getBody() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}

void TimeReportRepository::Delete(TimeReport * report)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		TimeReport* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[200];
			current = new TimeReport();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			oldFile.getline(buffer, 200);
			current->setBody(buffer);

			if (!oldFile.eof() && current->getId() != report->getId())
			{
				newFile << current->getId() << endl
					<< current->getTaskId() << endl
					<< current->getAuthorId() << endl
					<< current->getBody() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}
