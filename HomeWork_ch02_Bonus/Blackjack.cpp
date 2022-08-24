#pragma once

#include "Blackjack.h"


#include "pch.h"
#include "Utils.h"
#include "UtilsConsole.h"
#include "Func.h"

extern wchar_t title[150];

namespace classApp {

#pragma region card

	//�������� ����� ����� ����� ������
		const char* card::getCardSuit(const card* const object)
		{
			//�������� ����� ����� �� ������� ������
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

		//������� ���� �����
		const char* card::getCardColor(const card* const object)
		{
			//�� ����� ����� ������ ���������� �������� �����
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

		//������ �������� �����
		const char* card::getCardRank(const card* const object)
		{
			//�������� ����������� �������� �����
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

		//��������� ������������� �����: ����� ������, ����, �����, ������� �����
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

		//�������� ���� �� ������������� ����, ����� ������ ���� ������� ������!!!
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

		//�������� �����(index1) ���� ������ �����(index2)
		bool card::checkRankOK(card* tmp[], int index1, int index2,suitmarks trump_suit)
		{
			if (
				((tmp[index1]->card_rank > tmp[index2]->card_rank)//����� ���� ������
					&& (tmp[index1]->card_suit == tmp[index2]->card_suit))//����� ����� �����, ���� ��� ��������
				||
				((tmp[index1]->card_suit == trump_suit)//����� ��������
					&& (tmp[index2]->card_suit != trump_suit))//���� ����� �������
				)
				return true;
			
			return false;
		}
		
#pragma endregion

#pragma region Cards
	//STATIC data
#pragma region STATIC_data

	//�������������� ����������� ����������-������� ��������� ��������
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
		//������������� ����������� ������ ���� �� ���������
		for (int i = 0; i < max_card_; i++)
		{
			deck_[i].deck_number = 0;
			if (i < (max_card_/4))//13 ���� ������ �����
				deck_[i].card_suit = clubs;
			else if (i < (max_card_/2))
				deck_[i].card_suit = pikes;
			else if (i < ((max_card_/4)*3))
				deck_[i].card_suit = hearts;
			else
				deck_[i].card_suit = diamonds;

			if (i < max_card_/2)//������ ��� �����, ������� ������, ����� ������� ����� ��������������
				deck_[i].card_color = black;
			else
				deck_[i].card_color = red;

		if (max_card_==EASY_DECK)
			//����������� �������� ������ �� 6 �� 14(���)
			deck_[i].card_rank = rank(6 + i % (max_card_/4));
		else
			//����������� �������� ������ �� 2 �� 14(���)
			deck_[i].card_rank = rank(2 + i % (max_card_ / 4));
		}
			   		 	  
#ifdef _DEBUG
//		cout << endl << "����������� �� ���������(��� ����������). ����� Cards.\n";
//		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	Deck::Deck(const Deck& object)
		:max_card_{ object.max_card_ }
		, next_card_{ object.max_card_ }
	{
		//������ � ��� ����������, ������ �������� ����� �� ����� � ������
		for (int i = 0; i < max_card_; i++)
			this->deck_[i] = object.deck_[i];
			   
#ifdef _DEBUG
	//	cout << endl << "����������� �����������. ����� Cards.\n";
	//	cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	//destructor
	Deck::~Deck() {
		//������������ �������� � ��� �����������

#ifdef _DEBUG
	//	cout << endl << "����������. ����� Cards.\n";
	//	cout << "����� ���������� " << --count_ << " ��������\n";
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

	//������ ����� ����� �� ������� � ������
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

	//������ ����� ����� �� ������� � ������
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

	//������ �������� ����� �� ������� � ������
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

	//��������� �����
	card& Deck::getCard(int index)
	{
		return deck_[index];
	}

	//����������� ����� �� ������ � ����������� ���������
	card* Deck::getCard()
	{
		if (next_card_>=0)
			next_card_--;//������� �� ��������� �����

		//������� ��������� �� ����� ��� ��������
		card* tmp = new card{ suitmarks(0), color(0), rank(0), 0 };

		if (next_card_ < 0)//���� ���� ������ ���
		{
			next_card_ = 0;//���� ���
			cout << endl << "No cards yet!!!" << endl;
			return tmp;//������ ��������� �� ��������� �����
		}
				
		*tmp = deck_[next_card_];//������� ����� �� ������
		EmptyCard(next_card_);//������ ��� �����

		return tmp;//������ ��������� �� ��������� �����
	}
	
	//�������� ����� � ������ ��� ��������, ���������� ������
	void Deck::setCard(card& object, int index_card)
	{
		deck_[index_card] = object;
	}

	//������ ���������� ���� � ���� ������
	int Deck::getCntCard()
	{
		return next_card_;
	}
	
	//������ ����� ������ �����
	int Deck::getDeckNumber(int index)
	{
		return deck_[index].deck_number;
	}

	//���������� ����� ������ ��� ������������� � ������� ��������
	void Deck::setDeckNumber(int number)
	{
		for(int i=0;i< max_card_;i++)
			deck_[i].deck_number = number;
	}

	//���������� �������� �����
	void Deck::setTrumpCard()
	{
		trump_card_ = deck_[0].card_suit;
	}

	//������ �������� �����
	suitmarks Deck::getTrumpCard()
	{
		return trump_card_;
	}

#pragma endregion

	//METHODS
#pragma region METHODS

	//����� ���� ������: ����� �����, ����� ������, ����, �����, ������� �����
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

	//����� ����� �� ������ ��� �������� : ����� �����, ����� ������, ����, �����, ������� �����
	char* Deck::toString(int i) const
	{
		char* buf = new char[100];

		sprintf(buf, "%2d %2d %10s %8s %10s \n", (i+1), deck_[i].deck_number, getCardColor(i), Suitmarks[deck_[i].card_suit]/*getCardSuit(i)*/, getCardRank(i));

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

	//�������� �� ������� ����� ��� ��������
	bool Deck::IsEmpty(int index)
	{
		if (
			Suitmarks[deck_[index].card_suit] == "none"//���������� ��������� ���� �� ���������� ����������(�����) �����(�����, ����, �������)
			//getCardSuit(index) == "none"

			//	|| getCardColor(index) == "none" 
			//	|| getCardRank(index) == "none"
			) return true;
		
		return false;
	}

	//�������� ����� �� ������
	void Deck::EmptyCard(int index)
	{
		if (index >= 0 && index < max_card_)
		{
			deck_[index] = { suitmarks(0),color(0),rank(0),0 };//������(�������) ��� ���� �����
		//	deck_[index].card_suit = suitmarks(0);
		//	deck_[index].card_color = color(0);
		//	deck_[index].card_rank = rank(0);
			return;
		}
		throw exception("Cards:Wrong index.");
	}

	//���������� �����
	void Deck::Shuffle()
	{
		//�������� ����� ������ ����
		card new_deck[52];//����� ������������ � ����� ������ Deck new_deck; new_deck.deck_[i];
		//������ ��� �������, ����� �� �����������
//		cout << toString();

		//����� ��������� � �����
		int cnt = max_card_;
		int tmp;//��������� ������ � ������
		while (cnt > 0)//���� �� ��������� ��� ����� ������, ��������� ������� ���������� � ��������� �������
		{
			tmp = genRand(0, max_card_-1);//����������� ����� ��������� ������
			if (IsEmpty(tmp)) continue;//���� �� ����� ������� ��� ������� �����, ��������� ��������
			
			//������ ����������, �������� ����� � ���� ����� ������
			new_deck[--cnt] = deck_[tmp];
//			deck_[tmp] = { suitmarks(0),color(0),rank(0) };
//			deck_[tmp].card_suit = suitmarks(0);
			EmptyCard(tmp);//� ������ ������ ����� �������
		}

		//����������� ���� �������� ������, ����� �������������� �������!!!
		for (int i = 0; i < max_card_; i++)
			deck_[i] = new_deck[i];
	
		//��������� ������ ����� � �������� �������� �����
		setTrumpCard();
		//������ ��� �������, ����� ����� �����������
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
		cout << endl << "�������� ������������. ����� Cards.\n";
		cout << "����� ���������� " << count_ << " ��������\n";
#endif
		return *this;
	} // operator=

	
#pragma endregion

#pragma endregion

	void TestClassCards() {
	
		cls();

		// ��������� ���������� ��������� ����
		SetConsoleTitle(title);
		// ��������� ���������� ��������� ����
		myAddConsoleTitle(L" ������������ ������ Cards ");

		coutColor("\n�������� ��� ��������� �������\n", wAttributeSpecial);

		Deck c1(EASY_DECK);
		Deck c2=c1;

		coutColor("\n������� ���� �������.\n", wAttributeSpecial);
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;

		//************************
		coutColor("\n���������� � �������� �1 � �������� 4\n", wAttributeSpecial);

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
				
		coutColor("\n������������ ���������� ���������� []\n", wAttributeSpecial);
		
		for (int i = 0; i < 52; i++)
			cout << endl << c1[i].card_rank;

		coutColor("\n�������� ���������� ����� ��������\n", wAttributeSpecial);
		//������� ���������� � ������������ �������� � �������
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

	//�������������� ����������� ����������-������� ��������� ��������
	int Shoes::count_ = 0;

	//��� ������� ���������, ����������������� ���������� ��������������� �����
	//������ �� 6 �� 8, �� ���� ���� � � ����� �������
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
		//������������� �������� ���� � ����
		next_card_ = 52 * decks_;

		shoes_ = new Deck[decks_];
		//������ ��� �������, �� ����������� ����� � ����
//		cout << toString();

		for (int i = 0; i < decks_; i++)
		{
			shoes_[i].setDeckNumber(i);
			shoes_[i].Shuffle();
		}
		//������ ��� �������, ����� ����������� ���� ����� �� �����������
//		cout << toString();

		//����������� ��� ����� ����(����� � �������)
		Shuffle();
		setSpecialCard();//������ �� ���� ����� ���� ����� �����������
		
		//������ ��� �������, ����� ����������� ����� ����
//		cout << toString();

#ifdef _DEBUG
		cout << endl << "����������� �� ���������(��� ����������). ����� Shoes.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	Shoes::Shoes(const Shoes& object)
		:shoes_{ nullptr }
	{
		next_card_ = 52 * decks_;
		setSpecialCard();//������ �� ���� ����� ����

		shoes_ = new Deck[decks_];

		for (int i = 0; i < decks_; i++)
			shoes_[i] = object.shoes_[i];

#ifdef _DEBUG
		cout << endl << "����������� �����������. ����� Shoes.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	//destructor
	Shoes::~Shoes() {

		if (shoes_ != nullptr)
			delete[] shoes_;
		shoes_ = nullptr;

#ifdef _DEBUG
		cout << endl << "����������. ����� Shoes.\n";
		cout << "����� ���������� " << --count_ << " ��������\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	//������ ����� �� ����
	card* Shoes::getCard() 
	{
		next_card_--;//������� �� ��������� �����

		if (next_card_ < 0)//���� ���� ������ ���, ������� ����� ���
		{
			//� ���� �������� ����� ���
			cout << endl << "New Shoes create!!!" << endl;
			Shoes new_shoe;
			*this = new_shoe;
		}

		//������� ������� ������ � ����� � ����
		int tmp_deck_index = next_card_ / 52;
		int tmp_card_index = next_card_ % 52;
		//������� ��������� �� ����� ��� ��������
		card* tmp = new card;
		*tmp= shoes_[tmp_deck_index].getCard(tmp_card_index);//������� ����� �� ����
		shoes_[tmp_deck_index].EmptyCard(tmp_card_index);//������ ��� �����

		return tmp;//������ ��������� �� ��������� �����
	}

	//���������� ���������� ����� � ������ ������ � ������ �����
	void Shoes::setCard(card& object, int index_deck, int index_card) 
	{
		shoes_[index_deck].setCard(object,index_card);
	}

	//��������� ���� �����(������ ����� ���� �� ����)
	void Shoes::setSpecialCard()
	{
		//� ����� ������ �� �������� � �� �����
		int special_index = genRand(next_card_/2,next_card_);
		next_card_ = special_index;
	}

	//�������� �� ���� ����� (�� �������������)
	void Shoes::IsSpecialCard()
	{

	}

	//����������� ����!!!!
	void Shoes::Shuffle()
	{
		//������ ���������� ����������� ������

		//������� ������ ���� ���� � ����!!!!
		card* new_deck = new card[next_card_];
		
		int cnt = next_card_;//����� ��������� ������ � �����
		int tmp;

		//�������� ���������� ��� ������ ������ � ����� � ������
		int tmp_deck_index;
		int tmp_card_index;
				
		while (cnt > 0)//���� �� ��� ����� ����������
		{
			tmp = genRand(0, next_card_ - 1);//���������� ��������� ������
			
			//��������� ���������� ������ � ����� ������ � ����� � ������
			tmp_deck_index = tmp / 52;
			tmp_card_index = tmp % 52;

			if (shoes_[tmp_deck_index].IsEmpty(tmp_card_index)) continue;//���� ����� �����, ���� ��������� ������

			new_deck[--cnt] = shoes_[tmp_deck_index].getCard(tmp_card_index);//�������� �����

			shoes_[tmp_deck_index].EmptyCard(tmp_card_index);//������� ����� � ����
		}	

		//�������� ��� ������ � �������� ���
		for (int i = 0; i < next_card_; i++)
		{
			tmp_deck_index = i / 52;
			tmp_card_index = i % 52;
			setCard(new_deck[i], tmp_deck_index, tmp_card_index);
		}

		//������� ������������ ������ � �������
		delete[] new_deck;
	}

	//����� ���� � ����
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
		cout << endl << "�������� ������������. ����� Shoes.\n";
		cout << "����� ���������� " << count_ << " ��������\n";
#endif
		return *this;
	} // operator=


#pragma endregion

#pragma endregion

	void TestClassShoes(){

		cls();

		// ��������� ���������� ��������� ����
		SetConsoleTitle(title);
		// ��������� ���������� ��������� ����
		myAddConsoleTitle(L" ������������ ������ Shoes ");

		coutColor("\n�������� ��� ��������� �������\n", wAttributeSpecial);

		Shoes c1;
		Shoes c2 = c1;

		coutColor("\n������� ���� �������.\n", wAttributeSpecial);
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;

		anyKey();

		//************************
		coutColor("\n���������� � �������� �1 \n", wAttributeSpecial);

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
		
		coutColor("\n�������� ���������� ����� ��������\n", wAttributeSpecial);
		//������� ���������� � ������������ �������� � �������
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

	//�������������� ����������� ����������-������� ��������� ��������
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
		//� ������ ���������� 1000 �.�.
		money = 1000.;
		rank_ = 0;
		rate = 0;
		cntCard_ = 0;

		strcpy(name_, name);//����������� ���������� ���
		//��������������(��������) ������ ����
		for (int i = 0; i < 10; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };
		
#ifdef _DEBUG
		cout << endl << "����������� � �����������. ����� Player.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	//constructor
	Player::Player(const char* name,double money)
	{
		//��������� ������ ������(���� ������)
		this->money = money;
		rank_ = 0;
		rate = 0;
		cntCard_ = 0;

		//�������� ��� ������
		strcpy(name_,name);
		//��������������(��������) ������ ����
		for (int i = 0; i < 10; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };

#ifdef _DEBUG
		cout << endl << "����������� � �����������. ����� Player.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}
		
	//destructor
	Player::~Player() {
		
#ifdef _DEBUG
		cout << endl << "����������. ����� Player.\n";
		cout << "����� ���������� " << --count_ << " ��������\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	//����� ���� ������
	void Player::resetCard()
	{
		//����� ���� ������
		cntCard_ = 0;
		for (int i = 0; i < 10; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };
	}

	//������������� ������� ����� ��������
	void Player::winner(Player& winner, Player& loser, double koefficient)
	{
		if (koefficient == 1.) 
		{
			//������ ����������
			winner.setRate(loser.setMoney(false));
			winner.setMoney(true);
		}
		else
		{
			//������ �����������
			loser.setRate(winner.setMoney(true, koefficient));
			loser.setMoney(false);
		}
	}

	//�������� ����� � "����" ������
	void Player::takeCard(card* card)
	{
		my_card_[cntCard_++] = *card;
	}

	//�������� �� ������� ���� � ������ ����� � "����"
	bool Player::checkIfAceIsFirstCard()
	{
		if (card::getCardRank(&my_card_[0])=="-  A -")
			return true;

		return false;
	}

	//������ �����, � ��������� ����������� �����
	double Player::setMoney(bool winner, double koefficient)
	{
		double result;
		if (winner)
			money += result =(rate * koefficient);
		else
			money -= result = rate;

		return result;
	}

	//������ �� ���������� ����� � ������
	double Player::getMoney() const
	{
		return money;
	}

	//��������� ������
	void Player::setRate(double rate)
	{
		if (rate >= 0.)
			this->rate = rate;
	}

	//���� ������ �������
	void Player::setRate()
	{
		double tmp_rate =0.;

		while (tmp_rate <= 0) {
			cout << endl << "������� ������: " << endl;
			cin >> tmp_rate;
			if (tmp_rate > money)
			{
				tmp_rate = -1;//������ �� ��������
				cout << endl << "������ ����������. ���� ������: " << money << endl;
			}
		}

		rate = tmp_rate;
	}

	//������ ���� ������
	double Player::getRate() const
	{
		return rate;
	}

	//���������� ���� ���� � ����
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

		//���� ���� ��� �� ��� �������� ���������� �� 1, � �� �� 11
		while ((ace-- > 0)&&(tmp_rank>21))
			tmp_rank -= 10;

		rank_ = tmp_rank;
	}

	//��������� ����
	int Player::getRank()const
	{
		return rank_;
	}


	void Player::hitMe()
	{
		cout << "\n��� �����!!!\n";
	}

	void Player::pass()
	{
		cout << "\n����...\n";
	}

	//������� �������� �� ������: ���, �����, ������ � ������
	char* Player::toString(int count) const
	{
		char* buf = new char[40 * 10 + 200];
		int j = 0;

		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_,"�����:");
		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");

		for (int i = 0; i < count; i++)
			if (
				Suitmarks[my_card_[i].card_suit] != "none"
				//				card::getCardSuit(&my_card_[i])!="none"
				)
				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&my_card_[i]), Suitmarks[(*&my_card_[i]).card_suit], card::getCardRank(&my_card_[i]));
				//j += sprintf(buf + j, "%s\n", card::toString(&my_card_[i]));


		j += sprintf(buf + j, "%s %.2lf\n", "������:", getMoney());
		j += sprintf(buf + j, "%s %.2lf\n", "������:", getRate());

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

	//�������������� ����������� ����������-������� ��������� ��������
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
		//� ������ ���������� 1000 �.�.
		money = geld;
		rank_ = 0;
		rate = 0.;

		cntCard_ = 0;
		cntLost_card_ = 0;
		cntEnemy_card_ = 0;

		strcpy(name_, name);//����������� ���������� ���
		//��������������(��������) ������ ����
		for (int i = 0; i < 36; i++)
			my_card_[i] = { suitmarks(0),color(0),rank(0),0 };

		//��������������(��������) ������ ����
		for (int i = 0; i < 36; i++)
			lost_card_[i] = { suitmarks(0),color(0),rank(0),0 };

		//��������������(��������) ������ ����
		for (int i = 0; i < 36; i++)
			enemy_card_[i] = { suitmarks(0),color(0),rank(0),0 };

#ifdef _DEBUG
		cout << endl << "����������� � �����������. ����� PlayerFool.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	//destructor
	PlayerFool::~PlayerFool() {

#ifdef _DEBUG
		cout << endl << "����������. ����� PlayerFool.\n";
		cout << "����� ���������� " << --count_ << " ��������\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

			//����� ���������� ���� (����� ����� ����� ����)
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
//		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_, "�����:");
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

		//�������� ����� � ���������� �������
		//������� ���������� ����� 6�� ����, ����� ���� � �.�.

//		for (int i = 0; i < cnt; i++)//���� �� ���� ������(�� ������ ������������� ��� �����)
		int r = 2;
		int i = 0;
		for (rank k = Two; k <= Ace; r++, k = rank(r))//��������� �� ����� �� 2 �� ���� � � ������� �����!!!
		{
			//suitmarks cnt = trump_card_;
			int four_suit = 0;
			switch (trump_card_)//������ ����� ����� ������!!! ������ � �����
			{
			START_SWITCH_SORT_CARD:
				four_suit++;
				for (int j = 0; j < cnt; j++)//���������� ����� ���� ������ �� ����� � � ������� �����!!!
					if ((ptr[j].card_suit == suitmarks(diamonds)) && (ptr[j].card_rank == k))
					{
						//���������� �����, � �������� ��������� ���������� ������� ��������� ������(��� � ���� �� ����� ���� �� ����� 36 ����!!!)
						ptr[35] = ptr[i];//�������� �����(������� - ������������) �����

						//�� ������� ������ �������� �� ��������� ������ ��� ����������!!!
						ptr[i++] = ptr[j];//����������(������� - ������������) ����� ���������� �������� ����������

						ptr[j] = ptr[35];//����������(������� - ������������) ����� �� ���������� �������� ����������
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//������ ��������� �����
					}
				if (four_suit == 4)break;
			case diamonds:
				four_suit++;
				for (int j = 0; j < cnt; j++)//���������� ����� ���� ������ �� ����� � � ������� �����!!!
					if ((ptr[j].card_suit == suitmarks(clubs)) && (ptr[j].card_rank == k))
					{
						//���������� �����, � �������� ��������� ���������� ������� ��������� ������(��� � ���� �� ����� ���� �� ����� 36 ����!!!)
						ptr[35] = ptr[i];//�������� �����(������� - ������������) �����

						//�� ������� ������ �������� �� ��������� ������ ��� ����������!!!
						ptr[i++] = ptr[j];//����������(������� - ������������) ����� ���������� �������� ����������

						ptr[j] = ptr[35];//����������(������� - ������������) ����� �� ���������� �������� ����������
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//������ ��������� �����
					}
				if (four_suit == 4)break;
			case clubs:
				four_suit++;
				for (int j = 0; j < cnt; j++)//���������� ����� ���� ������ �� ����� � � ������� �����!!!
					if ((ptr[j].card_suit == suitmarks(hearts)) && (ptr[j].card_rank == k))
					{
						//���������� �����, � �������� ��������� ���������� ������� ��������� ������(��� � ���� �� ����� ���� �� ����� 36 ����!!!)
						ptr[35] = ptr[i];//�������� �����(������� - ������������) �����

						//�� ������� ������ �������� �� ��������� ������ ��� ����������!!!
						ptr[i++] = ptr[j];//����������(������� - ������������) ����� ���������� �������� ����������

						ptr[j] = ptr[35];//����������(������� - ������������) ����� �� ���������� �������� ����������
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//������ ��������� �����
					}
				if (four_suit == 4)break;
			case hearts:
				four_suit++;
				for (int j = 0; j < cnt; j++)//���������� ����� ���� ������ �� ����� � � ������� �����!!!
					if ((ptr[j].card_suit == suitmarks(pikes)) && (ptr[j].card_rank == k))
					{
						//���������� �����, � �������� ��������� ���������� ������� ��������� ������(��� � ���� �� ����� ���� �� ����� 36 ����!!!)
						ptr[35] = ptr[i];//�������� �����(������� - ������������) �����

						//�� ������� ������ �������� �� ��������� ������ ��� ����������!!!
						ptr[i++] = ptr[j];//����������(������� - ������������) ����� ���������� �������� ����������

						ptr[j] = ptr[35];//����������(������� - ������������) ����� �� ���������� �������� ����������
						ptr[35] = { suitmarks(0),color(0),rank(0),0 };//������ ��������� �����
					}
				if (four_suit == 4)break;
			case pikes:
				goto START_SWITCH_SORT_CARD;
			}
		}

	}

		//������ �� ���������� ����� � ������
	double PlayerFool::getMoney() const
	{
		return money;
	}

	//������ ��� ������
	char* PlayerFool::getName()
	{
		return name_;
	}

	//�������� ����, ���� ��� ����� �����!!!
	bool PlayerFool::checkCards()
	{
		suitmarks tmp = my_card_[0].card_suit;
		for (int i = 1; i < 36; i++)
			if (tmp != my_card_[i].card_suit) return 0;
		return true;
	}
			
	//����� ����
	void PlayerFool::yourTurn(PlayerFool& opponent)
	{


	}

	//����� ���� �� ���������� �� ���������(����������)
	void PlayerFool::notYourTurn(PlayerFool& opponent)
	{
	

	}
	
	//�������� ���� � ���������� � � �����
	void PlayerFool::checkEnemyCard()
	{
		for (int i = 0; i < cntEnemy_card_; i++)//�������� ��� ��������� ����� ������ �� ������� �� � �����
			for (int j = 0; j < cntLost_card_; j++)
				if ((enemy_card_[i].card_rank == lost_card_[j].card_rank)//���� �� ���� �����
					&& (enemy_card_[i].card_suit == lost_card_[j].card_suit))//� ����� ����
				{
					for (int k = i; k < cntEnemy_card_; k++)//������ ��� ����� �� ��������� ���
					{
						enemy_card_[k] = enemy_card_[k + 1];//����������(������� - ������������) �����
						enemy_card_[k + 1] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����
					};
					cntEnemy_card_-- ;
				}
	}


	//����� ���� ������
	void PlayerFool::resetCard()
	{
		//����� ���� ������
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

	//�������� ����� � "����" ������
	void PlayerFool::takeCard(card* card)
	{
		my_card_[cntCard_++] = *card;
	}
	
	//��������� ����� � �����
	void PlayerFool::takeLostCard(card* card)
	{
		lost_card_[cntLost_card_++] = *card;
	}
	
	//��������� ����� ����������� � ������
	void PlayerFool::takeEnemyCard(card* card)
	{
		enemy_card_[cntEnemy_card_++] = *card;
	}

	//������ ���������� ���� � ���� ������
	int PlayerFool::getCntCard()
	{
		return cntCard_;
	}

	//������ ���������� ���� � �����
	int PlayerFool::getCntLostCard()
	{
		return cntLost_card_;
	}

	//������ ���������� ���� ��������� � ������
	int PlayerFool::getCntEnemyCard()
	{
		return cntEnemy_card_;
	}

	//���� ������ �������
	void PlayerFool::setRate()
	{
		double tmp_rate = 0.;

		while (tmp_rate <= 0) {
			cout << endl << "������� ������: " << endl;
			cin >> tmp_rate;
			if (tmp_rate > money)
			{
				tmp_rate = -1;//������ �� ��������
				cout << endl << "������ ����������. ���� ������: " << money << endl;
			}
		}

		rate = tmp_rate;
	}

	//����������� ����� �� ���� � ����������� ���������
	card* PlayerFool::getCard(int index)
	{
		cntCard_--;//������� �� ��������� �����

		//������� ��������� �� ����� ��� ��������
		card* tmp = new card{ suitmarks(0),color(0),rank(0),0 };
		
		if (cntCard_ < 0)//���� ���� ������ ���, ������� ����� ������
		{
			cout << endl << "No cards!!!" << endl;		
			return tmp;//������ ��������� ��� �����
		}
				
		*tmp = my_card_[index];//������� ����� �� ���� ������
		my_card_[index] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����

		for(int i=0;i<cntCard_;i++)
			if (my_card_[i].card_suit == suitmarks(0))
			{
				my_card_[i] = my_card_[i + 1];//����������(������� - ������������) �����
				my_card_[i+1] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����
			}

		return tmp;//������ ��������� �� ��������� �����
	}
	
	//����������� ����� �� ����� � ����������� ���������
	card* PlayerFool::getLostCard(int index)
	{
		cntLost_card_--;//������� �� ��������� �����

		//������� ��������� �� ����� ��� ��������
		card* tmp = new card{ suitmarks(0),color(0),rank(0),0 };

		if (cntLost_card_ < 0)//���� ���� ������ ���, ������� ����� ������
		{
			cout << endl << "No cards!!!" << endl;
			return tmp;//������ ��������� ��� �����
		}

		*tmp = lost_card_[index];//������� ����� �� ���� ������
		lost_card_[index] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����

		for (int i = 0; i < cntLost_card_; i++)
			if (lost_card_[i].card_suit == suitmarks(0))
			{
				lost_card_[i] = lost_card_[i + 1];//����������(������� - ������������) �����
				lost_card_[i + 1] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����
			}

		return tmp;//������ ��������� �� ��������� �����
	}

	//����������� ����� �� ������ ���� ������(���������) � ����������� ���������
	card* PlayerFool::getEnemyCard(int index)
	{
		cntEnemy_card_--;//������� �� ��������� �����

		//������� ��������� �� ����� ��� ��������
		card* tmp = new card{ suitmarks(0),color(0),rank(0),0 };

		if (cntEnemy_card_ < 0)//���� ���� ������ ���, ������� ����� ������
		{
			cout << endl << "No cards!!!" << endl;
			return tmp;//������ ��������� ��� �����
		}

		*tmp = enemy_card_[index];//������� ����� �� ���� ������
		enemy_card_[index] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����

		for (int i = 0; i < cntEnemy_card_; i++)
			if (enemy_card_[i].card_suit == suitmarks(0))
			{
				enemy_card_[i] = enemy_card_[i + 1];//����������(������� - ������������) �����
				enemy_card_[i + 1] = { suitmarks(0),color(0),rank(0),0 };//������ ��� �����
			}

		return tmp;//������ ��������� �� ��������� �����
	}
	
	//������ ���� ������
	double PlayerFool::getRate() const
	{
		return rate;
	}

	//���������� ���� ���� � ����
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

	//��������� ����
	int PlayerFool::getRank()const
	{
		return rank_;
	}

	//������ �������� ����������� ������, ���� ����� ���� � ������� � ������
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

	//������� �������� �� ������: ���, �����, ������ � ������
	char* PlayerFool::toString(int count) const
	{
		
		char* buf = new char[40 * 10 + 40 * 36];
		int j = 0;

		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_, "�����:");
		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");

		for (int i = 0; i < count; i++)
			if (
				Suitmarks[my_card_[i].card_suit] != "none"
				//				card::getCardSuit(&my_card_[i])!="none"
				)
				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&my_card_[i]), Suitmarks[(*&my_card_[i]).card_suit], card::getCardRank(&my_card_[i]));
				//j += sprintf(buf + j, "%s\n", card::toString(&my_card_[i]));

	//	j += sprintf(buf + j, "%s %.2lf\n", "������:", getMoney());
	//	j += sprintf(buf + j, "%s %.2lf\n", "������:", getRate());

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

	//�������� �����
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

		j += sprintf(buf + j, "\n\t *** %s *** \n%s\n", name_, (ch=='A'?"����� (�����):":ch=='B'?"����� (� ������): ":"�����: "));
		j += sprintf(buf + j, "%5s %9s %7s\n", "Color", "Suitmarks", "Rank");

		for (int i = 0; i < cnt; i++)
			if (Suitmarks[ptr[i].card_suit] != "none")
				j += sprintf(buf + j, "%5s %9s %7s\n", card::getCardColor(&ptr[i]), Suitmarks[(*&ptr[i]).card_suit], card::getCardRank(&ptr[i]));
				
		char* res = new char[strlen(buf) + 1];
		strcpy(res, buf);
		delete[] buf;

		return res;
	}

	//����� ����� ��� ������������� ���������
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


			if (_kbhit())//�������� ������� ������ � �������, ������� ������� ��������� ����� �������� ������ �� �������
			{
				
				//�������� �� ������������ ������ ���������� ����
				keyMenuUpDown(&key);

				switch (key) {
				case 13:
					//������� Enter �������� � ����������(� ����. ��������) ���������� ����
					break;
				case 27:
					//Esc ��� ������
					tmp_k = -1;
					break;
				case 72:
					//UP ����� �� ���� 4...3...2...1...0...roundIndex...
					if (tmp_k < 0) {
						tmp_k = roundIndex; break;
					}
					else
						tmp_k--;
					if (tmp_k < 0) tmp_k = roundIndex;
					break;
				case 80:
					//DOWN ���� �� ���� 1...2...3...4...roundIndex...0...
					tmp_k++;
					if (tmp_k > roundIndex) {
						tmp_k = 0; break;
					}
					if (tmp_k < 0) tmp_k = 0;
					break;
				default:
					//����� ������ �� ������, ���� ����������� ����� � ����������
					break;
				}

				if (tmp_k == -1)
					//�����, ������ ���� �� �����������
					break;

				if (key == 13)
					//��������� �����
					break;
			}

		}
		setCursorVisible(true);


		if (key == 13)
		{

			//�������� �����
//			DrawCard(RGB(255, 0, 0), 400, 50, Suitmarks[(*&my_card_[tmp_k]).card_suit], my_card_[tmp_k].card_rank);

			return getCard(tmp_k);
		}
		else
			return new card{ suitmarks(0),color(0),rank(0),0 };
	}

	//����� ����� ��� ������������� ��������� �����������
	card* PlayerFool::choseCardSpecial(card** table_card,int* cntTable,char ch)
	{
		//�������� ������
		// �� ����� ����� � ����� lost_card_ � �� ���������� cntLost_card_
		// �� ����� ��������� ����� ������ enemy_card_ � �� ���������� cntEnemy_card_
//�� ����� ����� �� ����� ����� ��������� table_card � �� ���������� cntTable
//�� ����� ���� ����� my_card_ � �� ���������� cntCard_
//
//
//


		//�������� ���� ��������� � ������ �� ������� �� � �����
		checkEnemyCard();

		//************************************
		//******
		//************************************
		//����� ������ ����� ����� ��� �� ����������� � ����
		//������ ����
		Deck newDeck(EASY_DECK); 
		//����� ��� �� ������������ � ����
		card not_play_card[36];
		int cntNotPlay_card = 0;

		//�������� � ������
		for (int i = 0; i < 36; i++)//�������� ��� ��������� ����� ������ �� ������� �� � �����
		{
			//������� ���� ����������� ����� �� ������ ������
			not_play_card[cntNotPlay_card] = newDeck.getCard(i);

			if (not_play_card[cntNotPlay_card].card_rank == rank(0))
				continue;//����� ��� �������� � ���������
			//�������� � �� ����� ������� �� ������������ ��������(�����, � ������, �� �����, ������ �������)

		//� �������� ����������
			for (int j = 0; j < cntLost_card_; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == lost_card_[j].card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == lost_card_[j].card_suit))
				{
					//����� ��� �����������!!!
					cntNotPlay_card++;
					continue;//�������� � ������ ��������� �����
				}
			//� ������� ������
			for (int j = 0; j < cntEnemy_card_; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == enemy_card_[j].card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == enemy_card_[j].card_suit))
				{
					//����� ��� �����������!!!
					cntNotPlay_card++;
					continue;//�������� � ������ ��������� �����
				}
			//� ������������ �������)
			for (int j = 0; j < cntCard_; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == my_card_[j].card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == my_card_[j].card_suit))
				{
					//����� ��� �����������!!!
					cntNotPlay_card++;
					continue;//�������� � ������ ��������� �����
				}
			//� ������� �� ������� �����(������� ���)
			for (int j = 0; j < *cntTable; j++)
				if ((not_play_card[cntNotPlay_card].card_rank == table_card[j]->card_rank)
					&& (not_play_card[cntNotPlay_card].card_suit == table_card[j]->card_suit))
				{
					//����� ��� �����������!!!
					cntNotPlay_card++;
					continue;//�������� � ������ ��������� �����
				}

			

			//����� �� ���������, ������ � ������
			newDeck.setCard(not_play_card[cntNotPlay_card],i);
		};
		//************************************
		//******
		//************************************

		//************************************
		//******
		//************************************
//����� ������ ������� ����� ���� �������� � ����
//		int tmpLost = 36 - cntLost_card_ - cntEnemy_card_ - cntCard_;// -*cntTable;//���������� �����: ������ �� ������� � �����, ��������� �������, ���� ���� � �� �����
//		//cntNotPlay_card;//����� ���� �� ���������
//		int tmpPlayer;
//		if (cntEnemy_card_ > 0)
//			tmpPlayer = 6 + cntEnemy_card_ - (*cntTable / 2);//����� ������ � ������ ������ � ������� �� �����
//		else
//			tmpPlayer = 6;//�� ����� ������� ����, �� ����� �� ����� 6
//		//�� ����� ����� ����������
//		if ((36-cntNotPlay_card) <= tmpPlayer)
//			for (int i = 0; i < cntNotPlay_card; i++)
//				cout << card::toString(&not_play_card[i]);
		//************************************
		//******
		//************************************



		//������ ����
		if (ch=='B')
			//������ ����� � �����(��� ������)
			return choseCard();

		//��������������, ����� � ����� � ���������� �����
		//���� ������ ���������� ������(���� �������)
		if (ch == 'A')
		{
			//������ ���������� ������� �� ����� � �� ��������
			int max_try_cnt = cntCard_;// 36;//�� ����� ���� � ��� ����� 36 ����
			int index = 0;
			switch (*cntTable % 2)//������ ���� ���������� ������ ������
			{
			case 0:
				//����������� �����
				// *** ��������� ��� ������������ ���� ***

				while (max_try_cnt-- > 0)
				{
					if (index >= cntCard_) index = 0;

					cout << "->"
						<< setw(5) << card::getCardColor(&my_card_[index])
						<< setw(9) << Suitmarks[(*&my_card_[index]).card_suit]
						<< setw(7) << card::getCardRank(&my_card_[index])
						//<< endl; // ���� ����� ���������� ���� ������� ����
						<< "\r";

					//
					//if (!card::checkEqualRank(table_card, *cntTable))//�������� �� ������������ ����� � ���� �� ������
					//{
					//}
					if (*cntTable <= 1)
						//������� ����� ������ � ����
						return getCard(index);
					//�������� �� ������������
					int count = 0;
					for (int j = 0; j < *cntTable; j++)
						if ((my_card_[index].card_rank) == (table_card[j]->card_rank))
							count++;
					if (count < 1)
					{	//����� �� �������!!!
						index++;//��������� ��������� �����
						continue;
					}
					//
					//������� �����
					return getCard(index);
				}
				cout << "->"
					<< "                 *** �������!!! ***                  "
					<< "\r";
				break;
			case 1:
				//����������
				// *** ��������� ��� ��������� ***

				while (max_try_cnt-- > 0)
				{
					if (index >= cntCard_) index = 0;

					cout << "->"
						<< setw(5) << card::getCardColor(&my_card_[index])
						<< setw(9) << Suitmarks[(*&my_card_[index]).card_suit]
						<< setw(7) << card::getCardRank(&my_card_[index])
						//<< endl; // ���� ����� ���������� ���� ������� ����
						<< "\r";

					//
					//if (card::checkRankOK(table_card, *cntTable - 1, *cntTable - 2, trump_card_))
					//{
					//}
					if (
						((my_card_[index].card_rank > table_card[*cntTable - 1]->card_rank)//����� ���� ������
							&& (my_card_[index].card_suit == table_card[*cntTable - 1]->card_suit))//����� ����� �����, ���� ��� ��������
						||
						((my_card_[index].card_suit == trump_card_)//����� ��������
							&& (table_card[*cntTable - 1]->card_suit != trump_card_))//���� ����� �������
						)
						//������� �����
						return getCard(index);
					else
					{
						index++;//��������� ��������� �����
						continue;
					}
					//
				}
				cout << "->"
					<< "                 *** ����!!! ***                  "
					<< "\r";
				break;
			}

			//������� ������� ����� ����� ��� ���������� �����������
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