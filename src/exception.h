#pragma once
#include <string>
using namespace std;

class CoincideException : public exception
{
public:
	CoincideException(const char* str) :exception(str)
	{

	}
};
class InputException : public exception {
public:
	InputException(const char* str) : exception(str) {

	}
};
class CommandException : public exception {
public:
	CommandException(const char* str) : exception(str) {

	}
};