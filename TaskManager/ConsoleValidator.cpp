#include "stdafx.h"
#include "iostream"

#include "ConsoleValidator.h"

using namespace std;

ConsoleValidator::ConsoleValidator()
{
}


ConsoleValidator::~ConsoleValidator()
{
}

bool ConsoleValidator::IsMinLength(char * charArray, int minLength)
{
	if (strlen(charArray) < minLength)
	{
		cout << endl << "The length of this field should be at least " << minLength << " symbols." << endl;
		system("pause");
		return false;
	}
	return true;
}
