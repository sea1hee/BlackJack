#pragma once
#include "Command.h"
#include <queue>
using namespace std;
class CheckWinner :
	public Command
{
public:
	CheckWinner() {
		command_name = "--------------<승리자를 선정합니다>-------------";
	}
	CheckWinner(vector<User*>* _playerList, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* _scorePQ)
	{
		playerList = _playerList;
		scorePQ = _scorePQ;
	}
	~CheckWinner() {}


	void setprivate(vector<User*>* _playerList, priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* _scorePQ)
	{
		playerList = _playerList;
		scorePQ = _scorePQ;
	}


	void execute()
	{
		cout << command_name<<endl;
		UserScoreInfo* winner;
		for (int i = 0; i < playerList->size(); i++)
		{
			winner = new UserScoreInfo;
			winner->setUser((*playerList)[i]);
			winner->calculateScore();
			(*scorePQ).push(*winner);
		}

		// 배당 점수 지급
		vector<UserScoreInfo> tempscoreInfo;
		while (!scorePQ->empty())
		{
			tempscoreInfo.push_back(scorePQ->top());
			scorePQ->pop();
		}

		cout << "-------배당 현황 --------" << endl;
		for (int i = 0; i < tempscoreInfo.size(); i++)
		{
			cout <<"\t" << tempscoreInfo[i].getUser()->getUsername() << "님의 배당 금액 : "
				<< tempscoreInfo[i].getUser()->getbettingScore() << endl << endl;
		}
		
		cout << "-------게임 결과 --------" << endl;
		int win = 1;
		for (int i = tempscoreInfo.size() - 1; i >= 0; i--)
		{
			cout << win << "위";
			cout << "\t " << tempscoreInfo[i].getUserScore() << "점";
			cout << "\tID : " << tempscoreInfo[i].getUser()->getUserId() << endl;
			cout << "\tName : " << tempscoreInfo[i].getUser()->getUsername() << endl;
			cout << "\tremain Score : " << tempscoreInfo[i].getUser()->getRemainScore() << endl;
			cout << endl;
			win++;
		}


		User* loseruser;
		int losersum = 0;
		int winnergrade = 1;
		vector<User*> winneruser;

		for (int i = 0; i < tempscoreInfo.size(); i++)
		{
			loseruser = tempscoreInfo[i].getUser();
			loseruser->setRemainScoreingame();

			if (tempscoreInfo[i].getUserScore() > winnergrade)
			{
				winnergrade = tempscoreInfo[i].getUserScore();
				winneruser.clear();
				winneruser.push_back(tempscoreInfo[i].getUser());
			}
			else if (tempscoreInfo[i].getUserScore() == winnergrade)
			{
				winneruser.push_back(tempscoreInfo[i].getUser());
			}
		}


		for (int i = 0; i < tempscoreInfo.size(); i++)
		{
			if (tempscoreInfo[i].getUserScore() < winnergrade)
			{
				losersum += tempscoreInfo[i].getUser()->getbettingScore();
			}
		}


		if (winnergrade == 1)
		{
			cout << "\n\t모두 패배하였습니다." << endl;
		}
		else if (winneruser.size() == tempscoreInfo.size() && winnergrade != 1)
		{
			cout << "\n\t무승부 입니다." << endl;
		}
		else if (winneruser.size() != 1)
		{
			cout << "\n\t승자가 여러명입니다.\n";
			cout << " \n\t승자가 얻은 점수는 " << winnergrade << "입니다. ";
			cout << "\n\t승자가 얻은 금액은 " << losersum / winneruser.size() << "입니다." << endl;
			for (int i = 0; i < winneruser.size(); i++)
			{
				winneruser[i]->addscore(losersum / winneruser.size());
				winneruser[i]->addscore(winneruser[i]->getbettingScore());
			}
		}
		else if (winneruser.size() == 1)
		{
			cout << " \n\t승자가 얻은 점수는 " << winnergrade << "입니다. ";
			cout << "\n\t승자가 얻은 금액은 " << losersum << "입니다." << endl;
			winneruser[0]->addscore(winneruser[0]->getbettingScore() + losersum);
		}


		playerList->clear();
		for (int i = 0; i < tempscoreInfo.size(); i++)
		{
			playerList->push_back(tempscoreInfo[i].getUser());
			(*playerList)[i]->deckclear();
		}

		system("pause");
		system("cls");

		cout << "-------게임 후 사용자 현황 --------" << endl;
		for (int i = 0; i<(*playerList).size(); i++)
		{
			cout << "\tID : " << (*playerList)[i]->getUserId() << endl;
			cout << "\tName : " << (*playerList)[i]->getUsername() << endl;
			cout << "\tremain Score : " << (*playerList)[i]->getRemainScore() << endl;
			cout << endl;
		}



	}

private:
	vector<User*>* playerList;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>>* scorePQ;
};

