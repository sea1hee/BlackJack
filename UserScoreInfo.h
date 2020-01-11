#include "User.h"
#include <cstdlib>
#include <ctime>
#pragma once
class UserScoreInfo
{
public:
	UserScoreInfo(){}
	~UserScoreInfo() {}

	void setUser(User* temp)
	{
		user = temp;
	}
	void setUserScore(int userscore)
	{
		score = userscore;
	}

	User* getUser()
	{
		return user;
	}

	int getUserScore()
	{
		return score;
	}
	int calculateScore() 
	{
		srand(time(NULL));

		vector<Card*>* temp = user->getcard();

		int _score;
		int tempscore;
		int sum = 0;
		for (int i = 0; i < temp->size(); i++)
		{
			_score = (*temp)[i]->getnumber();
			
			if (_score == 11 || _score == 12 || _score == 13)
				sum += 10;
			else if (_score == 14)
				sum += 1;
			else if (_score == 15)
				sum += 11;
			else
				sum += _score;
		}

		score = sum;


		if (score > 21)
		{
			score = 0;
		}

		return score;
	}
	void printMyInformation()
	{
		user->printMyInformation();
		cout << "ÇöÀç score : " << score << endl;

	}
	bool operator<(const UserScoreInfo& b) const 
	{
		if (b.score < this->score )
			return true;
		else
			return false;
	}
private:
	User* user;
	int score;
};

