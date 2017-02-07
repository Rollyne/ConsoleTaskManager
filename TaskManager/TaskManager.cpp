// TaskManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);

	char result[80];
	strftime(result, 80, "%d/%m/%Y %I:%M:%S", &timeinfo);
	cout << result;
	system("pause");
    return 0;
	
}

