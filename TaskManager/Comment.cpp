#include "stdafx.h"
#include "string.h"

#include "Comment.h"


Comment::Comment()
{
}


Comment::~Comment()
{
}

void Comment::setId(int id)
{
	this->id = id;
}

int Comment::getId()
{
	return this->id;
}

void Comment::setTaskId(int taskId)
{
	this->taskId = taskId;
}

int Comment::getTaskId()
{
	return this->taskId;
}

void Comment::setAuthorId(int authorId)
{
	this->authorId = authorId;
}

int Comment::getAuthorId()
{
	return this->authorId;
}

void Comment::setBody(char body[200])
{
	strcpy_s(this->body, 200, body);
}

char * Comment::getBody()
{
	return this->body;
}
