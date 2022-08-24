
#include "pch.h"
#include "Utils.h"
#include "UtilsConsole.h"
#include "Func.h"
#include "FuncTime.h"

#include "Application.h"
#include "Televisor.h"
#include "Complex.h"
#include "Blackjack.h"


HANDLE hStdOut;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
WORD wOldColorAttrs;
RECT r;
HWND console;

wchar_t title[150] = L"КА \"ШАГ\" г.Донецк - Домашняя работа (часть 02) № 01 - от 23.11.2019год.";


void test_function(const char* name, ...) {
	const char** p = &name;
	while (*p != 0)
	{
		cout << *p;
		p++;
	}
}

void test_function2(int n, ...) {
	va_list p;
	va_start(p, n);
	while (n-- != 0)
	{
		int tmp = va_arg(p, int);
		cout << tmp << endl;
	}
	va_end(p);
}


int main(int argc, char *argv[])
{
	//введем переменную для формирования сообщений
	char* text = new char[2000];

	init();	

	// Установим актуальный заголовок окна
	SetConsoleTitle(title);
	//**************************************************************************
	
	try {
		// КОМПЛЕКСНЫЕ ЧИСЛА
//		classApp::TestClassComplex();

//		anyKey();

		// ИГРА БЛЭКДЖЕК
//		classApp::TestClassCards();
//		classApp::TestClassShoes();
		classApp::Blackjack::Game();

		// ИГРА В ДУРАЧКА
		classApp::Card_Game_Fooler::Game();
			   
		anyKey();

		// ФУНКЦИЯ ДЛЯ ФОРМАТИРОВАННОГО ВЫВОДА
//		test_function("Hello World!!!\n","\t\tHi, Everyone!!!\n","\tDas\n\t\tist\n\t\t\tWelt!!!\n",0);
//		test_function2(5, 90, 80, 70, 60, 50);

//		anyKey();


//		classApp::Exercises();
		//тестирование всех функций класса NoNameClass
//		classApp::TestClassTelevisor();
//		classApp::TestClassArrayTelevisor();







		// НЕИСПОЛЬЗУЕТЬСЯ
//		//ДОМАШНЯЯ РАБОТА
//		//написаны функции, сделано меню
//		menu();



//		anyKey();

	}
	catch (exception ex) {  // обработка исключения

		//переместим курсор в заданную позицию
		setCursorPosition(0, 0);
		//произведем очистку области под новую информацию
		placeClear(0, 0, 1, 123*80);

		SetConsoleTextAttribute(hStdOut, wAttributeWarning);
		cout << "\n\n"
			<< "\t\t                                                       \n"
			<< "\t\t    [Ошибка(уровень приложения)]                       \n"
			<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
			<< "\t\t                                                       \n"
			<< "\n\n\n\n\n\n\n\n\n\n\n\n";
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);
		Pause();
	}
	//**************************************************************************

	//переместим курсор в заданную позицию
	setCursorPosition(0, 0);
	//произведем очистку области под новую информацию
	placeClear(0, 0, 1, 123*80);
	
	SetConsoleTextAttribute(hStdOut, wAttributeSpecial);
	cout << "\n\n"
		<< "\t                                                       \n"
		<< "\t    [К сведению]                                       \n"
		<< "\t    Конец работы приложения                            \n"
		<< "\t                                                       \n"
		<< "\n\n\n\n\n\n\n\n\n\n\n\n\n";
	SetConsoleTextAttribute(hStdOut, wAttributeNormal);
	Pause(1);
	
	// Restore the original text colors. 
	SetConsoleTextAttribute(hStdOut, wOldColorAttrs);

	WINCLEAR;

	//удаляем динамическую строку
	delete[] text;

	return 0;
}






