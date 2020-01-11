#include "Command.h"
#pragma once
class PersonalHitRequest :
	public Command
{
public:
	PersonalHitRequest() {}
	~PersonalHitRequest() {}

	void setprivate(vector<User*>* _playerList, vector<Card*>* _cardDeck, int _requestedPlayerIndex)
	{
		playerList = _playerList;
		cardDeck = _cardDeck;
		requestedPlayerIndex = _requestedPlayerIndex;
		command_name = "------------<";
		command_name += (*playerList)[requestedPlayerIndex]->getUsername();
		command_name += "���� ī�带 ���� �� �޽��ϴ�>-------------------";

	}


	void execute() 
	{
		cout << command_name << endl;
		Card* temp;
		int random;

		temp = ((*cardDeck)[0]);
		(*playerList)[requestedPlayerIndex]->setcard(temp);
		cardDeck->erase(cardDeck->begin());

	}

private:
	vector<User*>* playerList;
	vector<Card*>* cardDeck;
	int requestedPlayerIndex;
};

