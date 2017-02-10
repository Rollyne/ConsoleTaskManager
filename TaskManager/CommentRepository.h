#pragma once
#include "Comment.h"
#include "UserRepository.h"

class CommentRepository
{
private:
	int getNextId();
	char filepath[50];
public:
	void Add(Comment* comment);

	Comment* GetById(int id);
	LinkedList<Comment>* GetAll(int taskId);

	void Update(Comment* comment);

	void Delete(Comment* comment);

	CommentRepository(char filepath[50]);
	~CommentRepository();
};

