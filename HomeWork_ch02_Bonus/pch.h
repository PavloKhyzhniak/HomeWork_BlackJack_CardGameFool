#ifndef PCH_H /* ����� */
#define PCH_H /* �������������� ��������� - ������ */



#define _USE_MATH_DEFINES
#define _CRT_RAND_S
#define _CRT_SECURE_NO_WARNINGS

//����������� ������ ������ � ������� ���������� CRT
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)


#define rand1() myRand()

// ���������� ������������� ��������� - ������� ��������
#define CODE_PAGE 1251


#ifndef WINDOWS_H /* ����� */
	#define WINDOWS_H /* �������������� ��������� - ������ */
	#include<Windows.h>
#endif //WINDOWS_H

#ifndef CONIO_H /* ����� */
	#define CONIO_H /* �������������� ��������� - ������ */
	#include<conio.h>
#endif //CONIO_H

#ifndef IOSTREAM /* ����� */
	#define IOSTREAM /* �������������� ��������� - ������ */
	#include<iostream>
#endif //IOSTREAM

#ifndef IOMANIP /* ����� */
	#define IOMANIP /* �������������� ��������� - ������ */
	#include<iomanip>
#endif //IOMANIP

#ifndef STDLIB_H /* ����� */
	#define STDLIB_H /* �������������� ��������� - ������ */
	#include <stdlib.h>
#endif //STDLIB_H

#ifndef SSTREAM /* ����� */
	#define SSTREAM /* �������������� ��������� - ������ */
	#include <sstream>
#endif //SSTREAM

//#ifndef FSTREAM /* ����� */
//	#define FSTREAM /* �������������� ��������� - ������ */
//	#include <fstream>
//#endif //FSTREAM

#ifndef STRING /* ����� */
	#define STRING /* �������������� ��������� - ������ */
	#include <string>
#endif //STRING

#ifndef STRING_H /* ����� */
	#define STRING_H /* �������������� ��������� - ������ */
	#include <string.h>
#endif //STRING_H

#define wAttributeNormal FOREGROUND_RED | FOREGROUND_INTENSITY
#define wAttributeWarning FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY
#define wAttributeError FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY
#define wAttributeSpecial FOREGROUND_GREEN 
#define wAttributeStandart FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_GREEN | FOREGROUND_INTENSITY

//using namespace std;
using std::cout;
using std::cin;
using std::is_same_v;
using std::endl;
using std::setw;
using std::setfill;
using std::setprecision;
using std::boolalpha;
using std::noboolalpha;
using std::fixed;
using std::left;
using std::right;

using std::exception;

using std::ostringstream;
using std::streambuf;


// ��� ������������ �������� ����� ������� _WIN32
#ifdef _WIN32
#define WINPAUSE system("pause");
#define WINCLEAR system("cls");
#endif

#endif //PCH_H
