#pragma once
#include "Command.h"

class InitialCardDistribution :
	public Command
{
public:
	InitialCardDistribution() {
		command_name = "--------<초기 카드 분배를 합니다>-------------";
	}
	~InitialCardDistribution() {}


	void setprivate(vector<User*>* _playerList, vector<Card*>* _cardDeck)
	{
		playerList = _playerList;
		cardDeck = _cardDeck;
	}


	void execute()
	{
		cout << command_name << endl;
		int random;
		Card* temp;
		for (int i = 0; i < playerList->size(); i++)
		{
			//첫번째 카드
			temp = ((*cardDeck)[0]);
			(*playerList)[i]->setcard(temp);
			cardDeck->erase(cardDeck->begin());
	

			//두번째 카드
			temp = ((*cardDeck)[0]);
			(*playerList)[i]->setcard(temp);
			cardDeck->erase(cardDeck->begin());

		}

		for (int i = 0; i < (*playerList).size(); i++)
		{
			(*playerList)[i]->printMyInformation();
			UserScoreInfo loser;
			loser.setUser((*playerList)[i]);
			cout << "\t" << loser.calculateScore() << "점 입니다." << endl;

		}
	}
private:
	vector<User*>* playerList;
	vector<Card*>* cardDeck;
};

