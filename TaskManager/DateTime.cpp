#include "stdafx.h"
#include <time.h>

#include "DateTime.h"
#include <sstream>


DateTime::DateTime()
{
}


DateTime::~DateTime()
{
}

time_t DateTime::CharToTime(char charArray[200])
{
	std::istringstream ss(charArray);
	time_t result;
	ss >> result;
	return result;
}

char* DateTime::FormatDate(time_t time)
{
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);

	char result[80];
	strftime(result, 80, "%d/%m/%Y %I:%M:%S %p", &timeinfo);
	return result;
}
