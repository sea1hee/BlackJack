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
		command_name += "님이 카드를 한장 더 받습니다>-------------------";

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

