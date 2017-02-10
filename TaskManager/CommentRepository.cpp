#include "stdafx.h"
#include "string.h"
#include "fstream"

#include "CommentRepository.h"

using namespace std;

CommentRepository::CommentRepository(char filepath[50])
{
	strcpy_s(this->filepath, 50, filepath);
}

CommentRepository::~CommentRepository()
{
}

int CommentRepository::getNextId()
{
	int nextId = 0;

	ifstream in(this->filepath);

	if (in.is_open())
	{
		Comment* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new Comment;

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

void CommentRepository::Add(Comment * comment)
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

Comment * CommentRepository::GetById(int id)
{
	ifstream in(this->filepath);
	Comment* result = NULL;

	if (in.is_open())
	{
		Comment* current = NULL;
		while (!in.eof())
		{
			char buffer[200];
			current = new Comment();

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
			current = new Comment;

			in.getline(buffer, 20);
			current->setId(atoi(buffer));

			in.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			in.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			in.getline(buffer, 200);
			current->setBody(buffer);

			if(current->getTaskId() == taskId)
				result->Add(current);
		}
	}

	return result;
}

void CommentRepository::Update(Comment * comment)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		Comment* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[200];
			current = new Comment();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			oldFile.getline(buffer, 200);
			current->setBody(buffer);

			if (!oldFile.eof() && current->getId() != comment->getId())
			{
				newFile << current->getId() << endl
					<< current->getTaskId() << endl
					<< current->getAuthorId() << endl
					<< current->getBody() << endl;
			}
			else if (!oldFile.eof() && current->getId() == comment->getId())
			{
				newFile << comment->getId() << endl
					<< comment->getTaskId() << endl
					<< comment->getAuthorId() << endl
					<< comment->getBody() << endl;
			}
		}
		newFile.close();
		oldFile.close();

		remove(this->filepath);
		rename("temp.txt", this->filepath);
		return;
	}
}

void CommentRepository::Delete(Comment * comment)
{
	ofstream newFile("temp.txt", ios::app);
	ifstream oldFile(this->filepath);

	if (oldFile.is_open() && newFile.is_open())
	{
		Comment* current = NULL;
		while (!oldFile.eof())
		{
			char buffer[200];
			current = new Comment();

			oldFile.getline(buffer, 20);
			current->setId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setTaskId(atoi(buffer));

			oldFile.getline(buffer, 20);
			current->setAuthorId(atoi(buffer));

			oldFile.getline(buffer, 200);
			current->setBody(buffer);

			if (!oldFile.eof() && current->getId() != comment->getId())
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