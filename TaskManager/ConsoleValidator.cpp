#include "stdafx.h"
#include <string>

#include "ConsoleValidator.h"

using namespace std;

ConsoleValidator::ConsoleValidator()
{
}


ConsoleValidator::~ConsoleValidator()
{
}

bool ConsoleValidator::IsMoreThan(char * charArray, int minLength)
{
	if (strlen(charArray) < minLength)
	{
		char lengthChar[32];
		sprintf_s(lengthChar, "%d", minLength);
		char message[100] = "The symbols of this field should be at least ";
		strcat_s(message, lengthChar);
		throw invalid_argument(message);
	}
	return true;
}
bool ConsoleValidator::IsMoreThan(string input, int minLength)
{
	if (input.length() < minLength)
	{
		char lengthChar[32];
		sprintf_s(lengthChar, "%d", minLength);
		char message[100] = "The symbols of this field should be at least ";
		strcat_s(message, lengthChar);
		throw invalid_argument(message);
	}
	return true;
}
