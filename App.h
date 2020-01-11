#include "CommandFactory.h"
#include "GameCommandInvoker.h"
#include <fstream>
#pragma once
class App
{
public:
	App()
	{
		readUserFile();
	}

	~App()
	{
		writeUserFile();
	}

	void run()
	{

		Command* replaycommand = NULL;	//리플레이 로그를 저장할 Command 객체

		login();	//로그인

		if (playerList.size() == 0)	//아무도 로그인 하지 않았을 때
			return;

		// 사용자 전체 메뉴
		int command;	//입력값
		while (1)
		{
			system("pause");
			system("cls");

			int AIcount = 0;	//ai 카운트
			for (int i = 0; i < playerList.size(); i++)	//ai 세기
			{
				if (playerList[i]->getUserId() == -1)
					AIcount++;
			}

			if (AIcount == 0)	//ai가 없다면 함께모드
				AI = 0;
			else	// ai가 있다면 ai모드
				AI = 1;

			if (AI == 0)
				cout << "함께모드";
			else
				cout << "AI모드";

			cout << "\n\t로그인한 사용자 : ";
			for (int i = 0; i < playerList.size(); i++)
				cout << i + 1 << ", " << playerList[i]->getUsername() << "\t";
			cout << "\n\n\t메뉴"
				<< "\n\t1. 플레이 게임"
				<< "\n\t2. 지난 경기 다시 보기"
				<< "\n\t3. 로그인한 사용자 정보 보기"
				<< "\n\t4. User 추가 로그인"
				<< "\n\t5.  AI  추가 로그인(AI모드 일때)"
				<< "\n\t6. User 로그아웃"
				<< "\n\t7.  AI  로그아웃"
				<< "\n\t0. 종료"
				<< "\n\t->";
			cin >> command;


			switch (command)
			{
			case 1:
				if (playerList.size() >= 2)
					playGame();
				replaycommand = gci.getcurCommand();
				break;
			case 2:
				gci.setcurCommand(replaycommand);
				showReplay();
				break;
			case 3:
				for (int i = 0; i < playerList.size(); i++)
				{
					cout << endl;
					cout << "\tID : " << playerList[i]->getUserId() << endl
						<< "\tName : " << playerList[i]->getUsername() << endl
						<< "\tScore : " << playerList[i]->getRemainScore() << endl;
				}
				cout << endl;
				break;
			case 4:
				if (AI == 0)
					login();
				else
				{
					cout << "\n\t함께모드일 때 이용가능합니다\n\n";

				}
				break;
			case 5:
				AIlogin();
				break;
			case 6:
				if (playerList.size() < 2)
					cout << "\n\t사용자가 여려명일 때 이용가능합니다.\n\n";
				else if (AI == 0)
					logout();
				else if (AI == 1)
					cout << "\n\t함께모드일 때 이용가능합니다.\n\n";
				if (playerList.size() == 0)
					return;
				break;
			case 7:
				if (AI == 1)
					AIlogout();
				else
				{
					cout << "\n\tAI모드일 때 이용가능합니다.\n\n";
				}
				break;
			case 0:
				return;
			default:
				break;
			}

		}
	}


	void login()
	{

		int AIselect = 0;
		int playernum;

		cout << "\n\t게임을 할 플레이어 수(0 : 나가기) : ";
		cin >> playernum;
		if (playernum == 0)
			return;
		else if (playernum + playerList.size() > userList.size())
		{
			cout << "\n\t사용자 입력이 너무 많습니다!" << endl;
			run();
			return;
		}
		else if (playernum == 1 && playerList.size() == 0)
		{
			cout << "\n\tAI모드로 즐기시겠습니까? Yes : 1, No(exit) : others :";
			cin >> AIselect;
			if (AIselect != 1)
				return;
			else
				AI = 1;

		}
		for (int i = 0; i < playernum; i++)
		{
			while (1)
			{
				User* temp = NULL;

				int id;
				string pw;
				cout << "\n\tID : ";
				cin >> id;

				if (id == 0)
					return;
				cout << "\tPW : ";
				cin >> pw;

				for (int i = 0; i < userList.size(); i++)
				{
					if (userList[i]->getUserId() == id && userList[i]->getPW() == pw)
					{
						temp = userList[i];
					}
				}


				if (temp == NULL)
					cout << "\n\t올바르지 않은 값입니다.\n";
				else
				{
					int j = 0;
					for (int i = 0; i < playerList.size(); i++)
					{
						if (temp == playerList[i])
							j++;
					}

					if (j == 0)
					{
						playerList.push_back(temp);
						cout<<"\t"<<temp->getUsername()<<"님 환영합니다\n";
					}
					else
						cout << "\n\nt이미 로그인되어 있습니다.\n";
					break;
				}
			}
		}


		if (AIselect == 1)
			AIlogin();
	}

	void logout()
	{
		int number, id;

		cout << "\t로그아웃을 할 플레이어 수(0 : 나가기) : ";
		cin >> number;


		for (int i = 0; i < number; i++)
		{
			while (1)
			{
				cout << "\n\tID : ";
				cin >> id;
				if (id == 0)
					return;

				for (int j = 0; j < playerList.size(); j++)
				{
					if (playerList[j]->getUserId() == id)
					{
						cout << "\n\t" << playerList[j]->getUsername() << "님이 로그아웃 하였습니다.\n";
						playerList.erase(playerList.begin() + j);
						id = -1000;
					}
				}

				if (id != -1000)
				{
					cout << "\n\t해당 유저가 존재하지 않습니다.\n\n";
				}
				else
				{
					break;
				}
			}
		}

	}

	void AIlogin()
	{
		int playerusercount = 0;
		int AIcount = 0;
		for (int i = 0; i < playerList.size(); i++)
		{
			if (playerList[i]->getUserId() != -1)
				playerusercount++;
			else if (playerList[i]->getUserId() == -1)
				AIcount++;
		}


		if (playerusercount == 1)
		{
			int AIplayernum;
			cout << "\n\t추가할 AI 수(0 : 나가기) : ";
			cin >> AIplayernum;

			for (int i = 0; i < AIplayernum; i++)
			{
				User* temp = new User;
				temp->setUserId(-1);
				temp->setUsername("AI");
				temp->setRemainScore(10000);

				AIcount++;
				playerList.push_back(temp);
			}
		}
		else
		{
			cout << "\n\t한명만 로그인 되어 있을 때, AI모드를 할 수 있습니다.\n\n";
		}
	}


	void AIlogout()
	{
		int select = 0;

		cout << "\n\t1. AI 모두 삭제 / 2. AI 하나 삭제 : ";
		cin >> select;

		vector<User*> index;
		if (select == 1)
		{
			for (int i = 0; i < playerList.size(); i++)
			{
				if (playerList[i]->getUserId() == -1)
				{
					index.push_back(playerList[i]);
				}
			}

			for (int j = 0; j < index.size(); j++)
			{
				for (int i = 0; i < playerList.size(); i++)
				{
					if (playerList[i] == index[j])
					{
						playerList.erase(playerList.begin() + i);
					}
				}
			}
		}
		else if (select == 2)
		{
			for (int i = 0; i < playerList.size(); i++)
			{
				if (playerList[i]->getUserId() == -1)
				{
					playerList.erase(playerList.begin() + i);
					break;
				}
			}
		}
	}

	
	void readUserFile()
	{
		ifstream ifs("user.txt");
		int userId, remainScore;
		string pw, username;

		User* temp;
		while (!ifs.eof()) {
			ifs >> userId >> pw >> username >> remainScore;
			temp = new User();
			temp->setUserId(userId);
			temp->setPW(pw);
			temp->setUsername(username);
			temp->setRemainScore(remainScore);
			userList.push_back(temp);
		}
		ifs.close();
	}



	void writeUserFile()
	{
		ofstream ofs("user.txt");
		if (!ofs)
		{
			cout << "파일로드 실패, 종료합니다." << endl;
			exit(100);
		}

		for (int i = 0; i < userList.size(); i++)
		{

			ofs << userList[i]->getUserId()
				<< "	"
				<< userList[i]->getPW()
				<< "	"
				<< userList[i]->getUsername()
				<< "	"
				<< userList[i]->getRemainScore();

			if (i != userList.size() - 1)
				ofs << endl;
		}
		ofs.close();
	}

	

	void playGame()
	{

		deck.clear();
		for (int i = 0; i < userList.size(); i++)
		{
			userList[i]->deckclear();
		}
		for (int i = 0; i < playerList.size(); i++)
		{
			playerList[i]->deckclear();
		}

		srand(time(NULL));
		//덱 설정
		Card* temp;

		for (int i = 0; i < 52; i++)
		{
			temp = new Card();
			temp->setnumber(i % 13 + 1);
			temp->setsuit(i / 13 + 1);
			deck.push_back(temp);
		}

		// 덱 셔플
		int left;
		int right;
		Card _temp;
		for (int i = 0; i < 100; i++)
		{
			left = rand() % 52;
			right = rand() % 52;
			temp = deck[left];
			deck[left] = deck[right];
			deck[right] = temp;
		}

		system("cls");


		if (AI == 0)	//함께모드 일때만 배당 금액을 설정할 수 있다. 
		{
			// 배당 금액 설정
			int tempint;
			cout << "\n";
			for (int i = 0; i < playerList.size(); i++)
			{
				while (1)
				{
					cout << "\t" << playerList[i]->getUsername() << "님의 배당금액 : ";
					cin >> tempint;

					if (tempint == 0 || tempint > playerList[i]->getRemainScore())
					{
						cout << "\t남은 점수가 " << playerList[i]->getRemainScore() << "입니다." << endl;

					}
					else
					{
						playerList[i]->setbettingScore(tempint);
						break;
					}
				}

				playerList[i]->setbettingScore(tempint);
			}
		}
		else if (AI == 1)
		{
			for (int i = 0; i < playerList.size(); i++)
			{
				playerList[i]->setbettingScore(200);	//ai모드일때는 자동으로 200점이 설정됨
				cout << "\t" << playerList[i]->getUsername() << "님의 배당금액 : " << playerList[i]->getbettingScore() << endl;
			}
		}


		//리플레이 플레이어, 덱 설정
		playerListForReplay.clear();
		for (int i = 0; i < playerList.size(); i++)
		{
			User* tempuser = new User;
			*tempuser = *playerList[i];
			playerListForReplay.push_back(tempuser);
		}

		shuffledDeckForReplay.clear();
		for (int i = 0; i < deck.size(); i++)
		{
			Card* tempcard = new Card;
			*tempcard = *deck[i];
			shuffledDeckForReplay.push_back(tempcard);
		}



		CommandFactory* commandF = CommandFactory::getInstance(); //commandfactory 싱글톤 패턴

		system("pause");
		system("cls");

		Replay* newreplay = (Replay*)commandF->getCommand(5);	//replaylog저장을 위한 객체 선언


																//처음 2장씩 가지기
		InitialCardDistribution* newcommandini = (InitialCardDistribution*)commandF->getCommand(3); //커멘트 팩토리에서 커멘드 생성하기
		newcommandini->setprivate(&playerList, &deck);	//필요한 정보 저장
		gci.setcurCommand(newcommandini);	//현재 커멘드로 설정
		gci.executeCommand();	//현재 코멘드 실행

		InitialCardDistribution* replaytempini = (InitialCardDistribution*)commandF->getCommand(3);	//replay로그 저장을 위한 커멘드 생성하기
		replaytempini->setprivate(&playerListForReplay, &shuffledDeckForReplay);	//리플레이 리스트. 덱 정보 저장
		newreplay->addCommandToLog(replaytempini);	//replaylog 저장

		int count = playerList.size();	//플레이어 수
		vector<User*> dontuser;	//그만 받겠다고 선언한 유저

		while (1)
		{
			if (count == 0)	//더이상없는가?
				break;

			cout << endl;
			// 처음 패자 체크, 받은 사람 패자 체크
			CheckLoser* newcommandloser = (CheckLoser*)commandF->getCommand(1);
			newcommandloser->setprivate(&playerList, &scorePQ);
			gci.setcurCommand(newcommandloser);
			gci.executeCommand();

			CheckLoser* replaytemploser = (CheckLoser*)commandF->getCommand(1);
			replaytemploser->setprivate(&playerListForReplay, &scorePQForReplay);
			newreplay->addCommandToLog(replaytemploser);
			//// command 추가			

			system("pause");
			system("cls");

			int inputc;	//계속할건지 묻는 변수 1이면 계속하고 나머지는 계속하지 않는다.
			count = 0;
			int n = 0;

			for (int i = 0; i < (playerList).size(); i++)
			{
				(playerList)[i]->printMyInformation();
				UserScoreInfo loser;
				loser.setUser((playerList)[i]);
				cout << "\t" << loser.calculateScore() << "점 입니다." << endl << endl;
			}

			for (int i = 0; i < playerList.size(); i++)
			{
				n = 0;
				for (int j = 0; j < dontuser.size(); j++)
				{
					if (dontuser[j] == playerList[i])
					{
						n++;
					}
				}

				cout << endl;
				if (n == 0)
				{
					cout << "\t" << playerList[i]->getUsername() << "님, 계속하시겠습니까? Yes : 1 / No : other\n\t- > ";
					cin >> inputc;

					PersonalHitRequest* newcommandreq;
					PersonalHitRequest* replaytempreq;
					switch (inputc)
					{
					case 1:
						count++;
						newcommandreq = (PersonalHitRequest*)commandF->getCommand(4);
						newcommandreq->setprivate(&playerList, &deck, i);
						gci.setcurCommand(newcommandreq);
						gci.executeCommand();

						replaytempreq = (PersonalHitRequest*)commandF->getCommand(4);
						replaytempreq->setprivate(&playerListForReplay, &shuffledDeckForReplay, i);
						newreplay->addCommandToLog(replaytempreq);
						break;
					default:
						dontuser.push_back(playerList[i]);
						break;
					}
				}

			}
			system("pause");
			system("cls");

		}

		// 승자 체크
		CheckWinner* newCommandwin = (CheckWinner*)commandF->getCommand(2);
		newCommandwin->setprivate(&playerList, &scorePQ);
		gci.setcurCommand(newCommandwin);
		gci.executeCommand();

		CheckWinner* replaytempwin = (CheckWinner*)commandF->getCommand(2);
		replaytempwin->setprivate(&playerListForReplay, &scorePQForReplay);
		newreplay->addCommandToLog(replaytempwin);


		system("pause");
		system("cls");

		// 배당 점수 지급

		gci.setcurCommand(newreplay);	//gameinvoker의 curCommand를 replay로 설정
	}


	void showReplay()
	{
		vector<Card*> tempDeckForReplay;	//리플레이를 무한으로 하기 위해 deck저장
		vector<User*> tempUserForReplay;	//리플레이를 무한으로 하기 위해 user저장

		tempUserForReplay.clear();
		for (int i = 0; i < playerListForReplay.size(); i++)
		{
			User* tempuser = new User;
			*tempuser = *playerListForReplay[i];
			tempUserForReplay.push_back(tempuser);
		}

		tempDeckForReplay.clear();
		for (int i = 0; i < shuffledDeckForReplay.size(); i++)
		{
			Card* tempcard = new Card;
			*tempcard = *shuffledDeckForReplay[i];
			tempDeckForReplay.push_back(tempcard);
		}


		//모든 사용자들의 deck 클리어
		for (int i = 0; i < playerListForReplay.size(); i++)
		{
			playerListForReplay[i]->deckclear();
		}

		//리플레이 진행
		gci.executeCommand();


		//플레이어 리스트 forReplay 초기화 후 저장해 놓은 forReplay 저장
		playerListForReplay.clear();
		for (int i = 0; i < tempUserForReplay.size(); i++)
		{
			User* tempuser2 = new User;
			*tempuser2 = *tempUserForReplay[i];
			playerListForReplay.push_back(tempuser2);
		}

		shuffledDeckForReplay.clear();
		for (int i = 0; i < tempDeckForReplay.size(); i++)
		{
			Card* tempcard2 = new Card;
			*tempcard2 = *tempDeckForReplay[i];
			shuffledDeckForReplay.push_back(tempcard2);
		}

	}
private:
	vector<User*> userList;
	vector<User*> playerList;
	vector<User*> playerListForReplay;

	vector<Card*> deck;
	vector<Card*> shuffledDeckForReplay;

	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQ;
	priority_queue<UserScoreInfo, vector<UserScoreInfo>, less<UserScoreInfo>> scorePQForReplay;

	GameCommandInvoker gci;


	bool AI;	//0 : 다른사람과 같이 게임, 1 : 혼자 게임
};

