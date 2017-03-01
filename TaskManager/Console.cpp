#include "stdafx.h"
#include "Console.h"
#include <iostream>
#include <string>

using namespace std;

Console::Console()
{
}


Console::~Console()
{
}

char* Console::ReadLine()
{
	string input;
	getline(cin, input);
	int inputSize = input.size();

	char* result = new char[inputSize + 1];
	const char* temp = input.c_str();

	strcpy_s(result, inputSize + 1, temp);

	return result;
}

char* Console::ReadLineMin(int minLength)
{
	string input;
	getline(cin, input);
	int inputSize = input.size();

	ConsoleValidator::IsMoreThan(input, minLength);

	char* result = new char[inputSize + 1];
	const char* temp = input.c_str();

	strcpy_s(result, inputSize + 1, temp);

	return result;
}


char* Console::ReadLine(int length)
{
	string input;
	getline(cin, input);

	if(input.length() > length)
	{
		throw invalid_argument("The input is way too long.");
	}

	char* result = new char[length + 1];
	const char* temp = input.c_str();

	strcpy_s(result,length+1, temp);

	return result;
}

char* Console::ReadLine(int length, int minLength)
{
	string input;
	getline(cin, input);
	if (input.length() > length)
	{
		throw invalid_argument("The input is way too long.");
	}

	ConsoleValidator::IsMoreThan(input, minLength);

	char* result = new char[length + 1];
	const char* temp = input.c_str();

	strcpy_s(result, length + 1, temp);
	return result;
}

int Console::ReadNumber()
{
	int input;
	cin >> input;
	if (cin.fail())
	{
		cin.clear();
		string ignoreLine;
		getline(cin, ignoreLine); //removing the input from the cin
		throw invalid_argument("The input is not a number.");
	}
	cin.clear();
	string ignoreLine;
	getline(cin, ignoreLine); //removing the input from the cin beacause it has leftover empty string
	return input;
}

