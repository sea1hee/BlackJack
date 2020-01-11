#pragma once
#include "Command.h"
class GameCommandInvoker
{
public:
	GameCommandInvoker() 
	{
	}
	~GameCommandInvoker() {}

	void setcurCommand(Command* temp)
	{
		curCommand = temp;
	}
	Command* getcurCommand()
	{
		return curCommand;
	}

	void executeCommand() 
	{

		curCommand->execute();
	}
private:
	Command* curCommand;
};

