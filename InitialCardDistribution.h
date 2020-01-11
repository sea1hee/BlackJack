#pragma once
#include "Command.h"

class InitialCardDistribution :
	public Command
{
public:
	InitialCardDistribution() {
		command_name = "--------<�ʱ� ī�� �й踦 �մϴ�>-------------";
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
			//ù��° ī��
			temp = ((*cardDeck)[0]);
			(*playerList)[i]->setcard(temp);
			cardDeck->erase(cardDeck->begin());
	

			//�ι�° ī��
			temp = ((*cardDeck)[0]);
			(*playerList)[i]->setcard(temp);
			cardDeck->erase(cardDeck->begin());

		}

		for (int i = 0; i < (*playerList).size(); i++)
		{
			(*playerList)[i]->printMyInformation();
			UserScoreInfo loser;
			loser.setUser((*playerList)[i]);
			cout << "\t" << loser.calculateScore() << "�� �Դϴ�." << endl;

		}
	}
private:
	vector<User*>* playerList;
	vector<Card*>* cardDeck;
};

