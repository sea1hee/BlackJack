#pragma once
#include "Command.h"
class Replay :
	public Command
{
public:
	Replay() {}
	~Replay() {}

	void addCommandToLog(Command* newCommand)
	{
		replayLog.push_back(newCommand);
	}
	void execute()
	{
		for (int i = 0; i < replayLog.size(); i++)
		{
			system("pause");
			system("cls");
			replayLog[i]->execute();

			int inputc;
			cout << "\n\n\t계속보시겠습니까 ? Yes : 1 / No : other\n\t - >";
			cin >> inputc;
			if (inputc != 1)
				return;

		}
	}
private:
	vector<Command*> replayLog;
};

