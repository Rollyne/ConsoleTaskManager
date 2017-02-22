#pragma once
#include "Comment.h"
#include "UserRepository.h"

class CommentRepository : public BaseRepository<Comment>
{
protected:
	void writeItem(Comment* item, std::ofstream* file) override;
	Comment* readItem(std::ifstream* file) override;
public:
	LinkedList<Comment>* GetAll(int parentId);
	explicit CommentRepository(char filepath[50]) : BaseRepository<Comment>(filepath) {}
};

