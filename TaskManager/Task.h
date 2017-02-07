#pragma once
class Task
{
private:
	int id;
	char header[50];
	char description[200];
	int measurement;		//time needed
	int executitiveId;		//id of the person who is going to do the task
	int creatorId;
	time_t timeOfCreation;
	time_t timeOfLastUpdate;
	bool isDone;			//Status of the task - done, or not

public:
	Task();
	~Task();

	void setId(int id);
	int getId();

	void setHeader(char header[50]);
	char* getHeader();

	void setDescription(char description[200]);
	char* getDescription();

	void setMeasurement(int measurement);
	int getMeasurement();

	void setExecutitiveId(int id);
	int getExecutitiveId();

	void setCreatorId(int id);
	int getCreatorId();

	void setTimeOfCreation(time_t time);
	time_t getRawTimeOfCreation();
	char* getTimeOfCreation();

	void setTimeOfLastUpdate(time_t time);
	time_t getRawTimeOfLastUpdate();
	char* getTimeOfLastUpdate();

	void setStatus(bool isDone);
	bool getStatus();
};

