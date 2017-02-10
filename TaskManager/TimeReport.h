#pragma once
class TimeReport
{
private:
	int id;
	int taskId;
	int reporterId;
	int hours;
	time_t timeOfReport;
public:
	TimeReport();
	~TimeReport();

	void setId(int id);
	int getId();

	void setTaskId(int taskId);
	int getTaskId();

	void setRepotrterId(int reporterId);
	int getReporterId();

	void setHoursSpent(int hoursSpent);
	int getHoursSpent();

	void setTimeOfReport(time_t time);
	time_t getRawTimeOfReport();
	char* getTimeOfReport();
};

