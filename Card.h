#pragma once
#include <iostream>
using namespace std;
#pragma once
class Card
{
public:
	Card(){}
	~Card(){}

	void setnumber(int _number)
	{

		int randomnum = rand() % 2 + 1;
		if (_number == 1)
		{
			if (randomnum = 1)
				number = 15;
			else if (randomnum == 2)
				number = 14;
		}
		else
			number = _number;

		//  1 : 값이 아직 설정되지 않은 A
		// 11 : J
		// 12 : Q
		// 13 : K
		// 14 : 1의 값을 가지도록 설정된 A
		// 15 : 11의 값을 가지도록 설정된 A

	}

	void setsuit(int _suit)
	{
		suit = _suit;
		// 1 : ♠
		// 2 : ◆
		// 3 : ♣
		// 4 : ♥

	}

	int getnumber()
	{
		return number;
	}

	void printMyInformation()
	{
		switch (suit)
		{
		case 1:
			cout << "♠";
			break;
		case 2:
			cout << "◆";
			break;
		case 3:
			cout << "♣";
			break;
		case 4:
			cout << "♥";
			break;
		}

		if (number == 14)
			cout << "A(1)\t";
		else if (number == 15)
			cout << "A(11)\t";
		else if (number == 11)
			cout << "J \t";
		else if (number == 12)
			cout << "Q \t";
		else if (number == 13)
			cout << "K \t";
		else
			cout << number << "\t";
	}
private:
	int number;
	int suit;
};

