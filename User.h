#include "Card.h"
#include "string"
#include <vector>
using namespace std;
#pragma once
class User
{
public:
	User()
	{
		bettingScore = 0;
	}
	~User(){}

	int getUserId()
	{
		return ID;
	}
	string getPW()
	{
		return pw;
	}
	string getUsername()
	{
		return username;
	}
	int getRemainScore()
	{
		return remainScore;
	}

	vector<Card*>* getcard()
	{
		return &cardsInHand; // A의 값을 결정하여 바꿔주기 위함
	}

	int getbettingScore()
	{
		return bettingScore;
	}

	void setbettingScore(int _bettingScore)
	{
		bettingScore = _bettingScore;
	}


	void setUserId(int userId)
	{
		ID = userId;
	}
	void setPW(string userPw)
	{
		pw = userPw;
	}
	void setUsername(string userName)
	{
		username = userName;
	}
	void setRemainScore(int remainscore)
	{
		remainScore = remainscore;
	}
	void setRemainScoreingame()
	{
		remainScore -= bettingScore;
	}

	void setcard(Card* temp)
	{
		cardsInHand.push_back(temp);
	}

	void addscore(int temp)
	{
		remainScore += temp;
	}

	void printMyInformation()
	{
		cout << endl;
		cout << "\tID : " << ID << endl
			<< "\tName : " << username << endl
			<< "\tScore : " << remainScore << endl
			<< "\tCard : ";

		for (int i = 0; i < cardsInHand.size(); i++)
		{
			cardsInHand[i]->printMyInformation();
		}

		cout << endl;
	}

	void deckclear()
	{
		cardsInHand.clear();
	}


private:
	int ID;
	string pw;
	string username;
	int bettingScore;
	int remainScore;
	vector<Card*> cardsInHand;
};

