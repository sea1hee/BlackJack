#pragma once
#include "Command.h"
#include <queue>
using namespace std;
class CheckWinner :
	public Command
{
public:
	CheckWinner() {
		command_name = "--------------<�¸��ڸ� �����մϴ�>-------------";
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

		// ��� ���� ����
		vector<UserScoreInfo> tempscoreInfo;
		while (!scorePQ->empty())
		{
			tempscoreInfo.push_back(scorePQ->top());
			scorePQ->pop();
		}

		cout << "-------��� ��Ȳ --------" << endl;
		for (int i = 0; i < tempscoreInfo.size(); i++)
		{
			cout <<"\t" << tempscoreInfo[i].getUser()->getUsername() << "���� ��� �ݾ� : "
				<< tempscoreInfo[i].getUser()->getbettingScore() << endl << endl;
		}
		
		cout << "-------���� ��� --------" << endl;
		int win = 1;
		for (int i = tempscoreInfo.size() - 1; i >= 0; i--)
		{
			cout << win << "��";
			cout << "\t " << tempscoreInfo[i].getUserScore() << "��";
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
			cout << "\n\t��� �й��Ͽ����ϴ�." << endl;
		}
		else if (winneruser.size() == tempscoreInfo.size() && winnergrade != 1)
		{
			cout << "\n\t���º� �Դϴ�." << endl;
		}
		else if (winneruser.size() != 1)
		{
			cout << "\n\t���ڰ� �������Դϴ�.\n";
			cout << " \n\t���ڰ� ���� ������ " << winnergrade << "�Դϴ�. ";
			cout << "\n\t���ڰ� ���� �ݾ��� " << losersum / winneruser.size() << "�Դϴ�." << endl;
			for (int i = 0; i < winneruser.size(); i++)
			{
				winneruser[i]->addscore(losersum / winneruser.size());
				winneruser[i]->addscore(winneruser[i]->getbettingScore());
			}
		}
		else if (winneruser.size() == 1)
		{
			cout << " \n\t���ڰ� ���� ������ " << winnergrade << "�Դϴ�. ";
			cout << "\n\t���ڰ� ���� �ݾ��� " << losersum << "�Դϴ�." << endl;
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

		cout << "-------���� �� ����� ��Ȳ --------" << endl;
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

