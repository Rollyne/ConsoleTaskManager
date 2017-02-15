#pragma once
#include <string>
class ConsoleValidator
{

public:
	ConsoleValidator();
	~ConsoleValidator();

	static bool IsMoreThan(char* charArray, int minLength);
	static bool IsMoreThan(std::string input, int minLength);
};

