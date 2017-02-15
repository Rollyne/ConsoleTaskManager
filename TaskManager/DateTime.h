#pragma once
class DateTime
{
public:
	DateTime();
	~DateTime();

	static time_t CharToTime(char charArray[200]);
	static char* FormatDate(time_t time);
};

