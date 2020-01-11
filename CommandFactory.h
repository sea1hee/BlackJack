#pragma once
#include "CheckLoser.h"
#include "CheckWinner.h"
#include "InitialCardDistribution.h"
#include "PersonalHitRequest.h"
#include "Replay.h"
#pragma once
class CommandFactory
{
private:
	CommandFactory() {}

public:
	~CommandFactory() {}

	Command* getCommand(int id) 
	{
		Command* temp;
		switch (id)
		{
		case 1:
			temp = new CheckLoser();
			return temp;
			break;
		case 2:
			temp = new CheckWinner();
			return temp;
			break;
		case 3:
			temp = new InitialCardDistribution();
			return temp;
			break;
		case 4:
			temp = new PersonalHitRequest();
			return temp;
			break;
		case 5:
			temp = new Replay();
			return temp;
			break;
		default:
			break;
		}

	}
	static CommandFactory* getInstance() 
	{
		if (instance == nullptr)
		{
			CommandFactory* newcommandfactory = new CommandFactory();
			instance = newcommandfactory;
			return instance;
		}
		else
		{
			return instance;
		}

	}

private:
	static CommandFactory* instance;
};

CommandFactory* CommandFactory::instance = nullptr;