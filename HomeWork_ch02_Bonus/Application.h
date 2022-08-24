#ifndef APPLICATION_H /* ����� */
#define APPLICATION_H /* �������������� ��������� - ������ */

#include"Utils.h"
#include"TypeStruct.h"

#include"App_All.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;

extern wchar_t title[150];


// �������� ������� �������
void forever(void (*func)(void));

void punkt(const wchar_t* ThemeAdd, const char* name, arguments* my_arguments, int App(arguments*) = [](arguments*) {return 0; });

//
//	punkt(L" ������� � 001 ", menu1.menu[k].name, my_arguments, App_13_1::App_13_1);
//
//
void punkt(
	const wchar_t* ThemeAdd
	, const char* name
	, arguments* my_arguments
	, int App(arguments*)
)
{
	// ��������� ���������� ��������� ����
	myAddConsoleTitle(ThemeAdd);

	//���������� ������ � �������� �������
	setCursorPosition(0, 3);
	//���������� �������� ��������� ����� ��� ����� ����������� ����� ������
	placeClear(0, 0, 30, 105);
	//������ ������ ��� ������� ������ ��������
	cout << "\n\t" << name << endl << endl;
	//������� ������ �� ������� *************************
	Line(96, '*');

	//������� ������� � ��������� �� ���� ����������� ����������
	App(my_arguments);
}


// ��������� ������� ��� ����������� �������
void forever(void (*func)(void)) {
	while (true) {
		func();
		if (keyEnter()) break;
	}
}


#endif //APPLICATION_H











