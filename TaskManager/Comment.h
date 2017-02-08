#pragma once
class Comment
{
private:
	int id;
	int taskId;
	int authorId;
	char body[200];
public:
	Comment();
	~Comment();

	void setId(int id);
	int getId();

	void setTaskId(int taskId);
	int getTaskId();

	void setAuthorId(int authorId);
	int getAuthorId();

	void setBody(char body[200]);
	char* getBody();
	
};

