
//предоставим пользователю только минимальную информацию о функциях определенных в пространстве имен App_01
//namespace App_01 {
namespace classApp {


	

}



#pragma region App_01
#include "Application.h"
extern void punkt(const wchar_t* ThemeAdd, const char* name, arguments* my_arguments, int App(arguments*) );

extern wchar_t title[150];

// тестовая процедура для тестирования функционала с использованием функции обертки
void menu_App_01(arguments* my_arguments) {

	try {//попробуем выполнить данную задачу(отлавливаем исключения)

		size_t k = 0; // переменная выбора задачи для выполнения
		k = 1; // указывает на пункт меню(подсвечивание)
		bool repeat = true; // условие выполнения цикла тестирования
		char key = 0;// ввод с клавиатуры

		const char* theme =
			"\t\t\
Выберите номер задачи из представленных ниже.                  ";

		//*********************************** - 96 - ***********************************
		MY_MENU menu1(
			"00 - Выход.                                                                    ",0);
		menu1.init(
			"01 - Задача 1. Даны два файла целых чисел одинакового размера. Создать текстовый       \n\t\
файл, содержащий эти числа, расположенные в два столбца шириной по 22 символа (в первом\n\t\
столбце содержатся числа из первого исходного файла, во втором — из второго файла).    \n\t\
Третий столбец – сумма чисел в этой строке. В начало и конец каждой строки текстового  \n\t\
файла, а также между столбцами добавить разделитель \"|\". Числа выравниваются по правому\n\t\
краю столбца.                                                                          ");
		menu1.init(
			"02 - Задача 2. Дана матрица размера M x N и целое число K (0 <= K < M). Найти сумму    \n\t\
и произведение нечетных (по значению) элементов K-й строки данной матрицы (в одной     \n\t\
функции). Матрицу хранить в двоичном файле. Сумму и произведение вернуть из функции в  \n\t\
выходных параметрах (по ссылке).                                                       ");
		menu1.init(
			"03 - Очистка временных файлов.                                                 ");

		int (*func)(arguments*) = nullptr;
		while (repeat) {

			// Установим актуальный заголовок окна
			SetConsoleTitle(title);
			myAddConsoleTitle(L" Приложение № 01 ");
			// выведем меню с подсвечиванием пунктов(активного пункта)
			key = displayMenu(theme, &menu1, &k);

			//только при нажатиии Enter выполнять выбранный пункт меню
			if (key == 13)
			{
				key = 0;//очистим значение нажатой клавиши
				//основная работа(выполнение пунктов меню)
				switch (k) {
				case 1:
				//	punkt(L" Задание № 001 ", menu1.menu[k].name, my_arguments, App_01_1::App_01_1);

					break;
				case 2:
				//	punkt(L" Задание № 002 ", menu1.menu[k].name, my_arguments, App_01_2::App_01_2);

					break;
				case 3:
				//	punkt(L" Очистка временных файлов ", menu1.menu[k].name, my_arguments, App_01::App_01_clear);

					break;
				case 4:

				case 99:
					break;
				case 0:
					punkt(L" Завершение работы. ", menu1.menu[k].name, my_arguments, [](arguments*) {return 0; });

					//выход
					repeat = false;
					break;
				default:
					//игнорирование ввода
					break;
				}


			}
			if (!repeat) continue; // выход из бесконечного цикла

		}

		//throw exception(" "); // генерирование исключения
	}
	catch (exception ex) {  // обработка исключения


		SetConsoleTextAttribute(hStdOut, wAttributeWarning);
		cout << "\n\n"
			<< "\t\t                                                       \n"
			<< "\t\t    [Ошибка(уровень выбора задачи)]                    \n"
			<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
			<< "\t\t                                                       \n"
			<< "\n\n\n\n\n\n\n\n\n\n\n\n";
		//throw; // проталкивание исключения на верх
		Sleep(1000);
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);
		//continue;
	}

}
#pragma endregion

