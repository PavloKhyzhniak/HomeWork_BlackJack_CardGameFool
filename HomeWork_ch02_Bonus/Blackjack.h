
#ifndef BLACKJACK_H /* Страж */
#define BLACKJACK_H /* единственности вхождения - начало */


#include "pch.h"
#include "Func.h"
#include "Utils.h"
#include "UtilsConsole.h"


namespace classApp {

	//перечисление под карточные масти
	enum suitmarks
	{ none,
		clubs = 1,
		pikes,
		hearts,
		diamonds,

		last_suitmarks
	};

	//массив названий карточных мастей
	static const char* Suitmarks[] =
	{
		"none" ,
		"Clubs",
		"Pikes",
		"Hearts",
		"Diamonds",
		"Last_Suitmarks"
	};

	//проверка на совпадение определенного перечисления и массива названий карточных мастей
	typedef char ERROR__ENUM_SUITMARKS_AND_ARRAY_SIZE_MISMATCH[(sizeof(suitmarks) / sizeof(Suitmarks[0])) != last_suitmarks ? 1 : -1];

	
	//перечисление допустимого цвета карт
	enum color
	{
		black = 1,
		red
	};

	//перечисление номинала карт
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

	//структура описывающая карту
	struct card
	{
		suitmarks card_suit;
		color card_color;
		rank card_rank;
		int deck_number;//номер колоды карты
	
static const char* getCardSuit(const card* const object);
static const char* getCardColor(const card* const object);
static const char* getCardRank(const card* const object);
static char* toString(const card* const object);

//проверка карт на эквивалентный ранг, карты должны быть минимум парами!!!
static bool checkEqualRank(card* tmp[],int cnt);
//проверка карта(index1) бьет нижнюю карту(index2)
static bool checkRankOK(card* tmp[], int index1, int index2, suitmarks trump_suit);
	};

	enum deck_count
	{
		EASY_DECK = 36,
		STANDART_DECK = 52
	};

	//класс Колода карт
	class Deck
	{
		static int count_;
		
		const deck_count max_card_ = EASY_DECK;

		//следующая карта из Колоды
		int next_card_;

		suitmarks trump_card_ = hearts;
		card deck_[52];
				
		//установить козырную масть
		void setTrumpCard();

	public:
	//	Deck() = delete;
		Deck(deck_count = STANDART_DECK);
		Deck(const Deck& object);
		~Deck();

		const char* getCardSuit(int index) const;
		const char* getCardColor(int index)const;
		const char* getCardRank(int index)const;

		//установить карту
		void setCard(card& object, int index_card);
		//запросить карту из колоды(извлеч - удалить)
		card& getCard(int index);
		//затребовать карту из Колоды с последующим удалением
		card* getCard();
		//узнать количество карт в руке Колоде
		int getCntCard();
//запросить номер колоды
		int getDeckNumber(int index);
//установить номер колоды
		void setDeckNumber(int number);

		//узнать козырную масть
		suitmarks getTrumpCard();

		//перетасовать карты в колоде
		void Shuffle();
		//удалить карту из колоды
		void EmptyCard(int index);
//проверить на наличие карты в колоде
		bool IsEmpty(int index);
		//methods
		// служебный метод - приведение полей объекта в строковое представление
		//показать все карты в колоде
		char* toString() const;
		//показать только карту под индексом = index
		char* toString(int index) const;

		//operators

		// оператор присваивания копированием
		Deck& operator=(const Deck& object);

		//запрос карты через перегруженный оператор индексации []
		card& operator[](int index) {
			if (index >= 0 && index < 52)
				return deck_[index];
			throw exception("Cards: Wrong index.");
		}
	};

	//класс Шуз(ботинок с перетасованными колодами карт)
	class Shoes
	{
		static int count_;
		//количнство задействованных колод
		static int decks_;
		
		//следующая карта из Шуза
		int next_card_;
		//динамический массив с колодами карт
		Deck* shoes_;
		//всего карт в Шузе(не используеться)
		int size_;

		//установить спец карту(отсечь часть карт из Шуза)
		void setSpecialCard();
	public:
		Shoes();
		Shoes(const Shoes& object);
		~Shoes();


		// служебный метод - приведение полей объекта в строковое представление
		char* toString() const;

		//перетасовать колоды и карты в Шузе
		void Shuffle();
		//затребовать карту из Шуза с последующим удалением
		card* getCard() ;
		//установить карту в Шузе
		void setCard(card& object,int index_deck,int index_card);

		//проверить на спец карту(не используеться)
		void IsSpecialCard();

		// оператор присваивания копированием
		Shoes& operator=(const Shoes& object);
	};

	//класс Игрок(или Крупье-Казино)
	class Player
	{
		static int count_;
		
		//имя Игрока
		char name_[50];
		//карты Игрока(в простейшем варианте их не будет больше 10, при имплементации сплита возможны варианты)
		card my_card_[10];
		//номер следующей карты в массиве(свободного места)
		int cntCard_;
		//количество очков Игрока
		int rank_;

		//деньги игрока
		double money;
		//его ставка
		double rate;

	public:
		Player(const char name[50]="Игрок");
		Player(const char name[50], double money);
		~Player();

		//установка денег при победе с учетом коэффициента выигрыша
		double setMoney(bool winner,double koefficient =1.);
		//запрос денег у Игрока
		double getMoney()const;
		//перераспределение денег от Игрока проигравшего к победителю с учетом коэффициента выигрыша
		//при 1. в качестве выигрыша должно быть указано Казино!!!
		static void winner(Player& winner, Player& loser, double koefficient = 1.);

		//удаление карт после игры
		void resetCard();
		//получение карты Игроком
		void takeCard(card* card);
		//проверка на наличие Туза у Крупье первой картой
		bool checkIfAceIsFirstCard();
		//установка ставки , когда Казино выигрывает деньги от Игрока!!!
		void setRate(double rate);
		//запрос на ставку для Игрока!!! в начале игры
		void setRate();
		//узнать ставку Игрока
		double getRate() const;
		//просчитать очки карт Игрока!!!
		void setRank();
		//узнать просчитанные очки Игрока!!! сначала вызывай setRank()
		int getRank() const;
		//еще карту
		void hitMe();
		//пасс...
		void pass();
		//Показать карты Игрока(действительные)
		//При 1 в аргументе покажет только первую выданную карту, для Крупье
		char* toString(int count = 10) const;
	
	};

	//класс Игрок(или Крупье-Казино)
	class PlayerFool
	{
		static int count_;

		//имя Игрока
		char name_[50];
		//карты Игрока
		card my_card_[36];
		int cntCard_; //номер следующей карты в массиве(свободного места)

		suitmarks trump_card_ = hearts;
		//отбой
		card lost_card_[36];
		int cntLost_card_;

		//карты оппонента
		card enemy_card_[36];
		int cntEnemy_card_;

		//количество очков Игрока
		int rank_;

		//деньги игрока
		double money;
		//его ставка
		double rate;
		 

	public:
		PlayerFool(const char* name = "Игрок" , double geld = 1000.);
		~PlayerFool();

		//метод сортировки карт (Бубна Трефы Черви Пики)
		void sortCard(char ch = 'C');

		//запрос денег у Игрока
		double getMoney()const;

		//узнать имя игрока
		char* getName();
		//проверка карт, если все одной масти!!!
		bool checkCards();

		//проверка очередности
		static int checkPriority(suitmarks trumpSuitmarks, PlayerFool& pl1, PlayerFool& pl2)
		{
			//запомним козырь для внутренних нужд игроков!!!
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




		//отбой карт Мы ходим на оппонента(на компьютер)
		void yourTurn(PlayerFool& opponent);

		//отбой карт Мы отбиваемся от оппонента(компьютера)
		void notYourTurn(PlayerFool& opponent);

		//проверка карт у противника и в отбое
		void checkEnemyCard();


		
		//удаление карт после игры
		void resetCard();
		//получение карты Игроком
		void takeCard(card* card);
		//получение карты в Отбой
		void takeLostCard(card* card);
		//получение карты находящиеся у Игрока
		void takeEnemyCard(card* card);
		//затребовать карту из Колоды с последующим удалением
		card* getCard(int index);
		//затребовать карту из отбоя с последующим удалением
		card* getLostCard(int index);
		//затребовать карту из памяти карт Игрока(оппонента) с последующим удалением
		card* getEnemyCard(int index);
		//узнать количество карт в руке Игрока
		int getCntCard();
		//узнать количество карт в отбое
		int getCntLostCard();
		//узнать количество карт известных у Игрока
		int getCntEnemyCard();

		//запрос на ставку для Игрока!!! в начале игры
		void setRate();
		//узнать ставку Игрока
		double getRate() const;
		//просчитать очки карт Игрока!!!
		void setRank();
		//узнать просчитанные очки Игрока!!! сначала вызывай setRank()
		int getRank() const;
		//вернем значение наименьшего козыря, если такой есть в наличии у Игрока
		int getMinTrumpCard(suitmarks trumpSuitmarks);
		//Показать карты Игрока(действительные)
		char* toString(int count = 36) const;

		//Показать карты
		char* toString(char ch) const;

		//выбор карты для подбрасывания оппоненту
		card* choseCard(int index=0);
		//выбор карты для подбрасывания оппоненту Компьютером
		card* choseCardSpecial(card** table_card, int* cntTable,char ch='A');
	};

	//класс 
	class Blackjack
	{

	public:

		//статический метод ИГРА
		static void Game()
		{
			//начало игры с инициализации действующих объектов

			//Игрок
			Player player1("Игрок 1");
			//Крупье - Казино
			Player dealer("Крупье",10000.);
			//Шуз с колодами карт
			Shoes gameShoes;
	

			//будем вести подсчет выигрышных партий Игрока и Казино, ничья не учитываеться
			int playerWin = 0;
			int casinoWin = 0;
			//количество проведенных игр
			int game_counter = 0;

			//бесконечный цикл СОБСТВЕННО ИГРА
			while (true)
			{
				//сбросим карты Игрока и Крупье
				player1.resetCard();
				dealer.resetCard();
			
				//Выведем информацию для играющих
				cout << endl << "Игра № " << ++game_counter << endl;
				cout << endl << "\t СЧЕТ (Игрок) " << playerWin << " : " << casinoWin << " (Казино)" << endl << endl;
				cout << endl << "И Г Р А   Н А Ч А Л А С Ь " << endl;

				//делаем ставки
				player1.setRate();

				dealer.setRate(0.);//сброс ставки Крупье(у Крупье ставка появляеться при выигрыше Казино!!!)
				
				//раздаем карты
				//первая раздача по две карты
				//манера раздачи может варьироваться
				player1.takeCard(gameShoes.getCard());
				player1.takeCard(gameShoes.getCard());

				dealer.takeCard(gameShoes.getCard());
				dealer.takeCard(gameShoes.getCard());

				//предпоказ карт
				cout << player1.toString();
				
				cout << dealer.toString(1);//Крупье показывает только первую карту(и то не во всех Казино!!!)

				
				//проверка промежуточного результата - первой раздачи
				player1.setRank();//узнаем сколько набрал Игрок
				int rankPlayer = player1.getRank();//запросим расчитанные очки
				
				//если 21, то это Блэкджек и возможен выигрыш Игрока
				if (rankPlayer == 21)
				{
					//если у Крупье открытая карты Туз, то есть вероятность Блэкджека и у Крупье!!!
					if (dealer.checkIfAceIsFirstCard())
					{
						//вероятность блэк-джека у крупье, взять выигрыш 1 к 1
						//или попытать счатья по окончанию игры
						char key[] = { 'Y','y','N','n' };
						while (!inputKey(key, sizeof(key), "Save money(Y) or play waiter(N)\n"))
							cout << "You choose is " << key[0] << endl;

						if ((key[0] == 'Y') || (key[0] == 'y'))
						{
							cout << "You are save money!!!";
							continue;//начать следующую игру
						}
					}
					else
					{
						cout << "Blackjack!!! You are WINNER!!! PlayerRank = " << rankPlayer << "";
						playerWin++;
						Player::winner(player1, dealer, 1.5);
						//	player1.setMoney(true, 1.5);
						//	dealer.setMoney(false);
					
						continue;//начать следующую игру
					}
				}
				
				//запрос действий игрока

				//действия игрока
				// у крупье открыта одна карта
				// игрок знает свои карты
				player1.setRank();
				while ((rankPlayer=player1.getRank()) < 21)
				{
					char key[] = { 'E','e','H','h' };
					while(!inputKey(key, sizeof(key), "Your step? Hit(H) or Enough(E)\n"))
						cout << "You choose is " << key[0] << endl;
					
					if ((key[0] == 'H') || (key[0] == 'h'))
					{
						player1.hitMe();//Игрок берет еще карту
						player1.takeCard(gameShoes.getCard());
						//предпоказ карт
						cout << player1.toString();
					}
					if ((key[0] == 'E') || (key[0] == 'e'))
					{
						player1.pass();//Игрок пасет, ему достаточно карт
						break;
					}
					player1.setRank();
				}
				
				// проверим не произошел ли перебор у игрока
				if (rankPlayer > 21)
				{
					cout << endl << "\nBrute force!!! You are LOSER!!! PlayerRank = " << rankPlayer << "\n" << endl;
					casinoWin++;
					
					Player::winner(dealer, player1);
					//player1.setMoney(false);
					//dealer.setMoney(true);

					continue;//переход к следующей игре
				}

				//проверка карт крупье
				dealer.setRank();//узнаем что у Крупье по очкам
				int rankDealer = dealer.getRank();
				cout << dealer.toString();//покажем все карты Крупье

				//если у Крупье 21, то проиграли все Игроки кроме тех у кого 21
				if (rankDealer == 21)
				{
					if (rankPlayer == rankDealer)
					{
						//в некоторых Казино, в этом случае выигрывает все равно Казино
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
					continue;//переход к следующей игре
				}

				//ответ крупье(добор карт)
				dealer.setRank();
				//крупье должен добирать карты пока не получи не менее 17 очков
				while ((rankDealer = dealer.getRank()) < 17)
				{
					dealer.takeCard(gameShoes.getCard());
					//предпоказ карт
					cout << dealer.toString();
					dealer.setRank();
				}

				//в случае перебора, выигрывают Игроки
				if (rankDealer > 21)
				{
					cout << "\nYou are WINNER!!! Casino LOSE!!! PlayerRank = " << rankPlayer << " CasinoRank = " << rankDealer << "\n";
					playerWin++;
					Player::winner(player1, dealer, 1.5);
					
					continue;//переход к следующей игре
				}

				if (rankPlayer == rankDealer)
				{
					//в некоторых Казино, в этом случае выигрывает все равно Казино
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

				//если закончились деньги, покинуть казино
				if (player1.getMoney() == 0.)
				{
					cout << endl << "\nИгра завершена. У Вас закончились деньги. Повезет в следующий раз!" << endl;
					break;
				}

				cout << endl << "\nИгра завершена. Желаете покинуть Казино?" << endl;
				//char c;
				//cin >> c;
				if (inputKey())break;
			}//while

		}

	
	};

	//класс 
	class Card_Game_Fooler
	{
		static void infoStartKON(PlayerFool& player, PlayerFool& computer, Deck& gameDeck)
		{
			//!!! только для отладки
//			computer.sortCard('A');
//			computer.sortCard('B');
//			cout << endl << computer.toString('A');
//			cout << endl << computer.toString('B');
			//!!! только для отладки

			//покажем козырь
			cout << endl << "Козырная масть: " << Suitmarks[gameDeck.getTrumpCard()];// card::toString(&TrumpCard);
			cout << "\nВ колоде еще: " << gameDeck.getCntCard();
			cout << "\nКарт отбито уже: " << computer.getCntLostCard() << endl;

			player.sortCard();//отсортируем карты по рангу
			cout << player.toString();//покажем наши карты

			computer.sortCard();//отсортируем карты по рангу

			//!!! только для отладки
//			cout << endl << computer.toString();//покажем карты компьютера
			//!!! только для отладки
		}

	public:

		//статический метод ИГРА
		static void Game()
		{
			//начало игры с инициализации действующих объектов

			//Игрок
			PlayerFool player1("Игрок 1");
			//Крупье - Казино
			PlayerFool computer("Компьютер");

			card TrumpCard;
			

			//будем вести подсчет выигрышных партий Игрока и Компьютера, ничья не учитываеться
			int playerWin = 0;
			int computerWin = 0;
			//количество проведенных игр
			int game_counter = 0;

			int countCard = 0;//количество заходов на оппонента(не более 6ти!!!)

				//бесконечный цикл СОБСТВЕННО ИГРА
			while (true)
			{
				//сбросим карты Игрока и Компьютера
				player1.resetCard();
				computer.resetCard();

				//Колода карт
				Deck gameDeck(EASY_DECK);
				//перетасуем колоду
				gameDeck.Shuffle();
				TrumpCard = card(gameDeck.getCard(0));//скопируем наш козырь
//				//покажем козырь
//				cout << endl << "Козырная масть: " << Suitmarks[gameDeck.getTrumpCard()];// card::toString(&TrumpCard);
//				
//				//Выведем информацию для играющих
//				cout << endl << "Кон № " << ++game_counter << endl;
//				cout << endl << "\t СЧЕТ (Игрок) " << playerWin << " : " << computerWin << " (Компьютер)" << endl << endl;
//				cout << endl << "И Г Р А   Н А Ч А Л А С Ь " << endl;


				//Ничьи в игре «Дурак» не бывает. Нет ни победителей, ни проигравших. 
				//Однако иногда в этой ситуации проигравшим считается игрок, бивший последней картой («последняя рука хуже дурака»)


				//раздаем карты
				//первая раздача по 6ть карт по кругу
				//так как сдает компьютер, он берет себе последним
				//манера раздачи может варьироваться
				for (int i = 0; i < 6; i++)
				{
					player1.takeCard(gameDeck.getCard());
					computer.takeCard(gameDeck.getCard());
				}


				//проверим раздачу, в случае если все 6ть карт одной масти, можно потребовать перездачу!!!
				if (computer.checkCards())
				{
					cout << endl << computer.getName() << ": All cards with the same suitmarks!!!";

					anyKey();
					continue;//начать следующую игру
				}
				if (player1.checkCards())
				{
					//карты с одинаковой масти
					char key[] = { 'Y','y','N','n' };
					while (!inputKey(key, sizeof(key), "Want new distribution of cards(Y) or play waiter(N)\n"))
						cout << "You choose is " << key[0] << endl;

					if ((key[0] == 'Y') || (key[0] == 'y'))
					{
						cout << endl << player1.getName() << ": All cards with the same suitmarks!!!";

						anyKey();
						continue;//начать следующую игру
					}
				}

				//infoStartKON(player1, computer, gameDeck);

				//добавим временный массив кард участвующих в отбое
				card* lost_card[12]{ nullptr };//в отбое не более 12 карт, 6 подкинутых и 6 чтоб отбиться
				int cntLost_card = 0;

				//определим очередность, наличие козыря меньшей масти
				switch (int priority = PlayerFool::checkPriority(gameDeck.getTrumpCard(), computer, player1))
				{
					// !!! СОБСТВЕННО ИГРА НАЧАЛАСЬ !!!
				START_KON:
				case 1:
					if (priority)
						cout << endl << "Computer have minimum Trump Card";
					priority = 0;

					countCard = 0;//количество заходов в КОНу
					
					coutColor("\nYour turn Computer.\n", wAttributeSpecial);

					infoStartKON(player1, computer, gameDeck);

					do
					{
						if (countCard++ == 6) break;//условие отбоя 6ть отбитых карт
						
						coutColor("\n\n *** Computer (ходит) *** \n", wAttributeSpecial);
						//разыгрываем заход от Компьютера на Игрока
						cout << endl;
						//Компьютер выбирает карту для захода на Игрока
						lost_card[cntLost_card++] = computer.choseCardSpecial(lost_card,&cntLost_card);
//						lost_card[cntLost_card++] = computer.choseCard();
						//если карт больше нет, то выход, передача хода дальше
						if ((lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							&&(cntLost_card>1))//хоть одну карту но пойти надо!!!
							break;
						
						//проверка на корректность карт:
						//карта допустима в ходе, ранг встречаеться!!!
						if (cntLost_card > 1)
							if (!card::checkEqualRank(lost_card,cntLost_card))//проверка на допустимость карты в ходе не прошла
							{
								cout << endl << "Computer: Wrong card. Choose another card." << endl;
								//карту вернуть отправителю!!!
								computer.takeCard(lost_card[--cntLost_card]);
								//карта не была разыграна, удаляем
								lost_card[cntLost_card] = nullptr;

								countCard--;//заход не прошел!!!
								continue;//повторить запрос карты
							};

						//Оппонент(Компьютер) учел карту, которой походил
						computer.takeLostCard(lost_card[cntLost_card - 1]);

						coutColor("\n\n *** Player1 (отбивается) *** \n", wAttributeSpecial);
						cout << endl;

						do
						{
							//Игрок выбирает карту, чтоб побить карту от Соперников
//							lost_card[cntLost_card++] = player1.choseCardSpecial(lost_card, &cntLost_card);
							lost_card[cntLost_card++] = player1.choseCard();
							
							//если карты нет, то нет отбоя и Игрок забирает все карты
							//в отбое не более 6 карт и 5ти от Отбивавшегося
							if (lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							{
								cntLost_card--;
								for (int i = 0; i < cntLost_card; i++)
								{
									coutColor("\n Игрок взял карты!!! \n", wAttributeSpecial);
									//Игрок принял все карты
									player1.takeCard(lost_card[i]);
									//Оппонент(Компьютер) запомнил какие карты пришли Игроку
									computer.takeEnemyCard(lost_card[i]);
									//карта была разыграна, удаляем
									lost_card[i] = nullptr;
									//убрали карты из отбойных, они сейчас у Игрока
									computer.getLostCard(computer.getCntLostCard() - 1);
								}

								//Игрок взял карты, повтор захода на игрока!!!
								cntLost_card = 0;//обнулим карты на столе

								countCard = 0;//обнулим карты КОНа

								//добор карт после хода
								//сначала ходивший
								while ((computer.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
									computer.takeCard(gameDeck.getCard());
								//если карт больше нет и нет добора, то определим ПОБЕДИТЕЛЯ(НЕ ДУРАКА)
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


							//отбой 
							//старшинство карт, карта бьет, если ранг выше и одной масти или козырь
							if (card::checkRankOK(lost_card, cntLost_card - 1, cntLost_card - 2, gameDeck.getTrumpCard()))
							{
								//Оппонент(Компьютер) учел карту, которой отбились
								computer.takeLostCard(lost_card[cntLost_card - 1]);

								//если карт больше нет и нет добора, то определим ПОБЕДИТЕЛЯ(НЕ ДУРАКА)
								if (
									(gameDeck.getCntCard() == 0)
									&& (player1.getCntCard() == 0)
									&& (computer.getCntCard() != 0)
									)
								{
									playerWin++;
									goto EXIT;
								}														

								break; //отбой прошел успешно
							}

							//карту вернуть отправителю!!!
							player1.takeCard(lost_card[--cntLost_card]);
							//карта не была разыграна, удаляем
							lost_card[cntLost_card] = nullptr;

							cout << endl << "Player1: Wrong card. Choose another card." << endl;

						} while (true);


					} while (true);
					
					coutColor("\n\n *** ОТБОЙ *** \n", wAttributeSpecial);
					coutColor("Добор карт!!!\n", wAttributeSpecial);

					cntLost_card = 0;//обнулим карты на столе

					//добор карт после хода
					//сначала ходивший
					while ((computer.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						computer.takeCard(gameDeck.getCard());

					//потом все по часовой стрелки

					//в конце добирает карты отбивавшийся
					while ((player1.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						player1.takeCard(gameDeck.getCard());

					//если карт больше нет и нет добора, то определим ПОБЕДИТЕЛЯ(НЕ ДУРАКА)
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

					countCard = 0;//количество заходов в КОНу

					coutColor("\nYour turn Player1.\n", wAttributeSpecial);

					infoStartKON(player1, computer, gameDeck);

					do
					{
						if (countCard++ == 6) break;//условие отбоя 6ть отбитых карт

						coutColor("\n\n *** Player1 (ходит)*** \n", wAttributeSpecial);
						//разыгрываем заход от Игрока на Компьютер
						cout << endl;
						//Игрок выбирает карту, чтоб походить на Компьютер
//						lost_card[cntLost_card++] = player1.choseCardSpecial(lost_card, &cntLost_card);
						lost_card[cntLost_card++] = player1.choseCard();

						//если карт больше нет, то выход, передача хода дальше
						if ((lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							&& (cntLost_card > 1))//хоть одну карту но пойти надо!!!
							break;

						//проверка на корректность карт:
						//карта допустима в ходе, ранг встречаеться!!!
						if (cntLost_card > 1)
							if (!card::checkEqualRank(lost_card, cntLost_card))//проверка на допустимость карты в ходе не прошла
							{
								cout << endl << "Player1: Wrong card. Choose another card." << endl;
								//карту вернуть отправителю!!!
								player1.takeCard(lost_card[--cntLost_card]);
								//карта не была разыграна, удаляем
								lost_card[cntLost_card] = nullptr;

								countCard--;//заход не прошел!!!
								continue;//повторить запрос карты
							};

						//Оппонент(Компьютер) учел карту, c которой на него походили
						computer.takeLostCard(lost_card[cntLost_card - 1]);

						coutColor("\n\n *** Computer (отбивается) *** \n", wAttributeSpecial);
						cout << endl;

						do
						{
							//Компьютер выбирает карту чтоб отбиться
							lost_card[cntLost_card++] = computer.choseCardSpecial((card**)lost_card, &cntLost_card);
//							lost_card[cntLost_card++] = computer.choseCard();

							//если карты нет, то нет отбоя и компьютер забирает все карты
							//в отбое не более 6 карт и 5ти от Отбивавшегося
							if (lost_card[cntLost_card - 1]->card_suit == suitmarks(0))
							{
								cntLost_card--;
								for (int i = 0; i < cntLost_card; i++)
								{
									coutColor("\n Компьютер взял карты!!! \n", wAttributeSpecial);
									//Компьютер принял все карты
									computer.takeCard(lost_card[i]);
									//карта была разыграна, удаляем
									lost_card[i] = nullptr;
									//убрали карты из отбойных, они сейчас у Компьютера
									computer.getLostCard(computer.getCntLostCard() - 1);
								}
								
								//добор карт после хода
								cntLost_card = 0;//обнулим карты на столе
								
								countCard = 0;//обнулим карты КОНа

								//добор карт после хода
								//сначала ходивший
								while ((player1.getCntCard() < 6) && (gameDeck.getCntCard()>0))
									player1.takeCard(gameDeck.getCard());

								//если карт больше нет и нет добора, то определим ПОБЕДИТЕЛЯ(НЕ ДУРАКА)
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

							//отбой 
							//старшинство карт, карта бьет, если ранг выше и одной масти или козырь
							if (card::checkRankOK(lost_card, cntLost_card - 1, cntLost_card - 2, gameDeck.getTrumpCard()))
							{
								//Оппонент(Компьютер) учел карту, которой отбились
								computer.takeLostCard(lost_card[cntLost_card - 1]);

								//если карт больше нет и нет добора, то определим ПОБЕДИТЕЛЯ(НЕ ДУРАКА)
								if (
									(gameDeck.getCntCard() == 0)
									&& (player1.getCntCard() != 0)
									&& (computer.getCntCard() == 0)
									)
								{
									computerWin++;
									goto EXIT;
								}

								break; //отбой прошел успешно
							}

							//карту вернуть отправителю!!!
							computer.takeCard(lost_card[--cntLost_card]);
							//карта не была разыграна, удаляем
							lost_card[cntLost_card] = nullptr;
							
							cout << endl << "Computer: Wrong card. Choose another card." << endl;

						} while (true);
											
					} while (true);

					coutColor("\n\n *** ОТБОЙ *** \n", wAttributeSpecial);
					coutColor("Добор карт!!!\n", wAttributeSpecial);

					cntLost_card = 0;//обнулим карты на столе
				   					 				  				  
					//добор карт после хода
					//сначала ходивший
					while ((player1.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						player1.takeCard(gameDeck.getCard());
	
					//потом все по часовой стрелки

					//в конце добирает карты отбивавшийся
					while ((computer.getCntCard() < 6) && (gameDeck.getCntCard() > 0))
						computer.takeCard(gameDeck.getCard());

					//если карт больше нет и нет добора, то определим ПОБЕДИТЕЛЯ(НЕ ДУРАКА)
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
				//Выведем информацию для играющих
				cout << endl << "Кон № " << game_counter << " ЗАВЕРШЕН" << endl;
				cout << endl << "\t СЧЕТ (Игрок) " << playerWin << " : " << computerWin << " (Компьютер)" << endl << endl;

				cout << endl << "\nИгра завершена. Желаете выйти из-за стола?" << endl;
				if (inputKey())break;
			}//while

		}


	};//CARD_GAME_FOOLER

	void TestClassCards();
	void TestClassShoes();
	void TestClassBlackjack();

}// classApp


#endif //BLACKJACK_H

