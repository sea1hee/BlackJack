#pragma once
#include "UserScoreInfo.h"
#include <cstdlib>
#include <ctime>
using namespace std;
class Command
{
public:
	Command(){}
	~Command(){}

	virtual void execute() = 0;

protected:
	string command_name;
};

