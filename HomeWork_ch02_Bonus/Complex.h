
#ifndef COMPLEX_H /* Страж */
#define COMPLEX_H /* единственности вхождения - начало */


#include "pch.h"
#include "Utils.h"


namespace classApp {

	//класс 
	class Complex
	{
	private:
		//статическая переменная, контроль созданных объектов в программе
		static int count_;

		//z=x + i*y;
		double ReZ_,ImZ_;

		//перегрузка через дружественные функции ввода >> и вывода <<
		friend std::ostream& operator<<(std::ostream& os, const Complex& object);
		friend std::istream& operator>>(std::istream& is, Complex& object);


	public:
		//constructor
//конструктор по умолчанию
		Complex();
		//конмтруктор с параметрами инициализации объекта
		Complex(double ReZ, double ImZ);
		//конструктор копирующий
		Complex(const Complex& object);
		//destructor
		//деструктор
		~Complex();

		//set
		//сеттеры установки полей объекта
		int setReZ(double number);
		int setImZ(double number);

		//get
		//геттеры для доступа к полям объекта
		double getReZ() const;
		double getImZ() const;

		//methods
		// служебный метод - приведение полей объекта в строковое представление
		char* toString() const;

		//operators

		// оператор присваивания копированием
		Complex& operator=(const Complex& object);

		// оператор присваивания перемещением
		Complex& operator=(Complex&& object) = default;

		Complex& operator+(const Complex& object);
		Complex& operator-(const Complex& object);
		Complex& operator*(const Complex& object);
		Complex& operator/(const Complex& object);
		Complex& operator^(const int pow);
	};

	void TestClassComplex();

}// classApp


#endif //COMPLEX_H

