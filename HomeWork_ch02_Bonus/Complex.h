
#ifndef COMPLEX_H /* ����� */
#define COMPLEX_H /* �������������� ��������� - ������ */


#include "pch.h"
#include "Utils.h"


namespace classApp {

	//����� 
	class Complex
	{
	private:
		//����������� ����������, �������� ��������� �������� � ���������
		static int count_;

		//z=x + i*y;
		double ReZ_,ImZ_;

		//���������� ����� ������������� ������� ����� >> � ������ <<
		friend std::ostream& operator<<(std::ostream& os, const Complex& object);
		friend std::istream& operator>>(std::istream& is, Complex& object);


	public:
		//constructor
//����������� �� ���������
		Complex();
		//����������� � ����������� ������������� �������
		Complex(double ReZ, double ImZ);
		//����������� ����������
		Complex(const Complex& object);
		//destructor
		//����������
		~Complex();

		//set
		//������� ��������� ����� �������
		int setReZ(double number);
		int setImZ(double number);

		//get
		//������� ��� ������� � ����� �������
		double getReZ() const;
		double getImZ() const;

		//methods
		// ��������� ����� - ���������� ����� ������� � ��������� �������������
		char* toString() const;

		//operators

		// �������� ������������ ������������
		Complex& operator=(const Complex& object);

		// �������� ������������ ������������
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

