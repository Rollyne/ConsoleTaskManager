#pragma once
#include "string.h"
class ConsoleValidator
{
public:
	ConsoleValidator();
	~ConsoleValidator();

	bool IsMinLength(char* charArray, int minLength);
};

