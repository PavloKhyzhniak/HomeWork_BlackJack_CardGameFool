

#include "pch.h"
#include "Utils.h"
#include "UtilsConsole.h"
#include "Func.h"
#include "FuncTime.h"
#include "TypeStruct.h"


// Строка s анализируется и выдает на выходе строку-путь к месту выполнения программы
void SplitTokenToFolder(char** s)
{
	char* s1 = new char[strlen(*s) + 1]{0};
	strcpy(s1, *s);

	char* token;
	char* last_token = new char[strlen(*s) + 1]{ 0 };
	const char* delim = "\\:";

	*s[0] = '\0';

	try {
		token = strtok(s1, delim);
		strcat(*s, "\\");

		while (token = strtok(0, delim)) {
			if (strstr(token, "x86")) break;
			if (strstr(token, "x64")) break;
			if (strstr(token, "Debug")) break;
			//if (strchr(token, '.')) break;
			strcat(*s,token);
			strcat(*s, "\\");
			strcpy(last_token, token);
		} // while
		strcat(*s, last_token);
		strcat(*s, "\\");
	}
	catch (exception ex)
	{
		delete[] s1;
		// обработка исключения
		SetConsoleTextAttribute(hStdOut, wAttributeWarning);
		cout << "\n\n"
			<< "\t\t                                                       \n"
			<< "\t\t    [Ошибка(уровень формирования каталога(пути))]      \n"
			<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
			<< "\t\t                                                       \n"
			<< "\n\n\n\n\n\n\n\n\n\n\n\n";
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);
	}

	delete[] last_token;
	delete[] s1;
	s1 = new char[strlen(*s) + 1]{ 0 };
	strcpy(s1, *s);
	delete[] *s;
	*s = s1;
} // SplitToketToArray

//объявим и определим глобальные строки для наших файлов по умолчанию
const char* text0 = "Temp\\text1";
const char* text1 = "Temp\\text2";
const char* text2 = "Temp\\text3";
const char* text3 = "Temp\\output";
const char* text4 = "Temp\\matrix";

//функция проверки аргументов-параметров работы программы
void CheckArguments(int argc, char* argv[], arguments* my_arguments)
{
	//создадим папку для наших временных файлов
	system("mkdir temp");

//используем конструктор для создания и параметрирования нашей структуры
//	arguments my_arguments = arguments();

	//введем временную переменную строку(будем формировать имена файлов по умолчанию используя функцию name_time)
	//проинициализируем все необходимые параметры (которые могут быть переданные из командной строки)
	char* time_str = name_time(text0, "txt");
	(*my_arguments).init(time_str);// - 0 - text1.txt
//	arguments my_arguments(time_str, strlen(time_str));// - 0 - text1.txt
	time_str = name_time(text1, "txt");
	(*my_arguments).init(time_str);// - 1 - text2.txt
	time_str = name_time(text2, "txt");
	(*my_arguments).init(time_str);// - 2 - text3.txt
	time_str = name_time(text3, "txt");
	(*my_arguments).init(time_str);// - 3 - output.txt
	time_str = name_time(text4, "bin");
	(*my_arguments).init(time_str);// - 4 - matrix.bin
	(*my_arguments).init("*");// - 5 - M
	(*my_arguments).init("*");// - 6 - N
	(*my_arguments).init("*");// - 7 - K

	//	(*my_arguments).init(argv[0], strlen(argv[0]));// - 8 - Main Programm Folder
	//подготовим путь к главной точке исполнения(путь к папке запуска программы)
	char* folder = new char[strlen(argv[0]) + 1];
	strcpy(folder, argv[0]);
	SplitTokenToFolder(&folder);
	(*my_arguments).init(folder);// - 8 - Main Programm Folder


	// ПРИМЕЧАНИЕ Указаны некоторые варианты передачи параметров для запуска нашей программы
	//по условию первой задачи ожидаем имена трех входных текстовых файлов и имя четвертого выходного файла(выходной файл может быть и не задан)
	// НАПРИМЕР : text1.txt text2.txt text3.txt (output4.txt)
	//по условию второй задачи ожидаем входной бинарный файл(matrix.bin) где заданы размерность MxN, число K и собственно все элементы заданной матрицы
	// бинарный файл может прийти вместо имени 4го выходного файла(из задачи 1) или быть заданным только целыми числами - размерностью
	// НАПРИМЕР : 3 2 (матрицу и файл создаем самостоятельно)
	// matrix.bin
	// 3 2 1
	// 12 67
	// -67 0
	// 2 -9

//неправильный параметры командной строки
//	if (argc != 2) {
//		exit(1);
//	}

	//введем указатели на строки для анализа переданных параметров
	char* tmp_s, *token;
	
	//если аргументов более одного, то необходимо произвести анализ
	if (argc > 1)
		//исходя из количества переданных параметров проведем инициализацию параметов указанных по умолчанию
		switch (argc) {

		case 8://text1.txt text2.txt text3.txt output.txt M N K
			(*my_arguments).menu[7].name = argv[7];//запись K - в каком столбце искать
			(*my_arguments).menu[7].length_name = sizeof(argv[7]);

			(*my_arguments).menu[6].name = argv[6];// запись M - сколько элементов в строке
			(*my_arguments).menu[6].length_name = sizeof(argv[6]);

			(*my_arguments).menu[5].name = argv[5];//запись - N - количество строк
			(*my_arguments).menu[5].length_name = sizeof(argv[5]);

			(*my_arguments).menu[3].name = argv[4];//имя выходного файла - файла результата
			(*my_arguments).menu[3].length_name = sizeof(argv[4]);

			goto LabelCase_04;//переход по метке заполнения остальный параметров

		case 7://text1.txt text2.txt text3.txt M N K

			(*my_arguments).menu[7].name = argv[6];//запись K - в каком столбце искать
			(*my_arguments).menu[7].length_name = sizeof(argv[6]);

			(*my_arguments).menu[6].name = argv[5];// запись M - сколько элементов в строке
			(*my_arguments).menu[6].length_name = sizeof(argv[5]);

			(*my_arguments).menu[5].name = argv[4];//запись - N - количество строк
			(*my_arguments).menu[5].length_name = sizeof(argv[4]);

			goto LabelCase_04;

		case 6://text1.txt text2.txt text3.txt output.txt matrix.bin OR //text1.txt text2.txt text3.txt M N

			if (atoi(argv[4]))
			{
				//Var2
				//text1.txt text2.txt text3.txt M N
				(*my_arguments).menu[6].name = argv[5];// запись M - сколько элементов в строке
				(*my_arguments).menu[6].length_name = sizeof(argv[5]);

				(*my_arguments).menu[5].name = argv[4];//запись - N - количество строк
				(*my_arguments).menu[5].length_name = sizeof(argv[4]);
			}
			else
			{
				//Var1
				//text1.txt text2.txt text3.txt output.txt matrix.bin
				(*my_arguments).menu[4].name = argv[5];//имя бинарного файла - матрица под обработку
				(*my_arguments).menu[4].length_name = sizeof(argv[5]);

				(*my_arguments).menu[3].name = argv[4];//имя выходного файла - файла результата
				(*my_arguments).menu[3].length_name = sizeof(argv[4]);
			}

			goto LabelCase_04;

		case 5://text1.txt text2.txt text3.txt output.txt OR //text1.txt text2.txt text3.txt matrix.bin
			
			tmp_s = new char[strlen(argv[4]) + 1]{ 0 };
			strcpy(tmp_s, argv[4]);
			token = strtok(tmp_s, ".");
			token = strtok(0, ".");

			if (strstr(token,"bin"))
			{
				//text1.txt text2.txt text3.txt matrix.bin
				(*my_arguments).menu[4].name = argv[4];//имя бинарного файла - матрица под обработку
				(*my_arguments).menu[4].length_name = sizeof(argv[4]);
			} 
			else
			{
				//text1.txt text2.txt text3.txt output.txt
				(*my_arguments).menu[3].name = argv[4];//имя выходного файла - файла результата
				(*my_arguments).menu[3].length_name = sizeof(argv[4]);
			}
			
		case 4://text1.txt text2.txt text3.txt 
		LabelCase_04:
			(*my_arguments).menu[2].name = argv[3];//имя 3го текстового файла
			(*my_arguments).menu[2].length_name = sizeof(argv[3]);

		case 3://text1.txt text2.txt 
			(*my_arguments).menu[1].name = argv[2];//имя 2го текстового файла
			(*my_arguments).menu[1].length_name = sizeof(argv[2]);

		case 2://text1.txt OR //matrix.bin
			tmp_s = new char[strlen(argv[1]) + 1]{ 0 };
			strcpy(tmp_s, argv[1]);
			token = strtok(tmp_s, ".");
			token = strtok(0, ".");

			if (strstr(token, "bin"))
			{
				//matrix.bin
				(*my_arguments).menu[4].name = argv[1];//имя бинарного файла - матрица под обработку
				(*my_arguments).menu[4].length_name = sizeof(argv[1]);
			} 
			else
			{
				//text1.txt
				(*my_arguments).menu[0].name = argv[1];//имя 1го текстового файла
				(*my_arguments).menu[0].length_name = sizeof(argv[1]);
			}
			
		case 1: 
		defaulf:
			break;
		}
}

// процедура выводит линию заданной длинны и заданным символом
void Line(size_t x, char y) {
	cout << setfill(y) << setw(x) << " " << setfill(' ') << endl ;
}


//**************************
//организуем пунты меню с подсветкой
char displayMenu(const char* theme, MY_MENU* menu, size_t* const k) {

	size_t N = menu->count;

	WINCLEAR;
	setCursorPosition(0, 0);

	ostringstream oss;
	oss.str("");

	Line(96, '*');

	SetConsoleTextAttribute(hStdOut, wAttributeStandart);
	cout << endl << theme << endl;
	SetConsoleTextAttribute(hStdOut, wAttributeNormal);

	//(сохраним наш текущий буфер стандартного потока вывода)
	streambuf* oldCoutStreamBuf = cout.rdbuf();

	//перенаправим стандартный буфер вывода на наш созданный буфер
	cout.rdbuf(oss.rdbuf());



	Line(96, '*');

	cout << setw(80) << left << "\n\t\tВыберите задачу: ";

	for (size_t i = 1; i < N; i++)
	{
		if (*k == static_cast<size_t>(((*menu).menu[i].name[0] - 48) * 10 + ((*menu).menu[i].name[1] - 48)))
		{
			//восстановление буфера стандартного потока вывода
			cout.rdbuf(oldCoutStreamBuf);
			cout << oss.str().c_str();
			oss.str("");

			SetConsoleTextAttribute(hStdOut, wAttributeStandart);

			cout << "\n\t" << setw(80) << left << (*menu).menu[i].name;

			//перенаправим стандартный буфер вывода на наш созданный буфер
			cout.rdbuf(oss.rdbuf());
		}
		else
			cout << "\n\t" << setw(80) << left << (*menu).menu[i].name;
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);
	}

	cout << endl;
	if (*k == static_cast<size_t>((*menu).menu[0].name[0] - 48))
	{

		//восстановление буфера стандартного потока вывода
		cout.rdbuf(oldCoutStreamBuf);
		cout << oss.str().c_str();
		oss.str("");

		SetConsoleTextAttribute(hStdOut, wAttributeStandart);

		cout << "\n\t" << setw(80) << left << (*menu).menu[0].name;

		//перенаправим стандартный буфер вывода на наш созданный буфер
		cout.rdbuf(oss.rdbuf());
	}
	else
		cout << "\n\t" << setw(80) << left << (*menu).menu[0].name;
	SetConsoleTextAttribute(hStdOut, wAttributeNormal);


	cout << endl;
	cout << setw(80) << left << "\n\t\tДля управления по меню используйте кнопки ВВЕРХ, ВНИЗ, Enter.";
	cout << endl;
	cout << setw(80) << left << "\n\tPS. Esc - выход. Цифры 00..99 быстрый переход к соответствующему пункту меню.";
	cout << right << endl;
	cout << endl;

	Line(96, '*');

	//восстановление буфера стандартного потока вывода
	cout.rdbuf(oldCoutStreamBuf);
	cout << oss.str().c_str();
	oss.str("");

	//только по сигналу от клавиатуры будем опрашивать нажатую кнопку
	double tmp = 0;
	int cycle_repeat = 0;//введем переменную опроса, дабы не все время перерисовывать "красоту"
	
	//ожидание действий пользователя
	while (TRUE)//цикл WHILE
	{
		if (cycle_repeat++ > 100)//каждые 100 циклов будем перерисовывать нашу "красоту"
		{
			//обнулим счетчик циклов
			cycle_repeat = 0;
			//произведем стирание ранее выведенных точек
			//Draw(RGB(0, 0, 0), 0., 1024., 1., 500, [](double x, double bias) {return(sin(M_PI * x / 25. + bias)); }, tmp);
			DrawV(RGB(0, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, tmp);
			DrawV(RGB(0, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, 2 + tmp);
			DrawV(RGB(0, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, -2 + tmp);
			//внесем небольшое изминение - эффект движения
			tmp += 0.1;
			//произведем выведение новых точек
			//Draw(RGB(0, 255, 0), 0., 1024., 1., 500, [](double x, double bias) {return(sin(M_PI * x / 25. + bias)); }, tmp);
			DrawV(RGB(0, 0, 255), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, tmp);
			DrawV(RGB(0, 255, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, 2 + tmp);
			DrawV(RGB(255, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, -2 + tmp);
		}
		if (_kbhit())//Проверка нажатия клавиш в консоли, которую следует выполнять перед попыткой чтения из консоли
		{
			//произведем стирание ранее выведенных точек нашей "красоты"
			DrawV(RGB(0, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, tmp);
			DrawV(RGB(0, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, 2 + tmp);
			DrawV(RGB(0, 0, 0), 0., 800., 1., 900, [](double x, double bias) {return(sin(M_PI * x / 50. + bias)); }, -2 + tmp);
			
			//опрос нажатой клавиши
			return setMenu(k, (*menu).count - 1);
		}
	}//цикл WHILE окончен
//	return setMenu(k,(*menu).count-1);
	return 0;
}
//**************************

//организуем пунты меню с подсветкой
void displayMenu(const char theme[1000],const size_t N, const char menu[][40],const size_t k) {

	WINCLEAR;

	Line(100, '*');

	SetConsoleTextAttribute(hStdOut, wAttributeStandart);
	cout << theme << endl;
	SetConsoleTextAttribute(hStdOut, wAttributeNormal);

	Line(100, '*');

	cout << setw(80) << left << "\n\t\tВыберите задачу: ";

	size_t tmp_N = N / 2;
	if ((N & 0x01) == 0) tmp_N--;

	for (size_t i = 1,j = tmp_N + 1; i <= tmp_N; i++,j++)
	{
		if (k == static_cast<size_t>((menu[i][0] - 48) * 10 + (menu[i][1] - 48)))
			SetConsoleTextAttribute(hStdOut, wAttributeStandart);
		cout << "\n\t" << setw(40) << left << menu[i];
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);

		if (k == static_cast<size_t>((menu[j][0] - 48) * 10 + (menu[j][1] - 48)))
			SetConsoleTextAttribute(hStdOut, wAttributeStandart);
		cout << setw(40) << left << menu[j];
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);
	}

	if ((N & 0x01) == 0)
	{
		cout << "\n\t" << setw(40) << " ";
		if (k == static_cast<size_t>((menu[N-1][0] - 48) * 10 + (menu[N-1][1] - 48)))
			SetConsoleTextAttribute(hStdOut, wAttributeStandart);
		cout << setw(40) << left << menu[N-1];
		SetConsoleTextAttribute(hStdOut, wAttributeNormal);
	}


	cout << endl;
	if (k == static_cast<size_t>(menu[0][0] - 48)) SetConsoleTextAttribute(hStdOut, wAttributeStandart);
	cout << "\n\t" << setw(80) << left << menu[0];
	SetConsoleTextAttribute(hStdOut, wAttributeNormal);


	cout << endl;
	cout << setw(80) << left << "\n\t\tДля управления по меню используйте кнопки ВВЕРХ, ВНИЗ, Enter.";
	cout << endl;
	cout << setw(80) << left << "\n\tPS. Esc - выход. Цифры 00..99 быстрый переход к соответствующему пункту меню.";
	cout << right << endl;
	cout << endl;

	Line(100, '*');
}

//функция опроса кнопок управления меню
char setMenu(size_t* k, const size_t roundIndex) {
	char key;
	//запросим от пользователя кнопку управления меню
	keyMenu(&key);

	//введем локальную переменную, для исключения множественного приминения разыменывания указателя
	size_t tmp_k = *k;

	//преобразуем полученное значение в указатель на пункт меню
	int tmp_key = 0; //смещение по десяткам
	switch (key) {
	case 13:
		//нажатие Enter приводит к выполнению(в след. итерации) выбранного меню
		break;
	case 27:
		//Esc для выхода
		tmp_k = 0;
		break;
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		//смещение по десяткам
		tmp_key = (key - 48) * 10;
		//запросим от пользователя кнопку управления меню
		keyMenuNumber(&key);
		//цифровые кнопки для мгновенного перемещения по меню
		tmp_k = tmp_key + key - 48;
		break;
	case 72:
		//UP вверх по меню
		if (tmp_k <= 0) {
			tmp_k = roundIndex; break;
		}
		else
			tmp_k--;
		if (tmp_k <= 0) tmp_k = 1;
		break;
	case 80:
		//DOWN вниз по меню
	//	if (tmp_k == roundIndex/2) {
	//		tmp_k = 0; break;
	//	}
		tmp_k++;
		if (tmp_k > roundIndex) {
			tmp_k = 0; break;
		}
		if (tmp_k <= 1) tmp_k = 0;
		break;
		//case 75:
		//	//LEFT влево по меню
		//	if (((roundIndex & 0x01) != 0) && (tmp_k == roundIndex))
		//		tmp_k = roundIndex / 2;
		//	else
		//		if (tmp_k > roundIndex / 2)
		//		{
		//			tmp_k -= roundIndex / 2;
		//		}
		//	break;
		//case 77:
		//	//RIGHT вправо по меню
		//	if (tmp_k <= roundIndex / 2)
		//		tmp_k += roundIndex / 2;
		//	break;
	default:
		//иначе ничего не делать, ждем правильного ввода с клавиатуры
		break;
	}

	*k = tmp_k;
	return key;
}

//функция опроса кнопок управления меню
void setMenuC(char* key, size_t* k,const size_t roundIndex) {
	//запросим от пользователя кнопку управления меню
	keyMenu(key);

	//введем локальную переменную, для исключения множественного приминения разыменывания указателя
	size_t tmp_k = *k;

	//преобразуем полученное значение в указатель на пункт меню
	int tmp_key = 0; //смещение по десяткам
	switch (*key) {
	case 13:
		//нажатие Enter приводит к выполнению(в след. итерации) выбранного меню
		break;
	case 27:
		//Esc для выхода
		tmp_k = 0;
		break;
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		//смещение по десяткам
		tmp_key = (*key - 48) * 10;
		//запросим от пользователя кнопку управления меню
		keyMenuNumber(key);
		//цифровые кнопки для мгновенного перемещения по меню
		tmp_k = tmp_key + *key - 48;
		break;
	case 72:
		//UP вверх по меню
		if (tmp_k <= 0) {
			tmp_k = roundIndex; break;
		}
		else
			tmp_k--;
		if (tmp_k <= 0) tmp_k = 1;
		break;
	case 80:
		//DOWN вниз по меню
		if (tmp_k == roundIndex / 2) {
			tmp_k = 0; break;
		}
		tmp_k++;
		if (tmp_k > roundIndex) {
			tmp_k = 0; break;
		}
		if (tmp_k <= 1) tmp_k = 0;
		break;
	case 75:
		//LEFT влево по меню
		if (((roundIndex & 0x01) != 0) && (tmp_k == roundIndex))
			tmp_k = roundIndex / 2;
		else
			if (tmp_k > roundIndex / 2)
			{
				tmp_k -= roundIndex / 2;
			}
		break;
	case 77:
		//RIGHT вправо по меню
		if (tmp_k <= roundIndex / 2)
			tmp_k += roundIndex / 2;
		break;
	default:
		//иначе ничего не делать, ждем правильного ввода с клавиатуры
		break;
	}

	*k = tmp_k;
}

// функция реакции на нажатую кнопку
bool inputKey(char* keyChar,
	size_t size,
	const char greeting[])
{
	char* ch = nullptr;
	if (keyChar == nullptr) {
		char tmp[] = { 'Y','y','Н','н' };
		size = sizeof(tmp);
		ch = static_cast<char*>(tmp);
	}
	else
		ch = static_cast<char*>(keyChar);

	cout << "\n\t" << greeting;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	for (size_t i = 0; i < size; i++)
		if (ch[i] == key) {
			if (keyChar != nullptr)
				*keyChar = key;
			return true;
		}
	return false;
}

// функция реакции на нажатую кнопку
bool inputInvisibleKey(char* keyChar, size_t size)
{
	char* ch = nullptr;
	if (keyChar == nullptr) {
		char tmp[] = { 'Y','y','Н','н' };
		size = sizeof(tmp);
		ch = static_cast<char*>(tmp);
	}
	else
		ch = (keyChar);

	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	for (size_t i = 0; i < size; i++)
		if (ch[i] == key) {
			if (keyChar != nullptr)
				*keyChar = key;
			return true;
		}
	return false;
}

// процедура организации ввода чисел и спец.символов 'Esc' и 'Enter'
// с возвратом вводимого символа
bool keyMenuUpDown(char* key) {
	// Enter, Esc, Up, Down
	char myEsc[] = { 0, 13,27,72,80};//первым обязательно неиспользуемое значение
	bool result = inputInvisibleKey(myEsc, sizeof(myEsc));
	*key = myEsc[0];//через первый элемент возвращаем нажатый код кнопки
	return result;
}

// процедура организации ввода чисел и спец.символов 'Esc' и 'Enter'
// с возвратом вводимого символа
bool keyMenu(char* key) {
	// Enter, Esc, Up, Down,Left, Right, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	char myEsc[] = {0, 13,27,72,80,75,77,48,49,50,51,52,53,54,55,56,57 };//первым обязательно неиспользуемое значение
	bool result = inputInvisibleKey(myEsc, sizeof(myEsc));
	*key = myEsc[0];//через первый элемент возвращаем нажатый код кнопки
	return result;
}

// процедура организации ввода чисел
// с возвратом вводимого символа
bool keyMenuNumber(char* key) {
	// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	char myEsc[] = { 0, 48,49,50,51,52,53,54,55,56,57 };//первым обязательно неиспользуемое значение
	bool result = inputInvisibleKey(myEsc, sizeof(myEsc));
	*key = myEsc[0];//через первый элемент возвращаем нажатый код кнопки
	return result;
}

// процедура организации повтора по выбору Y/(any key)
bool keyRepeat() {
	#pragma warning(suppress:4309)
	#pragma warning(suppress:4838)
	char myEsc[] = { 205,237,'Y','y' };
	#pragma warning(suppress:4804)
	return ~inputKey(myEsc, sizeof(myEsc), "\n\tДля повтора нажмите 'Y' или 'y'...");
}

// процедура организации выхода по нажатию Esc
bool keyExit() {
	char myEsc[] = { 27 };
	return inputKey(myEsc, sizeof(myEsc), "\n\tДля выхода нажмите 'Esc' ... ");
}

// процедура организации выхода по нажатию Enter
bool keyEnter() {
	char myEsc[] = { 13 };
	return inputKey(myEsc, sizeof(myEsc), "\n\tДля продолжения нажмите 'Enter' ... ");
}

//процедура организации "Нажмите любую клавишу..."
bool anyKey() {
	cout << endl << "Для продолжения нажмите любую клавишу..." << endl;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();
	return TRUE;
}

//процедура организации "Нажмите любую клавишу..."
bool anyKey(short x, short y) {
	cout << endl << "Для продолжения нажмите любую клавишу..." << endl;
	
	setCursorVisible(false); 
	setCursorPosition(x, y);
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();
	
	setCursorVisible(true); 
	return TRUE;
}


// процедура интерактивной паузы
void Pause(unsigned short timePause) {
	cout << "\n\tПауза " << timePause << " секунд." << "      \r";
	Sleep(1000);
	for (int i = timePause; i > 0; i--, Sleep(1000), cout << "\tОсталось ..." << i << "      \r");
	cout << "                                          \n";
}

//введем генератор случайных чисел, вместо rand()
__declspec(selectany) unsigned int number;
unsigned int myRand() {
	errno_t err = rand_s(&number);
	if (err != 0)
		throw exception ("The rand_s function failed!\n");
	return number;
}
