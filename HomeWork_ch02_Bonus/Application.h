#ifndef APPLICATION_H /* Страж */
#define APPLICATION_H /* единственности вхождения - начало */

#include"Utils.h"
#include"TypeStruct.h"

#include"App_All.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;

extern wchar_t title[150];


// прототип функции обертки
void forever(void (*func)(void));

void punkt(const wchar_t* ThemeAdd, const char* name, arguments* my_arguments, int App(arguments*) = [](arguments*) {return 0; });

//
//	punkt(L" Задание № 001 ", menu1.menu[k].name, my_arguments, App_13_1::App_13_1);
//
//
void punkt(
	const wchar_t* ThemeAdd
	, const char* name
	, arguments* my_arguments
	, int App(arguments*)
)
{
	// Установим актуальный заголовок окна
	myAddConsoleTitle(ThemeAdd);

	//переместим курсор в заданную позицию
	setCursorPosition(0, 3);
	//произведем очиистку заданного места под вывод результатов нашей работы
	placeClear(0, 0, 30, 105);
	//укажем задачу над которой сейчас работаем
	cout << "\n\t" << name << endl << endl;
	//отделим задачу от решения *************************
	Line(96, '*');

	//вызовем функцию с передачей ей всех необходимых параметров
	App(my_arguments);
}


// процедура обертка для выполняемой функции
void forever(void (*func)(void)) {
	while (true) {
		func();
		if (keyEnter()) break;
	}
}


#endif //APPLICATION_H











