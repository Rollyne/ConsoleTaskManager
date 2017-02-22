#include "stdafx.h"
#include "string.h"
#include "fstream"

#include "CommentRepository.h"

using namespace std;

void CommentRepository::writeItem(Comment* item, std::ofstream* file)
{
	if (file->is_open())
	{
		if (item->getId() < 0) // If it is less than zero it is undefined
			item->setId(this->getNextId());

		*file << item->getId() << endl
			<< item->getTaskId() << endl
			<< item->getAuthorId() << endl
			<< item->getBody() << endl;
	}
}

Comment* CommentRepository::readItem(std::ifstream* file)
{
	Comment* result = NULL;

	if (file->is_open())
	{
		Comment* current = new Comment;
		char buffer[200];

		file->getline(buffer, 20);
		current->setId(atoi(buffer));

		file->getline(buffer, 20);
		current->setTaskId(atoi(buffer));

		file->getline(buffer, 20);
		current->setAuthorId(atoi(buffer));

		file->getline(buffer, 200);
		current->setBody(buffer);

		result = current;

	}
	return result;
}

LinkedList<Comment>* CommentRepository::GetAll(int taskId)
{
	LinkedList<Comment>* result = new LinkedList<Comment>();
	ifstream in(this->filepath);

	if (in.is_open())
	{
		Comment* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = readItem(&in);

			if(current->getTaskId() == taskId)
				result->Add(current);
		}
	}

	return result;
}

