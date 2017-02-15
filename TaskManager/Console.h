#pragma once
#include "ConsoleValidator.h"
class Console
{
public:
	Console();
	~Console();

	static char* ReadLine();
	static char* ReadLineMin(int minLength);
	static char* ReadLine(int length);
	static char* ReadLine(int length, int minLength);
	static int ReadNumber();
	static int ReadNumber(int maxLength);
};

