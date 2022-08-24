#pragma once

#include "Complex.h"


#include "pch.h"
#include "Utils.h"
#include "UtilsConsole.h"
#include "Func.h"

extern wchar_t title[150];

namespace classApp {


#pragma region Complex
	//STATIC data
#pragma region STATIC_data

	//инициализируем статическую переменную-счетчик созданных объектов
	int Complex::count_ = 0;

#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

	std::ostream& operator<<(std::ostream& os, const Complex& object)
	{
		os << "\nZ = " << setw(10) << object.ReZ_
			<< " + " << setw(10) << object.ImZ_
			<< "i;\n";

		return os;
	}

	std::istream& operator>>(std::istream& is, Complex& object)
	{
		double tmpDouble;

		setValue<double>(is, &tmpDouble, "ReZ = ", [](const double* const k) {return(true); });
		object.setReZ(tmpDouble);

		setValue<double>(is, &tmpDouble, "ImZ = ", [](const double* const k) {return(true); });
		object.setImZ(tmpDouble);

		return is;
	}

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor
	Complex::Complex()
	{
		setReZ(0.);
		setImZ(0.);

#ifdef _DEBUG
		cout << endl << "Конструктор по умолчанию(без параметров). Класс Complex.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	Complex::Complex(double Re, double Im)
	{

		setReZ(Re);
		setImZ(Im);

#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами. Класс Complex.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	Complex::Complex(const Complex& object)
	{
		this->ReZ_ = object.ReZ_;
		this->ImZ_ = object.ImZ_;

#ifdef _DEBUG
		cout << endl << "Конструктор копирования. Класс Complex.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//destructor
	Complex::~Complex() {
				
#ifdef _DEBUG
		cout << endl << "Деструктор. Класс Complex.\n";
		cout << "Всего существует " << --count_ << " объектов\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS

inline int Complex::setReZ(double number) {
		this->ReZ_ = number;
		return 0;
	}

inline int Complex::setImZ(double number) {
		this->ImZ_ = number;
		return 0;
	}

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	double Complex::getReZ() const {
		return this->ReZ_;
	}

	double Complex::getImZ() const {
		return this->ImZ_;
	}

#pragma endregion

	//METHODS
#pragma region METHODS

	char* Complex::toString() const
	{
		char* buf = new char[1024];
		if(ImZ_>=0)
			sprintf(buf, "%5.2lf + %5.2lfi ", ReZ_, ImZ_);
		else
			sprintf(buf, "%5.2lf - %5.2lfi ", ReZ_, abs(ImZ_));

		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

#pragma endregion

#pragma region OPERATORS
	Complex& Complex::operator=(const Complex& object)
	{
		if (&object == this) return *this;

		this->ReZ_ = object.ReZ_;
		this->ImZ_ = object.ImZ_;

#ifdef _DEBUG
		cout << endl << "Оператор присваивания. Класс Complex.\n";
		cout << "Всего существует " << count_ << " объектов\n";
#endif
		return *this;
	} // operator=

	Complex& Complex::operator+(const Complex& object)
	{
		this->ReZ_ += object.ReZ_;
		this->ImZ_ += object.ImZ_;

		return *this;
	}

	Complex& Complex::operator-(const Complex& object)
	{
		this->ReZ_ -= object.ReZ_;
		this->ImZ_ -= object.ImZ_;

		return *this;
	}
	
	Complex& Complex::operator*(const Complex& object)
	{
		double tmp_ReZ = (this->ReZ_ * object.ReZ_) - (this->ImZ_ * object.ImZ_);
		double tmp_ImZ = (this->ReZ_ * object.ImZ_) + (this->ImZ_ * object.ReZ_);

		this->ReZ_ = tmp_ReZ;
		this->ImZ_ = tmp_ImZ;

		return *this;
	}

	Complex& Complex::operator/(const Complex& object)
	{
		double tmp_ReZ = ((this->ReZ_ * object.ReZ_) + (this->ImZ_ * object.ImZ_)) / ((object.ReZ_ * object.ReZ_) + (object.ImZ_ * object.ImZ_));
		double tmp_ImZ = ((this->ImZ_ * object.ReZ_) - (this->ReZ_ * object.ImZ_)) / ((object.ReZ_ * object.ReZ_) + (object.ImZ_ * object.ImZ_));

		this->ReZ_ = tmp_ReZ;
		this->ImZ_ = tmp_ImZ;

		return *this;
	}

	Complex& Complex::operator^(const int pow)
	{
		Complex tmp = *this;

		for (int i = 1; i < pow; i++)
			tmp = tmp * *this;

		*this = tmp;
		return *this;
	}


#pragma endregion

#pragma endregion


	void TestClassComplex() {

		cls();

		// Установим актуальный заголовок окна
		SetConsoleTitle(title);
		// Установим актуальный заголовок окна
		myAddConsoleTitle(L" Тестирование Класса Complex ");

		coutColor("\nСоздадим три отдельных объекта\n", wAttributeSpecial);
		
		Complex c1;
		Complex c2(2560, 1080);
		Complex c3 = c2;

		coutColor("\nПокажем наши объекты.\n", wAttributeSpecial);
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;
		cout << c3.toString() << endl;

		//************************
		coutColor("\nПоработаем с объектом №3\n", wAttributeSpecial);
		
		c3.setReZ(4);
		cout << "\nУкажем новую действительную часть: \n" << c3.toString() << endl;
		c3.setImZ(-3);
		cout << "\nУкажем новую мнимую часть: \n" << c3.toString() << endl;


		coutColor("\nЗапросим все поля объекта с использованием геттеров\n", wAttributeSpecial);
		//get
		cout << "\nПосмотрим его действительную часть: " << c3.getReZ();
		cout << "\nПосмотрим его мнимую часть: " << c3.getImZ();

		anyKey();

		//*************************

		coutColor("\nПротестируем перегрузку операторов\n", wAttributeSpecial);

		cout << "\nСложение с1 + с2: ";
		c1.operator+(c2);
		cout << c1.toString() << endl;

		cout << "\nВычитание с1 - с3: ";
		c1.operator-(c3);
		cout << c1.toString() << endl;

		cout << "\nУмножение с1 * с2: ";
		c1=c1*c2;
		cout << c1.toString() << endl;

		cout << "\nДеление с1 / с2: ";
		c1=c1/c3;
		cout << c1.toString() << endl;

		cout << "\nВозведение в степень с3^3 : ";
		c3.operator^(3);
		cout << c3.toString() << endl;

		coutColor("\nПроверим содержимое наших объектов\n", wAttributeSpecial);
		//выведем информацию о существующих объектов в массиве
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;
		cout << c3.toString() << endl;

		anyKey();//*************************
		
		coutColor("\nПротестируем перегрузку операторов ввода\\вывода\n", wAttributeSpecial);
		cout << "Выведем информацию об объекте № 3 и введем информацию в объект № 2.\n";
		cout << c3 << endl;
		cin >> c2;

		coutColor("\nПроверим содержимое наших объектов\n", wAttributeSpecial);
		//выведем информацию о существующих объектов в массиве
		cout << c1.toString() << endl;
		cout << c2.toString() << endl;
		cout << c3.toString() << endl;

		anyKey();

		cls();

	}
#pragma endregion

}