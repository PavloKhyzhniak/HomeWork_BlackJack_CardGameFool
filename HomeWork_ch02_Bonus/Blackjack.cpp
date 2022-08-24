#pragma once

#include "Blackjack.h"


#include "pch.h"
#include "Utils.h"
#include "UtilsConsole.h"
#include "Func.h"

extern wchar_t title[150];

namespace classApp {

#pragma region card

	//получаем масть карты через объект
		const char* card::getCardSuit(const card* const object)
		{
			//запросим масть карты из массива мастей
			return Suitmarks[(*object).card_suit];
//			switch ((*object).card_suit)
//			{
//			case none:
//				return "none";
//			case clubs:
//				return "Clubs";
//			case pikes:
//				return "Pikes";
//			case hearts:
//				return "Hearts";
//			case diamonds:
//				return "Diamonds";
//			default:
//				throw exception("card:Wrong suit!");
//			}

		}

		//запроси цвет карты
		const char* card::getCardColor(const card* const object)
		{
			//по цвету карты вернем символьное назнание цвета
			switch ((*object).card_color)
			{
			case 0:
				return "none";
			case black:
				return "Black";
			case red:
				return "Red";
			default:
				throw exception("card:Wrong color!");
			}
		}

		//запрос номинала карты
		const char* card::getCardRank(const card* const object)
		{
			//запросим обозначение номинала карты
			switch ((*object).card_rank)
			{
			case 0:
				return "none";
			case Two:
				return "-  2 -";
			case Three:
				return "-  3 -";
			case Four:
				return "-  4 -";
			case Five:
				return "-  5 -";
			case Six:
				return "-  6 -";
			case Seven:
				return "-  7 -";
			case Eight:
				return "-  8 -";
			case Nine:
				return "-  9 -";
			case Ten:
				return "- 10 -";
			case Jack:
				return "-  J -";
			case Queen:
				return "-  Q -";
			case King:
				return "-  K -";
			case Ace:
				return "-  A -";
			case 1:
			default:
				throw exception("card:Wrong rank!");
			}

		}

		//строковое представление карты: номер колоды, цвет, масть, номинал карты
		char* card::toString(const card* const object)
		{
			char* buf = new char[40];
			int j = 0;
			j += sprintf(buf + j, "%2d %10s %8s %10s \n", (*object).deck_number, card::getCardColor(object), Suitmarks[(*object).card_suit]/*; card::getCardSuit(object)*/, card::getCardRank(object));

			char* tmp = new char[strlen(buf) + 1];
			strcpy(tmp, buf);
			delete[] buf;

			return tmp;
		} // toString

		//проверка карт на эквивалентный ранг, карты должны быть минимум парами!!!
		bool card::checkEqualRank(card* tmp[],int cnt)
		{
			if (cnt <= 1)
				return true;
			int count = 0;
			int i = cnt-1;
				for (int j = 0; j < cnt-1; j++)
					if ((tmp[i]->card_rank) == (tmp[j]->card_rank))
						count++;
				if (count < 1)
					return false;
		}

		//проверка карта(index1) бьет нижнюю карту(index2)
		bool card::checkRankOK(card* tmp[], int index1, int index2,suitmarks trump_suit)
		{
			if (
				((tmp[index1]->card_rank > tmp[index2]->card_rank)//карта выше рангом
					&& (tmp[index1]->card_suit == tmp[index2]->card_suit))//карты одной масти, тоже для козырных
				||
				((tmp[index1]->card_suit == trump_suit)//карта козырная
					&& (tmp[index2]->card_suit != trump_suit))//бьет карту обычную
				)
				return true;
			
			return false;
		}
		
#pragma endregion

#pragma region Cards
	//STATIC data
#pragma region STATIC_data

	//инициализируем статическую переменную-счетчик созданных объектов
	int Deck::count_ = 0;

#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor
	Deck::Deck(deck_count max_card)
		:max_card_{max_card}
		, next_card_{ max_card_ }
	{
		//инициализация стандартной колоды карт по умолчанию
		for (int i = 0; i < max_card_; i++)
		{
			deck_[i].deck_number = 0;
			if (i < (max_card_/4))//13 карт каждой масти
				deck_[i].card_suit = clubs;
			else if (i < (max_card_/2))
				deck_[i].card_suit = pikes;
			else if (i < ((max_card_/4)*3))
				deck_[i].card_suit = hearts;
			else
				deck_[i].card_suit = diamonds;

			if (i < max_card_/2)//только два цвета, сначала черный, потом красные масти инициализируем
				deck_[i].card_color = black;
			else
				deck_[i].card_color = red;

		if (max_card_==EASY_DECK)
			//присваиваем номиналы картам от 6 до 14(туз)
			deck_[i].card_rank = rank(6 + i % (max_card_/4));
		else
			//присваиваем номиналы картам от 2 до 14(туз)
			deck_[i].card_rank = rank(2 + i % (max_card_ / 4));
		}
			   		 	  
#ifdef _DEBUG
//		cout << endl << "Конструктор по умолчанию(без параметров). Класс Cards.\n";
//		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	Deck::Deck(const Deck& object)
		:max_card_{ object.max_card_ }
		, next_card_{ object.max_card_ }
	{
		//колоды у нас одинаковые, просто копируем карты из одной в другую
		for (int i = 0; i < max_card_; i++)
			this->deck_[i] = object.deck_[i];
			   
#ifdef _DEBUG
	//	cout << endl << "Конструктор копирования. Класс Cards.\n";
	//	cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//destructor
	Deck::~Deck() {
		//динамические элементы у нас отсутствуют

#ifdef _DEBUG
	//	cout << endl << "Деструктор. Класс Cards.\n";
	//	cout << "Всего существует " << --count_ << " объектов\n";
	//
	//	if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS
		
#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	//запрос масти карты по индексу в колоде
	const char* Deck::getCardSuit(int index) const
	{
return Suitmarks[deck_[index].card_suit];
//		return card::getCardSuit(&deck_[index]);

	//	switch (deck_[index].card_suit)
	//	{
	//	case none:
	//		return "none";
	//	case clubs:
	//		return "Clubs";
	//	case pikes:
	//		return "Pikes";
	//	case hearts:
	//		return "Hearts";
	//	case diamonds:
	//		return "Diamonds";
	//	default:
	//		throw exception("Cards:Wrong suit!");
	//	}
		
	}

	//запрос цвета карты по индексу в колоде
	const char* Deck::getCardColor(int index)const
	{
		return card::getCardColor(&deck_[index]);
//
//		switch (deck_[index].card_color)
//		{
//		case 0:
//			return "none";
//		case black:
//			return "Black";
//		case red:
//			return "Red";
//		default:
//			throw exception("Cards:Wrong color!");
//		}		
	}

	//запрос номинала карты по индексу в колоде
	const char* Deck::getCardRank(int index)const
	{
		if ((max_card_ == EASY_DECK) && (deck_[index].card_rank < Six)) throw exception("Deck: Wrong card rank.");;
		return card::getCardRank(&deck_[index]);
//		switch (deck_[index].card_rank)
//		{
//		case 0:
//			return "none";
//		case Two:
//			return "-2-";
//		case Three:
//			return "-3-";
//		case Four:
//			return "-4-";
//		case Five:
//			return "-5-";
//		case Six:
//			return "-6-";
//		case Seven:
//			return "-7-";
//		case Eight:
//			return "-8-";
//		case Nine:
//			return "-9-";
//		case Ten:
//			return "-10-";
//		case Jack:
//			return "-J-";
//		case Queen:
//			return "-Q-";
//		case King:
//			return "-K-";
//		case Ace:
//			return "-A-";
//		default:
//			throw exception("Cards:Wrong rank!");
//		}
//
	}

	//запросить карту
	card& Deck::getCard(int index)
	{
		return deck_[index];
	}

	//затребовать карту из Колоды с последующим удалением
	card* Deck::getCard()
	{
		if (next_card_>=0)
			next_card_--;//смотрим на следующую карту

		//создаем указатель на карту для возврата
		card* tmp = new card{ suitmarks(0), color(0), rank(0), 0 };

		if (next_card_ < 0)//если карт больше нет
		{
			next_card_ = 0;//карт нет
			cout << endl << "No cards yet!!!" << endl;
			return tmp;//вернем указатель на забранную карту
		}
				
		*tmp = deck_[next_card_];//возьмем карту из Колоды
		EmptyCard(next_card_);//удалим эту карту

		return tmp;//вернем указатель на забранную карту
	}
	
	//заменить карту в колоде под индексом, переданной картой
	void Deck::setCard(card& object, int index_card)
	{
		deck_[index_card] = object;
	}

	//узнать количество карт в руке Колоде
	int Deck::getCntCard()
	{
		return next_card_;
	}
	
	//узнать номер колоды карты
	int Deck::getDeckNumber(int index)
	{
		return deck_[index].deck_number;
	}

	//установить номер колоды при инициализации в порядке создания
	void Deck::setDeckNumber(int number)
	{
		for(int i=0;i< max_card_;i++)
			deck_[i].deck_number = number;
	}

	//установить козырную масть
	void Deck::setTrumpCard()
	{
		trump_card_ = deck_[0].card_suit;
	}

	//узнать козырную масть
	suitmarks Deck::getTrumpCard()
	{
		return trump_card_;
	}

#pragma endregion

	//METHODS
#pragma region METHODS

	//вывод карт колоды: номер карты, номер колоды, цвет, масть, номинал карты
	char* Deck::toString() const
	{
		char* buf = new char[40* max_card_];
		int j = 0;
		for (int i = 0; i < 52; i++)
			//			cout << setw(2) << i << setw(10) << getCardColor(i) << setw(8) << getCardSuit(i) << setw(10) << getCardRank(i) << endl;
			j+=sprintf(buf+j, "%2d %2d %10s %8s %10s \n", (i+1), deck_[i].deck_number, getCardColor(i), Suitmarks[deck_[i].card_suit]/*getCardSuit(i)*/, getCardRank(i));

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

	//вывод карты из колоды под индексом : номер карты, номер колоды, цвет, масть, номинал карты
	char* Deck::toString(int i) const
	{
		char* buf = new char[100];

		sprintf(buf, "%2d %2d %10s %8s %10s \n", (i+1), deck_[i].deck_number, getCardColor(i), Suitmarks[deck_[i].card_suit]/*getCardSuit(i)*/, getCardRank(i));

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

	//проверим на наличие карты под индексом
	bool Deck::IsEmpty(int index)
	{
		if (
			Suitmarks[deck_[index].card_suit] == "none"//достаточно проверять один из правильных параметров(полей) карты(масть, цвет, номинал)
			//getCardSuit(index) == "none"

			//	|| getCardColor(index) == "none" 
			//	|| getCardRank(index) == "none"
			) return true;
		
		return false;
	}

	//удаление карты из колоды
	void Deck::EmptyCard(int index)
	{
		if (index >= 0 && index < max_card_)
		{
			deck_[index] = { suitmarks(0),color(0),rank(0),0 };//затрем(обнулим) все поля карты
		//	deck_[index].card_suit = suitmarks(0);
		//	deck_[index].card_color = color(0);
		//	deck_[index].card_rank = rank(0);
			return;
		}
		throw exception("Cards:Wrong index.");
	}

	//перетасуем карты
	void Deck::Shuffle()
	{
		//создадим новую колоду карт
		card new_deck[52];//можно использовать и новый объект Deck new_deck; new_deck.deck_[i];
		//только для отладки, карты до перетасовки
//		cout << toString();

		//будем заполнять с конца
		int cnt = max_card_;
		int tmp;//случайный индекс в колоде
		while (cnt > 0)//пока не заполнили всю новую колоду, реальными картами выбранными в случайном порядке
		{
			tmp = genRand(0, max_card_-1);//сгенерируем новый случайный индекс
			if (IsEmpty(tmp)) continue;//если по этому индексу уже забрали карту, повторить итерацию
			
			//индекс уникальный, копируем карту в нашу новую колоду
			new_deck[--cnt] = deck_[tmp];
//			deck_[tmp] = { suitmarks(0),color(0),rank(0) };
//			deck_[tmp].card_suit = suitmarks(0);
			EmptyCard(tmp);//в старой колоде карту убираем
		}

		//перезапишем нашу исходную колоду, новой сформированной колодой!!!
		for (int i = 0; i < max_card_; i++)
			deck_[i] = new_deck[i];
	
		//определим нижнюю карту в качестве козырной масти
		setTrumpCard();
		//только для отладки, карты после перетасовки
//		cout << toString();

	}


#pragma endregion

#pragma region OPERATORS
	Deck& Deck::operator=(const Deck& object)
	{
		if (&object == this) return *this;

		for (int i = 0; i < max_card_; i++)
			deck_[i] = object.deck_[i];

#ifdef _DEBUG
		cout << endl << "Оператор присваивания. Класс Cards.\n";
		cout << "Всего существует " << count_ << " объектов\n";
#endif
		return *this;
	} // operator=

	
#pragma endregion

#pragma endregion

	void TestClassCards() {
	
		cls();

		// Установим актуальный заголовок окна
		SetConsoleTitle(title);
		// Установим актуальный заголовок окна
		myAddConsoleTitle(L" Тестирование Класса Cards ");

		coutColor("\nСоздадим три отдельных объекта\n", wAttributeSpecial);

		Deck c1(EASY_DECK);
		Deck c2=c1;

		coutColor("\nПокажем наши объекты.\n", wAttributeSpecial);
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;

		//************************
		coutColor("\nПоработаем с объектом №1 и индексом 4\n", wAttributeSpecial);

		cout << c1.toString(4) << endl;
		cout << endl << c1.getCardSuit(4);
		cout << endl << c1.getCardColor(4);
		cout << endl << c1.getCardRank(4);
		if(c1.IsEmpty(4)) 
			cout << "\nCard in position 4 is empty.\n";
		else
			cout << "\nCard in position 4 not empty.\n";

		c1.EmptyCard(4);
		cout << c1.toString(4) << endl;

		if (c1.IsEmpty(4))
			cout << "\nCard in position 4 is empty.\n";
		else
			cout << "\nCard in position 4 not empty.\n";

		anyKey();

		//*************************
				
		coutColor("\nПротестируем перегрузку операторов []\n", wAttributeSpecial);
		
		for (int i = 0; i < 52; i++)
			cout << endl << c1[i].card_rank;

		coutColor("\nПроверим содержимое наших объектов\n", wAttributeSpecial);
		//выведем информацию о существующих объектов в массиве
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;
		c2.Shuffle();
		cout << c2.toString() << endl;


		anyKey();

		cls();
	}
	
	
#pragma endregion


#pragma region Shoes
	//STATIC data
#pragma region STATIC_data

	//инициализируем статическую переменную-счетчик созданных объектов
	int Shoes::count_ = 0;

	//при запуске программы, проинициализируем количество задействованных колод
	//обычно от 6 до 8, но есть игры и с одной колодой
	int Shoes::decks_ = genRand(1,10);
	
#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor
	Shoes::Shoes()
		:shoes_{ nullptr }
	{
		//инициализация счетчика карт в Шузе
		next_card_ = 52 * decks_;

		shoes_ = new Deck[decks_];
		//только для отладки, до перетасовки колод в Шузе
//		cout << toString();

		for (int i = 0; i < decks_; i++)
		{
			shoes_[i].setDeckNumber(i);
			shoes_[i].Shuffle();
		}
		//только для отладки, после перетасовки всех колод по отдельности
//		cout << toString();

		//перетасовка уже всего Шуза(колод с картами)
		Shuffle();
		setSpecialCard();//уберем из Шуза часть карт после перетасовки
		
		//только для отладки, после перетасовки всего Шуза
//		cout << toString();

#ifdef _DEBUG
		cout << endl << "Конструктор по умолчанию(без параметров). Класс Shoes.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	Shoes::Shoes(const Shoes& object)
		:shoes_{ nullptr }
	{
		next_card_ = 52 * decks_;
		setSpecialCard();//уберем из Шуза часть карт

		shoes_ = new Deck[decks_];

		for (int i = 0; i < decks_; i++)
			shoes_[i] = object.shoes_[i];

#ifdef _DEBUG
		cout << endl << "Конструктор копирования. Класс Shoes.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//destructor
	Shoes::~Shoes() {

		if (shoes_ != nullptr)
			delete[] shoes_;
		shoes_ = nullptr;

#ifdef _DEBUG
		cout << endl << "Деструктор. Класс Shoes.\n";
		cout << "Всего существует " << --count_ << " объектов\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	//запрос карты из Шуза
	card* Shoes::getCard() 
	{
		next_card_--;//смотрим на следующую карту

		if (next_card_ < 0)//если карт больше нет, создаем новый Шуз
		{
			//в игру вводится новый шуз
			cout << endl << "New Shoes create!!!" << endl;
			Shoes new_shoe;
			*this = new_shoe;
		}

		//находим индексы колоды и карты в Шузе
		int tmp_deck_index = next_card_ / 52;
		int tmp_card_index = next_card_ % 52;
		//создаем указатель на карту для возврата
		card* tmp = new card;
		*tmp= shoes_[tmp_deck_index].getCard(tmp_card_index);//возьмем карту из Шуза
		shoes_[tmp_deck_index].EmptyCard(tmp_card_index);//удалим эту карту

		return tmp;//вернем указатель на забранную карту
	}

	//установить переданную карту в нужную колоду и индекс карты
	void Shoes::setCard(card& object, int index_deck, int index_card) 
	{
		shoes_[index_deck].setCard(object,index_card);
	}

	//установим спец карту(удалим часть карт из игры)
	void Shoes::setSpecialCard()
	{
		//в нашем случае от половины и до конца
		int special_index = genRand(next_card_/2,next_card_);
		next_card_ = special_index;
	}

	//проверка на спец карту (не используеться)
	void Shoes::IsSpecialCard()
	{

	}

	//перетасовка Щуза!!!!
	void Shoes::Shuffle()
	{
		//делаем аналогично перетасовки колоды

		//создаем массив всех карт в Шузе!!!!
		card* new_deck = new card[next_card_];
		
		int cnt = next_card_;//будем заполнять массив с конца
		int tmp;

		//создадим переменные под индекс колоды и карты в колоде
		int tmp_deck_index;
		int tmp_card_index;
				
		while (cnt > 0)//пока не все карты обработали
		{
			tmp = genRand(0, next_card_ - 1);//генерируем случайный индекс
			
			//переводим полученный индекс в номер колоды и карты в колоде
			tmp_deck_index = tmp / 52;
			tmp_card_index = tmp % 52;

			if (shoes_[tmp_deck_index].IsEmpty(tmp_card_index)) continue;//если карта пуста, ищем следующий индекс

			new_deck[--cnt] = shoes_[tmp_deck_index].getCard(tmp_card_index);//копируем карту

			shoes_[tmp_deck_index].EmptyCard(tmp_card_index);//удаляем карту в Шузе
		}	

		//копируем наш массив в исходный Шуз
		for (int i = 0; i < next_card_; i++)
		{
			tmp_deck_index = i / 52;
			tmp_card_index = i % 52;
			setCard(new_deck[i], tmp_deck_index, tmp_card_index);
		}

		//удаляем динамический массив с картами
		delete[] new_deck;
	}

	//вывод карт в Шузе
	char* Shoes::toString() const
	{
		char* buf = new char[40 * 52 * decks_];
		int j = 0;

		for (int i = 0; i < decks_; i++)
			j += sprintf(buf + j, "%s\n", shoes_[i].toString());

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString
#pragma endregion

	//METHODS
#pragma region METHODS

	

#pragma endregion

#pragma region OPERATORS
	Shoes& Shoes::operator=(const Shoes& object)
	{
		if (&object == this) return *this;

		next_card_ = object.next_card_;

		if (shoes_ != nullptr)
			delete[] shoes_;
		shoes_ = nullptr;
		shoes_ = new Deck[decks_];

		for (int i = 0; i < decks_; i++)
			shoes_[i] = object.shoes_[i];

#ifdef _DEBUG
		cout << endl << "Оператор присваивания. Класс Shoes.\n";
		cout << "Всего существует " << count_ << " объектов\n";
#endif
		return *this;
	} // operator=


#pragma endregion

#pragma endregion

	void TestClassShoes(){

		cls();

		// Установим актуальный заголовок окна
		SetConsoleTitle(title);
		// Установим актуальный заголовок окна
		myAddConsoleTitle(L" Тестирование Класса Shoes ");

		coutColor("\nСоздадим три отдельных объекта\n", wAttributeSpecial);

		Shoes c1;
		Shoes c2 = c1;

		coutColor("\nПокажем наши объекты.\n", wAttributeSpecial);
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;

		anyKey();

		//************************
		coutColor("\nПоработаем с объектом №1 \n", wAttributeSpecial);

		card* tmp;
		for (int i = 0; i < 10; i++)
		{
			tmp = c1.getCard();
			cout << card::toString(tmp)
				<< endl;
			delete tmp;
		}

		anyKey();

		//*************************
		
		coutColor("\nПроверим содержимое наших объектов\n", wAttributeSpecial);
		//выведем информацию о существующих объектов в массиве
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;
		c2.Shuffle();
		cout << c2.toString() << endl;


		anyKey();

		cls();
	}
	

#pragma endregion;



#pragma region Player
	//STATIC data
#pragma region STATIC_data

	//инициализируем статическую переменную-счетчик созданных объектов
	int Player::count_ = 0;

#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor
	Player::Player(const char* name)
	{
		//у Игрока изначально 1000 у.е.
		money = 1000.;
		rank_ = 0;
		rate = 0;
		cntCard_ = 0;

		strcpy(name_, name);//присваиваем переданное имя
		//инициализируем(обнуляем) массив карт
		for (int i = 0; i < 10; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };
		
#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами. Класс Player.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//constructor
	Player::Player(const char* name,double money)
	{
		//назначаем деньги Игроку(чаще Крупье)
		this->money = money;
		rank_ = 0;
		rate = 0;
		cntCard_ = 0;

		//копируем имя Игрока
		strcpy(name_,name);
		//инициализируем(обнуляем) массив карт
		for (int i = 0; i < 10; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };

#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами. Класс Player.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}
		
	//destructor
	Player::~Player() {
		
#ifdef _DEBUG
		cout << endl << "Деструктор. Класс Player.\n";
		cout << "Всего существует " << --count_ << " объектов\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	//сброс карт Игрока
	void Player::resetCard()
	{
		//сброс карт Игрока
		cntCard_ = 0;
		for (int i = 0; i < 10; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };
	}

	//распределение средств между Игроками
	void Player::winner(Player& winner, Player& loser, double koefficient)
	{
		if (koefficient == 1.) 
		{
			//казино выигрывает
			winner.setRate(loser.setMoney(false));
			winner.setMoney(true);
		}
		else
		{
			//казино проигрывает
			loser.setRate(winner.setMoney(true, koefficient));
			loser.setMoney(false);
		}
	}

	//получить карту в "руку" Игрока
	void Player::takeCard(card* card)
	{
		my_card_[cntCard_++] = *card;
	}

	//проверка на наличие Туза в первой карте в "руке"
	bool Player::checkIfAceIsFirstCard()
	{
		if (card::getCardRank(&my_card_[0])=="-  A -")
			return true;

		return false;
	}

	//расчет денег, с возвратом начисленных денег
	double Player::setMoney(bool winner, double koefficient)
	{
		double result;
		if (winner)
			money += result =(rate * koefficient);
		else
			money -= result = rate;

		return result;
	}

	//запрос на количество денег у Игрока
	double Player::getMoney() const
	{
		return money;
	}

	//установка ставки
	void Player::setRate(double rate)
	{
		if (rate >= 0.)
			this->rate = rate;
	}

	//ввод ставки Игроком
	void Player::setRate()
	{
		double tmp_rate =0.;

		while (tmp_rate <= 0) {
			cout << endl << "Введите ставку: " << endl;
			cin >> tmp_rate;
			if (tmp_rate > money)
			{
				tmp_rate = -1;//ставка не возможка
				cout << endl << "Ставка невозможна. Ваши деньги: " << money << endl;
			}
		}

		rate = tmp_rate;
	}

	//узнать свою ставку
	double Player::getRate() const
	{
		return rate;
	}

	//рассчитать свои очки с карт
	void Player::setRank()
	{
		int tmp_rank = 0.;
		int ace = 0;

		for(int i=0;i<10;i++)
			switch (my_card_[i].card_rank)
			{
			case 0:
				tmp_rank += 0;
				break;
			case Two:
				tmp_rank += 2;
				break;
			case Three:
				tmp_rank += 3;
				break;
			case Four:
				tmp_rank += 4;
				break;
			case Five:
				tmp_rank += 5;
				break;
			case Six:
				tmp_rank += 6;
				break;
			case Seven:
				tmp_rank += 7;
				break;
			case Eight:
				tmp_rank += 8;
				break;
			case Nine:
				tmp_rank += 9;
				break;
			case Ten:
			case Jack:
			case Queen:
			case King:
				tmp_rank += 10;
				break;
			case Ace:
				tmp_rank += 11;
				ace++;
//				if (tmp_rank > 21)
//					tmp_rank -= 10;
				break;
			default:
				throw exception("Cards:Wrong rank!");
			}

		//если есть туз то при переборе считаеться за 1, а не за 11
		while ((ace-- > 0)&&(tmp_rank>21))
			tmp_rank -= 10;

		rank_ = tmp_rank;
	}

	//запросить очки
	int Player::getRank()const
	{
		return rank_;
	}


	void Player::hitMe()
	{
		cout << "\nЕще карту!!!\n";
	}

	void Player::pass()
	{
		cout << "\nПасс...\n";
	}

	//краткие сведения об Игроке: имя, карты, деньги и ставка
	char* Player::toString(int count) const
	{
		char* buf = new char[40 * 10 + 200];
		int j = 0;

		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_,"Карты:");
		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");

		for (int i = 0; i < count; i++)
			if (
				Suitmarks[my_card_[i].card_suit] != "none"
				//				card::getCardSuit(&my_card_[i])!="none"
				)
				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&my_card_[i]), Suitmarks[(*&my_card_[i]).card_suit], card::getCardRank(&my_card_[i]));
				//j += sprintf(buf + j, "%s\n", card::toString(&my_card_[i]));


		j += sprintf(buf + j, "%s %.2lf\n", "Деньги:", getMoney());
		j += sprintf(buf + j, "%s %.2lf\n", "Ставка:", getRate());

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString
#pragma endregion

	//METHODS
#pragma region METHODS



#pragma endregion

#pragma region OPERATORS
	

#pragma endregion

#pragma endregion

	


#pragma endregion;


#pragma region PlayerFool
	//STATIC data
#pragma region STATIC_data

	//инициализируем статическую переменную-счетчик созданных объектов
	int PlayerFool::count_ = 0;

#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor
	PlayerFool::PlayerFool(const char* name, double geld)
	{
		//у Игрока изначально 1000 у.е.
		money = geld;
		rank_ = 0;
		rate = 0.;

		cntCard_ = 0;
		cntLost_card_ = 0;
		cntEnemy_card_ = 0;

		strcpy(name_, name);//присваиваем переданное имя
		//инициализируем(обнуляем) массив карт
		for (int i = 0; i < 36; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };

		//инициализируем(обнуляем) массив карт
		for (int i = 0; i < 36; i++)
			lost_card_[i] = { suitmarks(0),color(0),rank(0),0 };

		//инициализируем(обнуляем) массив карт
		for (int i = 0; i < 36; i++)
			enemy_card_[i] = { suitmarks(0),color(0),rank(0),0 };

#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами. Класс PlayerFool.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//destructor
	PlayerFool::~PlayerFool() {

#ifdef _DEBUG
		cout << endl << "Деструктор. Класс PlayerFool.\n";
		cout << "Всего существует " << --count_ << " объектов\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

			//метод сортировки карт (Бубна Трефы Черви Пики)
	void PlayerFool::sortCard(char ch)
	{

		card* ptr = nullptr;
		int cnt = 0;
		switch (ch)
		{
		case 'A':
			ptr = lost_card_;
			cnt = cntLost_card_;
			break;
		case 'B':
			ptr = enemy_card_;
			cnt = cntEnemy_card_;
			break;
		case 'C':
			ptr = my_card_;
			cnt = cntCard_;
			break;
		}

//		char* buf = new char[40 * 10 + 40 * 36];
//		int j = 0;
//
//		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_, "Карты:");
//		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");
//
//		for (int i = 0; i < cnt; i++)
//			if (
//				Suitmarks[ptr[i].card_suit] != "none"
//				//				card::getCardSuit(&ptr[i])!="none"
//				)
//				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&ptr[i]), Suitmarks[(*&ptr[i]).card_suit], card::getCardRank(&ptr[i]));
//
//		delete[] buf;

		//линейный поиск и сортировка обменом
		//сначала организуем поиск 6ок Бубн, потом Треф и т.д.

//		for (int i = 0; i < cnt; i++)//цикл по всем картам(мы должны отсортировать все карты)
		int r = 2;
		int i = 0;
		for (rank k = Two; k <= Ace; r++, k = rank(r))//сортируем по рангу от 2 до Туза и в порядке масти!!!
		{
			//suitmarks cnt = trump_card_;
			int four_suit = 0;
			switch (trump_card_)//начнем сразу после козыря!!! КОЗЫРЬ В КОНЦЕ
			{
			START_SWITCH_SORT_CARD:
				four_suit++;
				for (int j = 0; j < cnt; j++)//организуем поиск всех мастей по рангу и в порядке масти!!!
					if ((ptr[j].card_suit == suitmarks(diamonds)) && (ptr[j].card_rank == k))
					{
						//организуем обмен, в качестве временной переменной возьмем последнюю ячейку(уни у кого не может быть на руках 36 карт!!!)
						ptr[35] = ptr[i];//сохраним карту(сдвинем - копированием) карту

						//не забудем теперь смотреть на следующую ячейку для сортировки!!!
						ptr[i++] = ptr[j];//переместим(сдвинем - копированием) карту подходящую условиям сортировки

						ptr[j] = ptr[35];//переместим(сдвинем - копированием) карту не подходящую условиям сортировки
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//удалим временную карту
					}
				if (four_suit == 4)break;
			case diamonds:
				four_suit++;
				for (int j = 0; j < cnt; j++)//организуем поиск всех мастей по рангу и в порядке масти!!!
					if ((ptr[j].card_suit == suitmarks(clubs)) && (ptr[j].card_rank == k))
					{
						//организуем обмен, в качестве временной переменной возьмем последнюю ячейку(уни у кого не может быть на руках 36 карт!!!)
						ptr[35] = ptr[i];//сохраним карту(сдвинем - копированием) карту

						//не забудем теперь смотреть на следующую ячейку для сортировки!!!
						ptr[i++] = ptr[j];//переместим(сдвинем - копированием) карту подходящую условиям сортировки

						ptr[j] = ptr[35];//переместим(сдвинем - копированием) карту не подходящую условиям сортировки
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//удалим временную карту
					}
				if (four_suit == 4)break;
			case clubs:
				four_suit++;
				for (int j = 0; j < cnt; j++)//организуем поиск всех мастей по рангу и в порядке масти!!!
					if ((ptr[j].card_suit == suitmarks(hearts)) && (ptr[j].card_rank == k))
					{
						//организуем обмен, в качестве временной переменной возьмем последнюю ячейку(уни у кого не может быть на руках 36 карт!!!)
						ptr[35] = ptr[i];//сохраним карту(сдвинем - копированием) карту

						//не забудем теперь смотреть на следующую ячейку для сортировки!!!
						ptr[i++] = ptr[j];//переместим(сдвинем - копированием) карту подходящую условиям сортировки

						ptr[j] = ptr[35];//переместим(сдвинем - копированием) карту не подходящую условиям сортировки
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//удалим временную карту
					}
				if (four_suit == 4)break;
			case hearts:
				four_suit++;
				for (int j = 0; j < cnt; j++)//организуем поиск всех мастей по рангу и в порядке масти!!!
					if ((ptr[j].card_suit == suitmarks(pikes)) && (ptr[j].card_rank == k))
					{
						//организуем обмен, в качестве временной переменной возьмем последнюю ячейку(уни у кого не может быть на руках 36 карт!!!)
						ptr[35] = ptr[i];//сохраним карту(сдвинем - копированием) карту

						//не забудем теперь смотреть на следующую ячейку для сортировки!!!
						ptr[i++] = ptr[j];//переместим(сдвинем - копированием) карту подходящую условиям сортировки

						ptr[j] = ptr[35];//переместим(сдвинем - копированием) карту не подходящую условиям сортировки
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//удалим временную карту
					}
				if (four_suit == 4)break;
			case pikes:
				goto START_SWITCH_SORT_CARD;
			}
		}

	}

		//запрос на количество денег у Игрока
	double PlayerFool::getMoney() const
	{
		return money;
	}

	//узнать имя игрока
	char* PlayerFool::getName()
	{
		return name_;
	}

	//проверка карт, если все одной масти!!!
	bool PlayerFool::checkCards()
	{
		suitmarks tmp = my_card_[0].card_suit;
		for (int i = 1; i < 36; i++)
			if (tmp != my_card_[i].card_suit) return 0;
		return true;
	}
			
	//отбой карт
	void PlayerFool::yourTurn(PlayerFool& opponent)
	{


	}

	//отбой карт Мы отбиваемся от оппонента(компьютера)
	void PlayerFool::notYourTurn(PlayerFool& opponent)
	{
	

	}
	
	//проверка карт у противника и в отбое
	void PlayerFool::checkEnemyCard()
	{
		for (int i = 0; i < cntEnemy_card_; i++)//проверим все известные карты Игрока на наличии их в отбое
			for (int j = 0; j < cntLost_card_; j++)
				if ((enemy_card_[i].card_rank == lost_card_[j].card_rank)//если их ранг равен
					&& (enemy_card_[i].card_suit == lost_card_[j].card_suit))//и масть тоже
				{
					for (int k = i; k < cntEnemy_card_; k++)//удалим эту карту из известных нам
					{
						enemy_card_[k] = enemy_card_[k + 1];//переместим(сдвинем - копированием) карту
						enemy_card_[k + 1] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту
					};
					cntEnemy_card_-- ;
				}
	}


	//сброс карт Игрока
	void PlayerFool::resetCard()
	{
		//сброс карт Игрока
		cntCard_ = 0;
		for (int i = 0; i < 36; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };
		cntLost_card_ = 0;
		for (int i = 0; i < 36; i++)
			lost_card_[i] = { suitmarks(0),color(0),rank(0),0 };
		cntEnemy_card_ = 0;
		for (int i = 0; i < 36; i++)
			enemy_card_[i] = { suitmarks(0),color(0),rank(0),0 };
	}

	//получить карту в "руку" Игрока
	void PlayerFool::takeCard(card* card)
	{
		my_card_[cntCard_++] = *card;
	}
	
	//получение карты в Отбой
	void PlayerFool::takeLostCard(card* card)
	{
		lost_card_[cntLost_card_++] = *card;
	}
	
	//получение карты находящиеся у Игрока
	void PlayerFool::takeEnemyCard(card* card)
	{
		enemy_card_[cntEnemy_card_++] = *card;
	}

	//узнать количество карт в руке Игрока
	int PlayerFool::getCntCard()
	{
		return cntCard_;
	}

	//узнать количество карт в отбое
	int PlayerFool::getCntLostCard()
	{
		return cntLost_card_;
	}

	//узнать количество карт известных у Игрока
	int PlayerFool::getCntEnemyCard()
	{
		return cntEnemy_card_;
	}

	//ввод ставки Игроком
	void PlayerFool::setRate()
	{
		double tmp_rate = 0.;

		while (tmp_rate <= 0) {
			cout << endl << "Введите ставку: " << endl;
			cin >> tmp_rate;
			if (tmp_rate > money)
			{
				tmp_rate = -1;//ставка не возможка
				cout << endl << "Ставка невозможна. Ваши деньги: " << money << endl;
			}
		}

		rate = tmp_rate;
	}

	//затребовать карту из руки с последующим удалением
	card* PlayerFool::getCard(int index)
	{
		cntCard_--;//смотрим на следующую карту

		//создаем указатель на карту для возврата
		card* tmp = new card{ suitmarks(0),color(0),rank(0),0 };
		
		if (cntCard_ < 0)//если карт больше нет, создаем новую Колоду
		{
			cout << endl << "No cards!!!" << endl;		
			return tmp;//вернем указатель без карты
		}
				
		*tmp = my_card_[index];//возьмем карту из руки Игрока
		my_card_[index] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту

		for(int i=0;i<cntCard_;i++)
			if (my_card_[i].card_suit == suitmarks(0))
			{
				my_card_[i] = my_card_[i + 1];//переместим(сдвинем - копированием) карту
				my_card_[i+1] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту
			}

		return tmp;//вернем указатель на забранную карту
	}
	
	//затребовать карту из отбоя с последующим удалением
	card* PlayerFool::getLostCard(int index)
	{
		cntLost_card_--;//смотрим на следующую карту

		//создаем указатель на карту для возврата
		card* tmp = new card{ suitmarks(0),color(0),rank(0),0 };

		if (cntLost_card_ < 0)//если карт больше нет, создаем новую Колоду
		{
			cout << endl << "No cards!!!" << endl;
			return tmp;//вернем указатель без карты
		}

		*tmp = lost_card_[index];//возьмем карту из руки Игрока
		lost_card_[index] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту

		for (int i = 0; i < cntLost_card_; i++)
			if (lost_card_[i].card_suit == suitmarks(0))
			{
				lost_card_[i] = lost_card_[i + 1];//переместим(сдвинем - копированием) карту
				lost_card_[i + 1] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту
			}

		return tmp;//вернем указатель на забранную карту
	}

	//затребовать карту из памяти карт Игрока(оппонента) с последующим удалением
	card* PlayerFool::getEnemyCard(int index)
	{
		cntEnemy_card_--;//смотрим на следующую карту

		//создаем указатель на карту для возврата
		card* tmp = new card{ suitmarks(0),color(0),rank(0),0 };

		if (cntEnemy_card_ < 0)//если карт больше нет, создаем новую Колоду
		{
			cout << endl << "No cards!!!" << endl;
			return tmp;//вернем указатель без карты
		}

		*tmp = enemy_card_[index];//возьмем карту из руки Игрока
		enemy_card_[index] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту

		for (int i = 0; i < cntEnemy_card_; i++)
			if (enemy_card_[i].card_suit == suitmarks(0))
			{
				enemy_card_[i] = enemy_card_[i + 1];//переместим(сдвинем - копированием) карту
				enemy_card_[i + 1] = { suitmarks(0),color(0),rank(0),0 };//удалим эту карту
			}

		return tmp;//вернем указатель на забранную карту
	}
	
	//узнать свою ставку
	double PlayerFool::getRate() const
	{
		return rate;
	}

	//рассчитать свои очки с карт
	void PlayerFool::setRank()
	{
		int tmp_rank = 0.;

		for (int i = 0; i < 36; i++)
			switch (my_card_[i].card_rank)
			{
			case 0:
				tmp_rank += 0;
				break;
			case Six:
				tmp_rank += 6;
				break;
			case Seven:
				tmp_rank += 7;
				break;
			case Eight:
				tmp_rank += 8;
				break;
			case Nine:
				tmp_rank += 9;
				break;
			case Ten:
				tmp_rank += 10;
				break;
			case Jack:
				tmp_rank += 11;
				break;
			case Queen:
				tmp_rank += 12;
				break;
			case King:
				tmp_rank += 13;
				break;
			case Ace:
				tmp_rank += 14;
				break;
			default:
				throw exception("Cards:Wrong rank!");
			}

		rank_ = tmp_rank;
	}

	//запросить очки
	int PlayerFool::getRank()const
	{
		return rank_;
	}

	//вернем значение наименьшего козыря, если такой есть в наличии у Игрока
	int PlayerFool::getMinTrumpCard(suitmarks trumpSuitmarks)
	{
		int tmp_rank = 0;
		int min_rank = 20;
		for (int i = 0; i < cntCard_; i++)
		{
			tmp_rank = 0;
			if (my_card_[i].card_suit == trumpSuitmarks)
				switch (my_card_[i].card_rank)
				{
				case 0:
					break;
				case Six:
					tmp_rank = 6;
					break;
				case Seven:
					tmp_rank = 7;
					break;
				case Eight:
					tmp_rank = 8;
					break;
				case Nine:
					tmp_rank = 9;
					break;
				case Ten:
					tmp_rank = 10;
					break;
				case Jack:
					tmp_rank = 11;
					break;
				case Queen:
					tmp_rank = 12;
					break;
				case King:
					tmp_rank = 13;
					break;
				case Ace:
					tmp_rank = 14;
					break;
				default:
					throw exception("Cards:Wrong rank!");
				}

			if ((min_rank > tmp_rank) && (tmp_rank > 0)) min_rank = tmp_rank;
		}
		return min_rank;
	}

	//краткие сведения об Игроке: имя, карты, деньги и ставка
	char* PlayerFool::toString(int count) const
	{
		
		char* buf = new char[40 * 10 + 40 * 36];
		int j = 0;

		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_, "Карты:");
		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");

		for (int i = 0; i < count; i++)
			if (
				Suitmarks[my_card_[i].card_suit] != "none"
				//				card::getCardSuit(&my_card_[i])!="none"
				)
				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&my_card_[i]), Suitmarks[(*&my_card_[i]).card_suit], card::getCardRank(&my_card_[i]));
				//j += sprintf(buf + j, "%s\n", card::toString(&my_card_[i]));

	//	j += sprintf(buf + j, "%s %.2lf\n", "Деньги:", getMoney());
	//	j += sprintf(buf + j, "%s %.2lf\n", "Ставка:", getRate());

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

	//Показать карты
	char* PlayerFool::toString(char ch) const
	{
		const card* ptr = nullptr;
		int cnt = 0;
		switch (ch)
		{
		case 'A':
			ptr = lost_card_;
			cnt = cntLost_card_;
			break;
		case 'B':
			ptr = enemy_card_;
			cnt = cntEnemy_card_;
			break;
		case 'C':
			ptr = my_card_;
			cnt = cntCard_;
			break;
		}
				
		char* buf = new char[40 * 10 + 40*36];
		int j = 0;

		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_, (ch=='A'?"Карты (ОТБОЙ):":ch=='B'?"Карты (у Игрока): ":"Карты: "));
		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");

		for (int i = 0; i < cnt; i++)
			if (Suitmarks[ptr[i].card_suit] != "none")
				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&ptr[i]), Suitmarks[(*&ptr[i]).card_suit], card::getCardRank(&ptr[i]));
				
		char* res = new char[strlen(buf) + 1];
		strcpy(res, buf);
		delete[] buf;

		return res;
	}

	//выбор карты для подбрасывания оппоненту
	card* PlayerFool::choseCard(int index)
	{
		int tmp_k = 0;
		int roundIndex = cntCard_ - 1;
		char key;

		setCursorVisible(false);

		while (true)
		{
			cout<< "->"
				<< setw(5) << card::getCardColor(&my_card_[tmp_k])
				<< setw(9) << Suitmarks[(*&my_card_[tmp_k]).card_suit]
				<< setw(7) << card::getCardRank(&my_card_[tmp_k])
				<<"\r";


			if (_kbhit())//Проверка нажатия клавиш в консоли, которую следует выполнять перед попыткой чтения из консоли
			{
				
				//запросим от пользователя кнопку управления меню
				keyMenuUpDown(&key);

				switch (key) {
				case 13:
					//нажатие Enter приводит к выполнению(в след. итерации) выбранного меню
					break;
				case 27:
					//Esc для выхода
					tmp_k = -1;
					break;
				case 72:
					//UP вверх по меню 4...3...2...1...0...roundIndex...
					if (tmp_k < 0) {
						tmp_k = roundIndex; break;
					}
					else
						tmp_k--;
					if (tmp_k < 0) tmp_k = roundIndex;
					break;
				case 80:
					//DOWN вниз по меню 1...2...3...4...roundIndex...0...
					tmp_k++;
					if (tmp_k > roundIndex) {
						tmp_k = 0; break;
					}
					if (tmp_k < 0) tmp_k = 0;
					break;
				default:
					//иначе ничего не делать, ждем правильного ввода с клавиатуры
					break;
				}

				if (tmp_k == -1)
					//выход, больше карт не подкидывать
					break;

				if (key == 13)
					//подкинуть карту
					break;
			}

		}
		setCursorVisible(true);


		if (key == 13)
		{

			//отрисуем карту
//			DrawCard(RGB(255, 0, 0), 400, 50, Suitmarks[(*&my_card_[tmp_k]).card_suit], my_card_[tmp_k].card_rank);

			return getCard(tmp_k);
		}
		else
			return new card{ suitmarks(0),color(0),rank(0),0 };
	}

	//выбор карты для подбрасывания оппоненту Компьютером
	card* PlayerFool::choseCardSpecial(card** table_card,int* cntTable,char ch)
	{
		//ИСХОДНЫЕ ДАННЫЕ
		// Мы знаем карты в отбое lost_card_ и их количество cntLost_card_
		// Мы знаем некоторые карты Игрока enemy_card_ и их количество cntEnemy_card_
//Мы знаем карты на столе через аргументы table_card и их количество cntTable
//Мы знаем свои карты my_card_ и их количество cntCard_
//
//
//


		//проверка карт известных у Игрока на наличие их в отбое
		checkEnemyCard();

		//************************************
		//******
		//************************************
		//можем узнать какие карты еще не участвовали в Игре
		//Колода карт
		Deck newDeck(EASY_DECK); 
		//карты еще не участвовашие в Игре
		card not_play_card[36];
		int cntNotPlay_card = 0;

		//проверим с Отбоем
		for (int i = 0; i < 36; i++)//проверим все известные карты Игрока на наличии их в отбое
		{
			//возьмем одну стандартную карту из чистой колоды
			not_play_card[cntNotPlay_card] = newDeck.getCard(i);

			if (not_play_card[cntNotPlay_card].card_rank == rank(0))
				continue;//карту уже находили в подколоде
			//проверим её со всеми картами из существующих подколод(Отбой, у Игрока, на столе, нашими картами)

		//с отбойной подколодой
			for (int j = 0; j < cntLost_card_; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == lost_card_[j].card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == lost_card_[j].card_suit))
				{
					//карта уже засветилась!!!
					cntNotPlay_card++;
					continue;//перейдем к поиску следующей карты
				}
			//с картами Игрока
			for (int j = 0; j < cntEnemy_card_; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == enemy_card_[j].card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == enemy_card_[j].card_suit))
				{
					//карта уже засветилась!!!
					cntNotPlay_card++;
					continue;//перейдем к поиску следующей карты
				}
			//с собственными картами)
			for (int j = 0; j < cntCard_; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == my_card_[j].card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == my_card_[j].card_suit))
				{
					//карта уже засветилась!!!
					cntNotPlay_card++;
					continue;//перейдем к поиску следующей карты
				}
			//с картами на игровом столе(текущий КОН)
			for (int j = 0; j < *cntTable; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == table_card[j]->card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == table_card[j]->card_suit))
				{
					//карта уже засветилась!!!
					cntNotPlay_card++;
					continue;//перейдем к поиску следующей карты
				}

			

			//карта не засвечена, вернем в колоду
			newDeck.setCard(not_play_card[cntNotPlay_card],i);
		};
		//************************************
		//******
		//************************************

		//************************************
		//******
		//************************************
//можем узнать сколько всего карт осталось в Игре
//		int tmpLost = 36 - cntLost_card_ - cntEnemy_card_ - cntCard_;// -*cntTable;//оставшиеся карты: колода за вычетом в отбое, добранных Игроком, моих карт и на столе
//		//cntNotPlay_card;//всего карт не сыгравших
//		int tmpPlayer;
//		if (cntEnemy_card_ > 0)
//			tmpPlayer = 6 + cntEnemy_card_ - (*cntTable / 2);//карты Игрока с учетом добора и вычетом на столе
//		else
//			tmpPlayer = 6;//не знаем сколько карт, но точно не более 6
//		//мы знаем карты противника
//		if ((36-cntNotPlay_card) <= tmpPlayer)
//			for (int i = 0; i < cntNotPlay_card; i++)
//				cout << card::toString(&not_play_card[i]);
		//************************************
		//******
		//************************************



		//ручная игра
		if (ch=='B')
			//играть самим с собой(Два Игрока)
			return choseCard();

		//автоматическая, берем и ходим с наименьшей карты
		//бьем первой подходящей картой(даже козырем)
		if (ch == 'A')
		{
			//введем количество попыток на отбой и на походить
			int max_try_cnt = cntCard_;// 36;//не может быть у нас более 36 карт
			int index = 0;
			switch (*cntTable % 2)//логика игры компьютера против Игрока
			{
			case 0:
				//подкидываем карты
				// *** СТРАТЕГИЯ ПРИ ПОДКИДЫВАНИИ КАРТ ***

				while (max_try_cnt-- > 0)
				{
					if (index >= cntCard_) index = 0;

					cout << "->"
						<< setw(5) << card::getCardColor(&my_card_[index])
						<< setw(9) << Suitmarks[(*&my_card_[index]).card_suit]
						<< setw(7) << card::getCardRank(&my_card_[index])
						//<< endl; // если хотим посмотреть весь перебор карт
						<< "\r";

					//
					//if (!card::checkEqualRank(table_card, *cntTable))//проверка на допустимость карты в ходе не прошла
					//{
					//}
					if (*cntTable <= 1)
						//выдадим карту первую в руке
						return getCard(index);
					//проверим на допустимость
					int count = 0;
					for (int j = 0; j < *cntTable; j++)
						if ((my_card_[index].card_rank) == (table_card[j]->card_rank))
							count++;
					if (count < 1)
					{	//карта не подошла!!!
						index++;//попробуем следующую карту
						continue;
					}
					//
					//выдадим карту
					return getCard(index);
				}
				cout << "->"
					<< "                 *** Отбился!!! ***                  "
					<< "\r";
				break;
			case 1:
				//отбиваемся
				// *** СТРАТЕГИЯ ПРИ ОТБИВАНИИ ***

				while (max_try_cnt-- > 0)
				{
					if (index >= cntCard_) index = 0;

					cout << "->"
						<< setw(5) << card::getCardColor(&my_card_[index])
						<< setw(9) << Suitmarks[(*&my_card_[index]).card_suit]
						<< setw(7) << card::getCardRank(&my_card_[index])
						//<< endl; // если хотим посмотреть весь перебор карт
						<< "\r";

					//
					//if (card::checkRankOK(table_card, *cntTable - 1, *cntTable - 2, trump_card_))
					//{
					//}
					if (
						((my_card_[index].card_rank > table_card[*cntTable - 1]->card_rank)//карта выше рангом
							&& (my_card_[index].card_suit == table_card[*cntTable - 1]->card_suit))//карты одной масти, тоже для козырных
						||
						((my_card_[index].card_suit == trump_card_)//карта козырная
							&& (table_card[*cntTable - 1]->card_suit != trump_card_))//бьет карту обычную
						)
						//выдадим карту
						return getCard(index);
					else
					{
						index++;//попробуем следующую карту
						continue;
					}
					//
				}
				cout << "->"
					<< "                 *** Беру!!! ***                  "
					<< "\r";
				break;
			}

			//принято решение взять карту или прекратить подкидывать
			return new card{ suitmarks(0),color(0),rank(0),0 }; 
		}
	}

#pragma endregion

	//METHODS
#pragma region METHODS



#pragma endregion

#pragma region OPERATORS


#pragma endregion

#pragma endregion




#pragma endregion;


	void TestClassBlackjack() {



	}

}