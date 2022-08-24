
#ifndef BLACKJACK_H /* ����� */
#define BLACKJACK_H /* �������������� ��������� - ������ */


#include "pch.h"
#include "Func.h"
#include "Utils.h"
#include "UtilsConsole.h"


namespace classApp {

	//������������ ��� ��������� �����
	enum suitmarks
	{ none,
		clubs = 1,
		pikes,
		hearts,
		diamonds,

		last_suitmarks
	};

	//������ �������� ��������� ������
	static const char* Suitmarks[] =
	{
		"none" ,
		"Clubs",
		"Pikes",
		"Hearts",
		"Diamonds",
		"Last_Suitmarks"
	};

	//�������� �� ���������� ������������� ������������ � ������� �������� ��������� ������
	typedef char ERROR__ENUM_SUITMARKS_AND_ARRAY_SIZE_MISMATCH[(sizeof(suitmarks) / sizeof(Suitmarks[0])) != last_suitmarks ? 1 : -1];

	
	//������������ ����������� ����� ����
	enum color
	{
		black = 1,
		red
	};

	//������������ �������� ����
	enum rank
	{
		Two = 2,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace
	};

	//��������� ����������� �����
	struct card
	{
		suitmarks card_suit;
		color card_color;
		rank card_rank;
		int deck_number;//����� ������ �����
	
static const char* getCardSuit(const card* const object);
static const char* getCardColor(const card* const object);
static const char* getCardRank(const card* const object);
static char* toString(const card* const object);

//�������� ���� �� ������������� ����, ����� ������ ���� ������� ������!!!
static bool checkEqualRank(card* tmp[],int cnt);
//�������� �����(index1) ���� ������ �����(index2)
static bool checkRankOK(card* tmp[], int index1, int index2, suitmarks trump_suit);
	};

	enum deck_count
	{
		EASY_DECK = 36,
		STANDART_DECK = 52
	};

	//����� ������ ����
	class Deck
	{
		static int count_;
		
		const deck_count max_card_ = EASY_DECK;

		//��������� ����� �� ������
		int next_card_;

		suitmarks trump_card_ = hearts;
		card deck_[52];
				
		//���������� �������� �����
		void setTrumpCard();

	public:
	//	Deck() = delete;
		Deck(deck_count = STANDART_DECK);
		Deck(const Deck& object);
		~Deck();

		const char* getCardSuit(int index) const;
		const char* getCardColor(int index)const;
		const char* getCardRank(int index)const;

		//���������� �����
		void setCard(card& object, int index_card);
		//��������� ����� �� ������(������ - �������)
		card& getCard(int index);
		//����������� ����� �� ������ � ����������� ���������
		card* getCard();
		//������ ���������� ���� � ���� ������
		int getCntCard();
//��������� ����� ������
		int getDeckNumber(int index);
//���������� ����� ������
		void setDeckNumber(int number);

		//������ �������� �����
		suitmarks getTrumpCard();

		//������������ ����� � ������
		void Shuffle();
		//������� ����� �� ������
		void EmptyCard(int index);
//��������� �� ������� ����� � ������
		bool IsEmpty(int index);
		//methods
		// ��������� ����� - ���������� ����� ������� � ��������� �������������
		//�������� ��� ����� � ������
		char* toString() const;
		//�������� ������ ����� ��� �������� = index
		char* toString(int index) const;

		//operators

		// �������� ������������ ������������
		Deck& operator=(const Deck& object);

		//������ ����� ����� ������������� �������� ���������� []
		card& operator[](int index) {
			if (index >= 0 && index < 52)
				return deck_[index];
			throw exception("Cards: Wrong index.");
		}
	};

	//����� ���(������� � ��������������� �������� ����)
	class Shoes
	{
		static int count_;
		//���������� ��������������� �����
		static int decks_;
		
		//��������� ����� �� ����
		int next_card_;
		//������������ ������ � �������� ����
		Deck* shoes_;
		//����� ���� � ����(�� �������������)
		int size_;

		//���������� ���� �����(������ ����� ���� �� ����)
		void setSpecialCard();
	public:
		Shoes();
		Shoes(const Shoes& object);
		~Shoes();


		// ��������� ����� - ���������� ����� ������� � ��������� �������������
		char* toString() const;

		//������������ ������ � ����� � ����
		void Shuffle();
		//����������� ����� �� ���� � ����������� ���������
		card* getCard() ;
		//���������� ����� � ����
		void setCard(card& object,int index_deck,int index_card);

		//��������� �� ���� �����(�� �������������)
		void IsSpecialCard();

		// �������� ������������ ������������
		Shoes& operator=(const Shoes& object);
	};

	//����� �����(��� ������-������)
	class Player
	{
		static int count_;
		
		//��� ������
		char name_[50];
		//����� ������(� ���������� �������� �� �� ����� ������ 10, ��� ������������� ������ �������� ��������)
		card my_card_[10];
		//����� ��������� ����� � �������(���������� �����)
		int cntCard_;
		//���������� ����� ������
		int rank_;

		//������ ������
		double money;
		//��� ������
		double rate;

	public:
		Player(const char name[50]="�����");
		Player(const char name[50], double money);
		~Player();

		//��������� ����� ��� ������ � ������ ������������ ��������
		double setMoney(bool winner,double koefficient =1.);
		//������ ����� � ������
		double getMoney()const;
		//����������������� ����� �� ������ ������������ � ���������� � ������ ������������ ��������
		//��� 1. � �������� �������� ������ ���� ������� ������!!!
		static void winner(Player& winner, Player& loser, double koefficient = 1.);

		//�������� ���� ����� ����
		void resetCard();
		//��������� ����� �������
		void takeCard(card* card);
		//�������� �� ������� ���� � ������ ������ ������
		bool checkIfAceIsFirstCard();
		//��������� ������ , ����� ������ ���������� ������ �� ������!!!
		void setRate(double rate);
		//������ �� ������ ��� ������!!! � ������ ����
		void setRate();
		//������ ������ ������
		double getRate() const;
		//���������� ���� ���� ������!!!
		void setRank();
		//������ ������������ ���� ������!!! ������� ������� setRank()
		int getRank() const;
		//��� �����
		void hitMe();
		//����...
		void pass();
		//�������� ����� ������(��������������)
		//��� 1 � ��������� ������� ������ ������ �������� �����, ��� ������
		char* toString(int count = 10) const;
	
	};

	//����� �����(��� ������-������)
	class PlayerFool
	{
		static int count_;

		//��� ������
		char name_[50];
		//����� ������
		card my_card_[36];
		int cntCard_; //����� ��������� ����� � �������(���������� �����)

		suitmarks trump_card_ = hearts;
		//�����
		card lost_card_[36];
		int cntLost_card_;

		//����� ���������
		card enemy_card_[36];
		int cntEnemy_card_;

		//���������� ����� ������
		int rank_;

		//������ ������
		double money;
		//��� ������
		double rate;
		 

	public:
		PlayerFool(const char* name = "�����" , double geld = 1000.);
		~PlayerFool();

		//����� ���������� ���� (����� ����� ����� ����)
		void sortCard(char ch = 'C');

		//������ ����� � ������
		double getMoney()const;

		//������ ��� ������
		char* getName();
		//�������� ����, ���� ��� ����� �����!!!
		bool checkCards();

		//�������� �����������
		static int checkPriority(suitmarks trumpSuitmarks, PlayerFool& pl1, PlayerFool& pl2)
		{
			//�������� ������ ��� ���������� ���� �������!!!
			pl1.trump_card_ = trumpSuitmarks;
			pl2.trump_card_ = trumpSuitmarks;
			int tmp1 = pl1.getMinTrumpCard(trumpSuitmarks);
			int tmp2 = pl2.getMinTrumpCard(trumpSuitmarks);
			if (tmp1 == tmp2)
				return genRand(1,2);
			else if (tmp1 > tmp2)
				return 2;
			else 
				return 1;
			return 0;
		}




		//����� ���� �� ����� �� ���������(�� ���������)
		void yourTurn(PlayerFool& opponent);

		//����� ���� �� ���������� �� ���������(����������)
		void notYourTurn(PlayerFool& opponent);

		//�������� ���� � ���������� � � �����
		void checkEnemyCard();


		
		//�������� ���� ����� ����
		void resetCard();
		//��������� ����� �������
		void takeCard(card* card);
		//��������� ����� � �����
		void takeLostCard(card* card);
		//��������� ����� ����������� � ������
		void takeEnemyCard(card* card);
		//����������� ����� �� ������ � ����������� ���������
		card* getCard(int index);
		//����������� ����� �� ����� � ����������� ���������
		card* getLostCard(int index);
		//����������� ����� �� ������ ���� ������(���������) � ����������� ���������
		card* getEnemyCard(int index);
		//������ ���������� ���� � ���� ������
		int getCntCard();
		//������ ���������� ���� � �����
		int getCntLostCard();
		//������ ���������� ���� ��������� � ������
		int getCntEnemyCard();

		//������ �� ������ ��� ������!!! � ������ ����
		void setRate();
		//������ ������ ������
		double getRate() const;
		//���������� ���� ���� ������!!!
		void setRank();
		//������ ������������ ���� ������!!! ������� ������� setRank()
		int getRank() const;
		//������ �������� ����������� ������, ���� ����� ���� � ������� � ������
		int getMinTrumpCard(suitmarks trumpSuitmarks);
		//�������� ����� ������(��������������)
		char* toString(int count = 36) const;

		//�������� �����
		char* toString(char ch) const;

		//����� ����� ��� ������������� ���������
		card* choseCard(int index=0);
		//����� ����� ��� ������������� ��������� �����������
		card* choseCardSpecial(card** table_card, int* cntTable,char ch='A');
	};

	//����� 
	class Blackjack
	{

	public:

		//����������� ����� ����
		static void Game()
		{
			//������ ���� � ������������� ����������� ��������

			//�����
			Player player1("����� 1");
			//������ - ������
			Player dealer("������",10000.);
			//��� � �������� ����
			Shoes gameShoes;
	

			//����� ����� ������� ���������� ������ ������ � ������, ����� �� ������������
			int playerWin = 0;
			int casinoWin = 0;
			//���������� ����������� ���
			int game_counter = 0;

			//����������� ���� ���������� ����
			while (true)
			{
				//������� ����� ������ � ������
				player1.resetCard();
				dealer.resetCard();
			
				//������� ���������� ��� ��������
				cout << endl << "���� � " << ++game_counter << endl;
				cout << endl << "\t ���� (�����) " << playerWin << " : " << casinoWin << " (������)" << endl << endl;
				cout << endl << "� � � �   � � � � � � � � " << endl;

				//������ ������
				player1.setRate();

				dealer.setRate(0.);//����� ������ ������(� ������ ������ ����������� ��� �������� ������!!!)
				
				//������� �����
				//������ ������� �� ��� �����
				//������ ������� ����� �������������
				player1.takeCard(gameShoes.getCard());
				player1.takeCard(gameShoes.getCard());

				dealer.takeCard(gameShoes.getCard());
				dealer.takeCard(gameShoes.getCard());

				//��������� ����
				cout << player1.toString();
				
				cout << dealer.toString(1);//������ ���������� ������ ������ �����(� �� �� �� ���� ������!!!)

				
				//�������� �������������� ���������� - ������ �������
				player1.setRank();//������ ������� ������ �����
				int rankPlayer = player1.getRank();//�������� ����������� ����
				
				//���� 21, �� ��� �������� � �������� ������� ������
				if (rankPlayer == 21)
				{
					//���� � ������ �������� ����� ���, �� ���� ����������� ��������� � � ������!!!
					if (dealer.checkIfAceIsFirstCard())
					{
						//����������� ����-����� � ������, ����� ������� 1 � 1
						//��� �������� ������ �� ��������� ����
						char key[] = { 'Y','y','N','n' };
						while (!inputKey(key, sizeof(key), "Save money(Y) or play waiter(N)\n"))
							cout << "You choose is " << key[0] << endl;

						if ((key[0] == 'Y') || (key[0] == 'y'))
						{
							cout << "You are save money!!!";
							continue;//������ ��������� ����
						}
					}
					else
					{
						cout << "Blackjack!!! You are WINNER!!! PlayerRank = " << rankPlayer << "";
						playerWin++;
						Player::winner(player1, dealer, 1.5);
						//	player1.setMoney(true, 1.5);
						//	dealer.setMoney(false);
					
						continue;//������ ��������� ����
					}
				}
				
				//������ �������� ������

				//�������� ������
				// � ������ ������� ���� �����
				// ����� ����� ���� �����
				player1.setRank();
				while ((rankPlayer=player1.getRank()) < 21)
				{
					char key[] = { 'E','e','H','h' };
					while(!inputKey(key, sizeof(key), "Your step? Hit(H) or Enough(E)\n"))
						cout << "You choose is " << key[0] << endl;
					
					if ((key[0] == 'H') || (key[0] == 'h'))
					{
						player1.hitMe();//����� ����� ��� �����
						player1.takeCard(gameShoes.getCard());
						//��������� ����
						cout << player1.toString();
					}
					if ((key[0] == 'E') || (key[0] == 'e'))
					{
						player1.pass();//����� �����, ��� ���������� ����
						break;
					}
					player1.setRank();
				}
				
				// �������� �� ��������� �� ������� � ������
				if (rankPlayer > 21)
				{
					cout << endl << "\nBrute force!!! You are LOSER!!! PlayerRank = " << rankPlayer << "\n" << endl;
					casinoWin++;
					
					Player::winner(dealer, player1);
					//player1.setMoney(false);
					//dealer.setMoney(true);

					continue;//������� � ��������� ����
				}

				//�������� ���� ������
				dealer.setRank();//������ ��� � ������ �� �����
				int rankDealer = dealer.getRank();
				cout << dealer.toString();//������� ��� ����� ������

				//���� � ������ 21, �� ��������� ��� ������ ����� ��� � ���� 21
				if (rankDealer == 21)
				{
					if (rankPlayer == rankDealer)
					{
						//� ��������� ������, � ���� ������ ���������� ��� ����� ������
						//					cout << "Push!!! Casino WIN!!!";
						//					casinoWin++;
						//					Player::winner(dealer, player1);
						//					//player1.setMoney(false);
						//					//dealer.setMoney(true);
						cout << "\nPush!!! You are save money!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
					}
					else if (rankPlayer < rankDealer)
					{
						cout << "\nYou are LOSER!!! Casino WIN!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
						casinoWin++;
						Player::winner(dealer, player1);
						//player1.setMoney(false);
						//dealer.setMoney(true);
					}
					continue;//������� � ��������� ����
				}

				//����� ������(����� ����)
				dealer.setRank();
				//������ ������ �������� ����� ���� �� ������ �� ����� 17 �����
				while ((rankDealer = dealer.getRank()) < 17)
				{
					dealer.takeCard(gameShoes.getCard());
					//��������� ����
					cout << dealer.toString();
					dealer.setRank();
				}

				//� ������ ��������, ���������� ������
				if (rankDealer > 21)
				{
					cout << "\nYou are WINNER!!! Casino LOSE!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
					playerWin++;
					Player::winner(player1, dealer, 1.5);
					
					continue;//������� � ��������� ����
				}

				if (rankPlayer == rankDealer)
				{
					//� ��������� ������, � ���� ������ ���������� ��� ����� ������
					//					cout << "Push!!! Casino WIN!!!";
					//					casinoWin++;
					//					Player::winner(dealer, player1);
					//					//player1.setMoney(false);
					//					//dealer.setMoney(true);
					cout << "\nPush!!! You are save money!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
				}
				else if (rankPlayer < rankDealer)
				{
					cout << "\nYou are LOSER!!! Casino WIN!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
					casinoWin++;
					Player::winner(dealer, player1);
					//player1.setMoney(false);
					//dealer.setMoney(true);
				}
				else 
				{
					cout << "\nYou are WINNER!!! Casino LOSE!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
					playerWin++;
					Player::winner(player1,dealer,1.5);
					//player1.setMoney(true, 1.5);
					//dealer.setMoney(false,);
				}

				//���� ����������� ������, �������� ������
				if (player1.getMoney() == 0.)
				{
					cout << endl << "\n���� ���������. � ��� ����������� ������. ������� � ��������� ���!" << endl;
					break;
				}

				cout << endl << "\n���� ���������. ������� �������� ������?" << endl;
				//char c;
				//cin >> c;
				if (inputKey())break;
			}//while

		}

	
	};

	//����� 
	class Card_Game_Fooler
	{
		static void infoStartKON(PlayerFool& player, PlayerFool& computer, Deck& gameDeck)
		{
			//!!! ������ ��� �������
//			computer.sortCard('A');
//			computer.sortCard('B');
//			cout << endl << computer.toString('A');
//			cout << endl << computer.toString('B');
			//!!! ������ ��� �������

			//������� ������
			cout << endl << "�������� �����: " << Suitmarks[gameDeck.getTrumpCard()];// card::toString(&TrumpCard);
			cout << "\n� ������ ���: " << gameDeck.getCntCard();
			cout << "\n���� ������ ���: " << computer.getCntLostCard() << endl;

			player.sortCard();//����������� ����� �� �����
			cout << player.toString();//������� ���� �����

			computer.sortCard();//����������� ����� �� �����

			//!!! ������ ��� �������
//			cout << endl << computer.toString();//������� ����� ����������
			//!!! ������ ��� �������
		}

	public:

		//����������� ����� ����
		static void Game()
		{
			//������ ���� � ������������� ����������� ��������

			//�����
			PlayerFool player1("����� 1");
			//������ - ������
			PlayerFool computer("���������");

			card TrumpCard;
			

			//����� ����� ������� ���������� ������ ������ � ����������, ����� �� ������������
			int playerWin = 0;
			int computerWin = 0;
			//���������� ����������� ���
			int game_counter = 0;

			int countCard = 0;//���������� ������� �� ���������(�� ����� 6��!!!)

				//����������� ���� ���������� ����
			while (true)
			{
				//������� ����� ������ � ����������
				player1.resetCard();
				computer.resetCard();

				//������ ����
				Deck gameDeck(EASY_DECK);
				//���������� ������
				gameDeck.Shuffle();
				TrumpCard = card(gameDeck.getCard(0));//��������� ��� ������
//				//������� ������
//				cout << endl << "�������� �����: " << Suitmarks[gameDeck.getTrumpCard()];// card::toString(&TrumpCard);
//				
//				//������� ���������� ��� ��������
//				cout << endl << "��� � " << ++game_counter << endl;
//				cout << endl << "\t ���� (�����) " << playerWin << " : " << computerWin << " (���������)" << endl << endl;
//				cout << endl << "� � � �   � � � � � � � � " << endl;


				//����� � ���� ������ �� ������. ��� �� �����������, �� �����������. 
				//������ ������ � ���� �������� ����������� ��������� �����, ������ ��������� ������ (���������� ���� ���� ������)


				//������� �����
				//������ ������� �� 6�� ���� �� �����
				//��� ��� ����� ���������, �� ����� ���� ���������
				//������ ������� ����� �������������
				for (int i = 0; i < 6; i++)
				{
					player1.takeCard(gameDeck.getCard());
					computer.takeCard(gameDeck.getCard());
				}


				//�������� �������, � ������ ���� ��� 6�� ���� ����� �����, ����� ����������� ���������!!!
				if (computer.checkCards())
				{
					cout << endl << computer.getName() << ": All cards with the same suitmarks!!!";

					anyKey();
					continue;//������ ��������� ����
				}
				if (player1.checkCards())
				{
					//����� � ���������� �����
					char key[] = { 'Y','y','N','n' };
					while (!inputKey(key, sizeof(key), "Want new distribution of cards(Y) or play waiter(N)\n"))
						cout << "You choose is " << key[0] << endl;

					if ((key[0] == 'Y') || (key[0] == 'y'))
					{
						cout << endl << player1.getName() << ": All cards with the same suitmarks!!!";

						anyKey();
						continue;//������ ��������� ����
					}
				}

				//infoStartKON(player1, computer, gameDeck);

				//������� ��������� ������ ���� ����������� � �����
				card* lost_card[12]{ nullptr };//� ����� �� ����� 12 ����, 6 ���������� � 6 ���� ��������
				int cntLost_card = 0;

				//��������� �����������, ������� ������ ������� �����
				switch (int priority = PlayerFool::checkPriority(gameDeck.getTrumpCard(), computer, player1))
				{
					// !!! ���������� ���� �������� !!!
				START_KON:
				case 1:
					if (priority)
						cout << endl << "Computer have minimum Trump Card";
					priority = 0;

					countCard = 0;//���������� ������� � ����
					
					coutColor("\nYour turn Computer.\n", wAttributeSpecial);

					infoStartKON(player1, computer, gameDeck);

					do
					{
						if (countCard++ == 6) break;//������� ����� 6�� ������� ����
						
						coutColor("\n\n *** Computer (�����) *** \n", wAttributeSpecial);
						//����������� ����� �� ���������� �� ������
						cout << endl;
						//��������� �������� ����� ��� ������ �� ������
						lost_card[cntLost_card++] = computer.choseCardSpecial(lost_card,&cntLost_card);
//						lost_card[cntLost_card++] = computer.choseCard();
						//���� ���� ������ ���, �� �����, �������� ���� ������
						if ((lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							&&(cntLost_card>1))//���� ���� ����� �� ����� ����!!!
							break;
						
						//�������� �� ������������ ����:
						//����� ��������� � ����, ���� ������������!!!
						if (cntLost_card > 1)
							if (!card::checkEqualRank(lost_card,cntLost_card))//�������� �� ������������ ����� � ���� �� ������
							{
								cout << endl << "Computer: Wrong card. Choose another card." << endl;
								//����� ������� �����������!!!
								computer.takeCard(lost_card[--cntLost_card]);
								//����� �� ���� ���������, �������
								lost_card[cntLost_card] = nullptr;

								countCard--;//����� �� ������!!!
								continue;//��������� ������ �����
							};

						//��������(���������) ���� �����, ������� �������
						computer.takeLostCard(lost_card[cntLost_card - 1]);

						coutColor("\n\n *** Player1 (����������) *** \n", wAttributeSpecial);
						cout << endl;

						do
						{
							//����� �������� �����, ���� ������ ����� �� ����������
//							lost_card[cntLost_card++] = player1.choseCardSpecial(lost_card, &cntLost_card);
							lost_card[cntLost_card++] = player1.choseCard();
							
							//���� ����� ���, �� ��� ����� � ����� �������� ��� �����
							//� ����� �� ����� 6 ���� � 5�� �� �������������
							if (lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							{
								cntLost_card--;
								for (int i = 0; i < cntLost_card; i++)
								{
									coutColor("\n ����� ���� �����!!! \n", wAttributeSpecial);
									//����� ������ ��� �����
									player1.takeCard(lost_card[i]);
									//��������(���������) �������� ����� ����� ������ ������
									computer.takeEnemyCard(lost_card[i]);
									//����� ���� ���������, �������
									lost_card[i] = nullptr;
									//������ ����� �� ��������, ��� ������ � ������
									computer.getLostCard(computer.getCntLostCard() - 1);
								}

								//����� ���� �����, ������ ������ �� ������!!!
								cntLost_card = 0;//������� ����� �� �����

								countCard = 0;//������� ����� ����

								//����� ���� ����� ����
								//������� ��������
								while ((computer.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
									computer.takeCard(gameDeck.getCard());
								//���� ���� ������ ��� � ��� ������, �� ��������� ����������(�� ������)
								if (
									(gameDeck.getCntCard() == 0)
									&& (player1.getCntCard() != 0)
									&& (computer.getCntCard() == 0)
									)
								{
									computerWin++;
									goto EXIT;
								}

								infoStartKON(player1, computer, gameDeck);

								break;
							}


							//����� 
							//����������� ����, ����� ����, ���� ���� ���� � ����� ����� ��� ������
							if (card::checkRankOK(lost_card, cntLost_card - 1, cntLost_card - 2, gameDeck.getTrumpCard()))
							{
								//��������(���������) ���� �����, ������� ��������
								computer.takeLostCard(lost_card[cntLost_card - 1]);

								//���� ���� ������ ��� � ��� ������, �� ��������� ����������(�� ������)
								if (
									(gameDeck.getCntCard() == 0)
									&& (player1.getCntCard() == 0)
									&& (computer.getCntCard() != 0)
									)
								{
									playerWin++;
									goto EXIT;
								}														

								break; //����� ������ �������
							}

							//����� ������� �����������!!!
							player1.takeCard(lost_card[--cntLost_card]);
							//����� �� ���� ���������, �������
							lost_card[cntLost_card] = nullptr;

							cout << endl << "Player1: Wrong card. Choose another card." << endl;

						} while (true);


					} while (true);
					
					coutColor("\n\n *** ����� *** \n", wAttributeSpecial);
					coutColor("����� ����!!!\n", wAttributeSpecial);

					cntLost_card = 0;//������� ����� �� �����

					//����� ���� ����� ����
					//������� ��������
					while ((computer.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						computer.takeCard(gameDeck.getCard());

					//����� ��� �� ������� �������

					//� ����� �������� ����� ������������
					while ((player1.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						player1.takeCard(gameDeck.getCard());

					//���� ���� ������ ��� � ��� ������, �� ��������� ����������(�� ������)
					if (
						(gameDeck.getCntCard() == 0)
						&& (player1.getCntCard() != 0)
						&& (computer.getCntCard() == 0)
						)
					{
						computerWin++;
						break;
					}
					if (
						(gameDeck.getCntCard() == 0)
						&& (player1.getCntCard() == 0)
						&& (computer.getCntCard() != 0)
						)
					{
						playerWin++;
						break;
					}

					anyKey();
				case 2:
					if (priority)
						cout << endl << "Player have minimum Trump Card";
					priority = 0;

					countCard = 0;//���������� ������� � ����

					coutColor("\nYour turn Player1.\n", wAttributeSpecial);

					infoStartKON(player1, computer, gameDeck);

					do
					{
						if (countCard++ == 6) break;//������� ����� 6�� ������� ����

						coutColor("\n\n *** Player1 (�����)*** \n", wAttributeSpecial);
						//����������� ����� �� ������ �� ���������
						cout << endl;
						//����� �������� �����, ���� �������� �� ���������
//						lost_card[cntLost_card++] = player1.choseCardSpecial(lost_card, &cntLost_card);
						lost_card[cntLost_card++] = player1.choseCard();

						//���� ���� ������ ���, �� �����, �������� ���� ������
						if ((lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							&& (cntLost_card > 1))//���� ���� ����� �� ����� ����!!!
							break;

						//�������� �� ������������ ����:
						//����� ��������� � ����, ���� ������������!!!
						if (cntLost_card > 1)
							if (!card::checkEqualRank(lost_card, cntLost_card))//�������� �� ������������ ����� � ���� �� ������
							{
								cout << endl << "Player1: Wrong card. Choose another card." << endl;
								//����� ������� �����������!!!
								player1.takeCard(lost_card[--cntLost_card]);
								//����� �� ���� ���������, �������
								lost_card[cntLost_card] = nullptr;

								countCard--;//����� �� ������!!!
								continue;//��������� ������ �����
							};

						//��������(���������) ���� �����, c ������� �� ���� ��������
						computer.takeLostCard(lost_card[cntLost_card - 1]);

						coutColor("\n\n *** Computer (����������) *** \n", wAttributeSpecial);
						cout << endl;

						do
						{
							//��������� �������� ����� ���� ��������
							lost_card[cntLost_card++] = computer.choseCardSpecial((card**)lost_card, &cntLost_card);
//							lost_card[cntLost_card++] = computer.choseCard();

							//���� ����� ���, �� ��� ����� � ��������� �������� ��� �����
							//� ����� �� ����� 6 ���� � 5�� �� �������������
							if (lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							{
								cntLost_card--;
								for (int i = 0; i < cntLost_card; i++)
								{
									coutColor("\n ��������� ���� �����!!! \n", wAttributeSpecial);
									//��������� ������ ��� �����
									computer.takeCard(lost_card[i]);
									//����� ���� ���������, �������
									lost_card[i] = nullptr;
									//������ ����� �� ��������, ��� ������ � ����������
									computer.getLostCard(computer.getCntLostCard() - 1);
								}
								
								//����� ���� ����� ����
								cntLost_card = 0;//������� ����� �� �����
								
								countCard = 0;//������� ����� ����

								//����� ���� ����� ����
								//������� ��������
								while ((player1.getCntCard() < 6) && (gameDeck.getCntCard()>0))
									player1.takeCard(gameDeck.getCard());

								//���� ���� ������ ��� � ��� ������, �� ��������� ����������(�� ������)
								if (
									(gameDeck.getCntCard() == 0)
									&& (player1.getCntCard() == 0)
									&& (computer.getCntCard() != 0)
									)
								{
									playerWin++;
									goto EXIT;
								}

								infoStartKON(player1, computer, gameDeck);

								break;
							}

							//����� 
							//����������� ����, ����� ����, ���� ���� ���� � ����� ����� ��� ������
							if (card::checkRankOK(lost_card, cntLost_card - 1, cntLost_card - 2, gameDeck.getTrumpCard()))
							{
								//��������(���������) ���� �����, ������� ��������
								computer.takeLostCard(lost_card[cntLost_card - 1]);

								//���� ���� ������ ��� � ��� ������, �� ��������� ����������(�� ������)
								if (
									(gameDeck.getCntCard() == 0)
									&& (player1.getCntCard() != 0)
									&& (computer.getCntCard() == 0)
									)
								{
									computerWin++;
									goto EXIT;
								}

								break; //����� ������ �������
							}

							//����� ������� �����������!!!
							computer.takeCard(lost_card[--cntLost_card]);
							//����� �� ���� ���������, �������
							lost_card[cntLost_card] = nullptr;
							
							cout << endl << "Computer: Wrong card. Choose another card." << endl;

						} while (true);
											
					} while (true);

					coutColor("\n\n *** ����� *** \n", wAttributeSpecial);
					coutColor("����� ����!!!\n", wAttributeSpecial);

					cntLost_card = 0;//������� ����� �� �����
				   					 				  				  
					//����� ���� ����� ����
					//������� ��������
					while ((player1.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						player1.takeCard(gameDeck.getCard());
	
					//����� ��� �� ������� �������

					//� ����� �������� ����� ������������
					while ((computer.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						computer.takeCard(gameDeck.getCard());

					//���� ���� ������ ��� � ��� ������, �� ��������� ����������(�� ������)
					if (
						(gameDeck.getCntCard() == 0)
						&& (player1.getCntCard() != 0)
						&& (computer.getCntCard() == 0)
						)
					{
						computerWin++;
						break;
					}
					if (
						(gameDeck.getCntCard() == 0)
						&& (player1.getCntCard() == 0)
						&& (computer.getCntCard() != 0)
						)
					{
						playerWin++;
						break;
					}


					anyKey();
					goto START_KON;
				default:
					cout << endl << "Error. All players have the same Trump Card";
					anyKey();
				}
							   
				EXIT:
				//������� ���������� ��� ��������
				cout << endl << "��� � " << game_counter << " ��������" << endl;
				cout << endl << "\t ���� (�����) " << playerWin << " : " << computerWin << " (���������)" << endl << endl;

				cout << endl << "\n���� ���������. ������� ����� ��-�� �����?" << endl;
				if (inputKey())break;
			}//while

		}


	};//CARD_GAME_FOOLER

	void TestClassCards();
	void TestClassShoes();
	void TestClassBlackjack();

}// classApp


#endif //BLACKJACK_H

