#ifndef PCH_H /* Страж */
#define PCH_H /* единственности вхождения - начало */



#define _USE_MATH_DEFINES
#define _CRT_RAND_S
#define _CRT_SECURE_NO_WARNINGS

//отлавливаем утечку памяти с помощью библиотеки CRT
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)


#define rand1() myRand()

// объявление символической константы - кодовой страницы
#define CODE_PAGE 1251


#ifndef WINDOWS_H /* Страж */
	#define WINDOWS_H /* единственности вхождения - начало */
	#include<Windows.h>
#endif //WINDOWS_H

#ifndef CONIO_H /* Страж */
	#define CONIO_H /* единственности вхождения - начало */
	#include<conio.h>
#endif //CONIO_H

#ifndef IOSTREAM /* Страж */
	#define IOSTREAM /* единственности вхождения - начало */
	#include<iostream>
#endif //IOSTREAM

#ifndef IOMANIP /* Страж */
	#define IOMANIP /* единственности вхождения - начало */
	#include<iomanip>
#endif //IOMANIP

#ifndef STDLIB_H /* Страж */
	#define STDLIB_H /* единственности вхождения - начало */
	#include <stdlib.h>
#endif //STDLIB_H

#ifndef SSTREAM /* Страж */
	#define SSTREAM /* единственности вхождения - начало */
	#include <sstream>
#endif //SSTREAM

//#ifndef FSTREAM /* Страж */
//	#define FSTREAM /* единственности вхождения - начало */
//	#include <fstream>
//#endif //FSTREAM

#ifndef STRING /* Страж */
	#define STRING /* единственности вхождения - начало */
	#include <string>
#endif //STRING

#ifndef STRING_H /* Страж */
	#define STRING_H /* единственности вхождения - начало */
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


// для единообразия кодируем также команды _WIN32
#ifdef _WIN32
#define WINPAUSE system("pause");
#define WINCLEAR system("cls");
#endif

#endif //PCH_H
