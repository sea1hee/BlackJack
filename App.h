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

		Command* replaycommand = NULL;	//���÷��� �α׸� ������ Command ��ü

		login();	//�α���

		if (playerList.size() == 0)	//�ƹ��� �α��� ���� �ʾ��� ��
			return;

		// ����� ��ü �޴�
		int command;	//�Է°�
		while (1)
		{
			system("pause");
			system("cls");

			int AIcount = 0;	//ai ī��Ʈ
			for (int i = 0; i < playerList.size(); i++)	//ai ����
			{
				if (playerList[i]->getUserId() == -1)
					AIcount++;
			}

			if (AIcount == 0)	//ai�� ���ٸ� �Բ����
				AI = 0;
			else	// ai�� �ִٸ� ai���
				AI = 1;

			if (AI == 0)
				cout << "�Բ����";
			else
				cout << "AI���";

			cout << "\n\t�α����� ����� : ";
			for (int i = 0; i < playerList.size(); i++)
				cout << i + 1 << ", " << playerList[i]->getUsername() << "\t";
			cout << "\n\n\t�޴�"
				<< "\n\t1. �÷��� ����"
				<< "\n\t2. ���� ��� �ٽ� ����"
				<< "\n\t3. �α����� ����� ���� ����"
				<< "\n\t4. User �߰� �α���"
				<< "\n\t5.  AI  �߰� �α���(AI��� �϶�)"
				<< "\n\t6. User �α׾ƿ�"
				<< "\n\t7.  AI  �α׾ƿ�"
				<< "\n\t0. ����"
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
					cout << "\n\t�Բ������ �� �̿밡���մϴ�\n\n";

				}
				break;
			case 5:
				AIlogin();
				break;
			case 6:
				if (playerList.size() < 2)
					cout << "\n\t����ڰ� �������� �� �̿밡���մϴ�.\n\n";
				else if (AI == 0)
					logout();
				else if (AI == 1)
					cout << "\n\t�Բ������ �� �̿밡���մϴ�.\n\n";
				if (playerList.size() == 0)
					return;
				break;
			case 7:
				if (AI == 1)
					AIlogout();
				else
				{
					cout << "\n\tAI����� �� �̿밡���մϴ�.\n\n";
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

		cout << "\n\t������ �� �÷��̾� ��(0 : ������) : ";
		cin >> playernum;
		if (playernum == 0)
			return;
		else if (playernum + playerList.size() > userList.size())
		{
			cout << "\n\t����� �Է��� �ʹ� �����ϴ�!" << endl;
			run();
			return;
		}
		else if (playernum == 1 && playerList.size() == 0)
		{
			cout << "\n\tAI���� ���ðڽ��ϱ�? Yes : 1, No(exit) : others :";
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
					cout << "\n\t�ùٸ��� ���� ���Դϴ�.\n";
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
						cout<<"\t"<<temp->getUsername()<<"�� ȯ���մϴ�\n";
					}
					else
						cout << "\n\nt�̹� �α��εǾ� �ֽ��ϴ�.\n";
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

		cout << "\t�α׾ƿ��� �� �÷��̾� ��(0 : ������) : ";
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
						cout << "\n\t" << playerList[j]->getUsername() << "���� �α׾ƿ� �Ͽ����ϴ�.\n";
						playerList.erase(playerList.begin() + j);
						id = -1000;
					}
				}

				if (id != -1000)
				{
					cout << "\n\t�ش� ������ �������� �ʽ��ϴ�.\n\n";
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
			cout << "\n\t�߰��� AI ��(0 : ������) : ";
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
			cout << "\n\t�Ѹ� �α��� �Ǿ� ���� ��, AI��带 �� �� �ֽ��ϴ�.\n\n";
		}
	}


	void AIlogout()
	{
		int select = 0;

		cout << "\n\t1. AI ��� ���� / 2. AI �ϳ� ���� : ";
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
			cout << "���Ϸε� ����, �����մϴ�." << endl;
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
		//�� ����
		Card* temp;

		for (int i = 0; i < 52; i++)
		{
			temp = new Card();
			temp->setnumber(i % 13 + 1);
			temp->setsuit(i / 13 + 1);
			deck.push_back(temp);
		}

		// �� ����
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


		if (AI == 0)	//�Բ���� �϶��� ��� �ݾ��� ������ �� �ִ�. 
		{
			// ��� �ݾ� ����
			int tempint;
			cout << "\n";
			for (int i = 0; i < playerList.size(); i++)
			{
				while (1)
				{
					cout << "\t" << playerList[i]->getUsername() << "���� ���ݾ� : ";
					cin >> tempint;

					if (tempint == 0 || tempint > playerList[i]->getRemainScore())
					{
						cout << "\t���� ������ " << playerList[i]->getRemainScore() << "�Դϴ�." << endl;

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
				playerList[i]->setbettingScore(200);	//ai����϶��� �ڵ����� 200���� ������
				cout << "\t" << playerList[i]->getUsername() << "���� ���ݾ� : " << playerList[i]->getbettingScore() << endl;
			}
		}


		//���÷��� �÷��̾�, �� ����
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



		CommandFactory* commandF = CommandFactory::getInstance(); //commandfactory �̱��� ����

		system("pause");
		system("cls");

		Replay* newreplay = (Replay*)commandF->getCommand(5);	//replaylog������ ���� ��ü ����


																//ó�� 2�徿 ������
		InitialCardDistribution* newcommandini = (InitialCardDistribution*)commandF->getCommand(3); //Ŀ��Ʈ ���丮���� Ŀ��� �����ϱ�
		newcommandini->setprivate(&playerList, &deck);	//�ʿ��� ���� ����
		gci.setcurCommand(newcommandini);	//���� Ŀ���� ����
		gci.executeCommand();	//���� �ڸ�� ����

		InitialCardDistribution* replaytempini = (InitialCardDistribution*)commandF->getCommand(3);	//replay�α� ������ ���� Ŀ��� �����ϱ�
		replaytempini->setprivate(&playerListForReplay, &shuffledDeckForReplay);	//���÷��� ����Ʈ. �� ���� ����
		newreplay->addCommandToLog(replaytempini);	//replaylog ����

		int count = playerList.size();	//�÷��̾� ��
		vector<User*> dontuser;	//�׸� �ްڴٰ� ������ ����

		while (1)
		{
			if (count == 0)	//���̻���°�?
				break;

			cout << endl;
			// ó�� ���� üũ, ���� ��� ���� üũ
			CheckLoser* newcommandloser = (CheckLoser*)commandF->getCommand(1);
			newcommandloser->setprivate(&playerList, &scorePQ);
			gci.setcurCommand(newcommandloser);
			gci.executeCommand();

			CheckLoser* replaytemploser = (CheckLoser*)commandF->getCommand(1);
			replaytemploser->setprivate(&playerListForReplay, &scorePQForReplay);
			newreplay->addCommandToLog(replaytemploser);
			//// command �߰�			

			system("pause");
			system("cls");

			int inputc;	//����Ұ��� ���� ���� 1�̸� ����ϰ� �������� ������� �ʴ´�.
			count = 0;
			int n = 0;

			for (int i = 0; i < (playerList).size(); i++)
			{
				(playerList)[i]->printMyInformation();
				UserScoreInfo loser;
				loser.setUser((playerList)[i]);
				cout << "\t" << loser.calculateScore() << "�� �Դϴ�." << endl << endl;
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
					cout << "\t" << playerList[i]->getUsername() << "��, ����Ͻðڽ��ϱ�? Yes : 1 / No : other\n\t- > ";
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

		// ���� üũ
		CheckWinner* newCommandwin = (CheckWinner*)commandF->getCommand(2);
		newCommandwin->setprivate(&playerList, &scorePQ);
		gci.setcurCommand(newCommandwin);
		gci.executeCommand();

		CheckWinner* replaytempwin = (CheckWinner*)commandF->getCommand(2);
		replaytempwin->setprivate(&playerListForReplay, &scorePQForReplay);
		newreplay->addCommandToLog(replaytempwin);


		system("pause");
		system("cls");

		// ��� ���� ����

		gci.setcurCommand(newreplay);	//gameinvoker�� curCommand�� replay�� ����
	}


	void showReplay()
	{
		vector<Card*> tempDeckForReplay;	//���÷��̸� �������� �ϱ� ���� deck����
		vector<User*> tempUserForReplay;	//���÷��̸� �������� �ϱ� ���� user����

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


		//��� ����ڵ��� deck Ŭ����
		for (int i = 0; i < playerListForReplay.size(); i++)
		{
			playerListForReplay[i]->deckclear();
		}

		//���÷��� ����
		gci.executeCommand();


		//�÷��̾� ����Ʈ forReplay �ʱ�ȭ �� ������ ���� forReplay ����
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


	bool AI;	//0 : �ٸ������ ���� ����, 1 : ȥ�� ����
};

