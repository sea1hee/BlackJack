#pragma once
#include "Command.h"
#include <queue>
using namespace std;
class CheckLoser :
	public Command
{
public:
	CheckLoser() {

		command_name = "\n----------<Ż���ڸ� �����մϴ�>---------------";
	}
	CheckLoser(vector<User*>* _playerList, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* _scorePQ)
	{
		playerList = _playerList;
		scorePQ = _scorePQ;
	}
	~CheckLoser() {}

	void setprivate(vector<User*>* _playerList, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* _scorePQ)
	{
		playerList = _playerList;
		scorePQ = _scorePQ;
	}

	void execute()
	{
		system("pause");
		system("cls");

		for (int i = 0; i < (*playerList).size(); i++)
		{
			(*playerList)[i]->printMyInformation();
			UserScoreInfo loser;
			loser.setUser((*playerList)[i]);
			cout << "\t" << loser.calculateScore() << "�� �Դϴ�." << endl << endl;

		}

		cout << command_name << endl;
		int count = 0;

		vector<User*>loserindex;
		for (int i = 0; i < playerList->size(); i++)
		{
			UserScoreInfo loser;
			loser.setUser((*playerList)[i]);
			if (loser.calculateScore() == 0)
			{
				count++;
				(*scorePQ).push(loser);
				loserindex.push_back((*playerList)[i]);
				(*playerList)[i]->printMyInformation();
				cout << endl;
			}
		}

		if (count == 0)
			cout << "\n\tŻ���ڰ� �����ϴ�.\n\n";
		else
		{
			for (int j = 0; j < loserindex.size(); j++)
			{
				for (int i = 0; i < (*playerList).size(); i++)
				{
					if ((*playerList)[i] == loserindex[j])
					{
						(*playerList).erase((*playerList).begin() + i);

					}
				}
			}
		}
	}
private:
	vector<User*>* playerList;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQ;
};

