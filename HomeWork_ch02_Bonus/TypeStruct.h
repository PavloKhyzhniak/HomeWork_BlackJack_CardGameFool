#ifndef TYPESTRUCT_H /* Страж */
#define TYPESTRUCT_H /* единственности вхождения - начало */

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;

//объявим новый тип под пункт меню
struct MENU_NAME {
	const char* name;
	size_t length_name;
};

//объявим новый тип под меню
struct MY_MENU {
	MENU_NAME* menu = nullptr;
	size_t count = 0;

	//конструктор без параметров
	MY_MENU(void) {
		menu = nullptr;
		count = 0;
	}
	
	// MY_MENU menu1("00 - ","01 - ","02 - ", 0);
		//конструктор с переменным числом параметров - имя пункта меню
	MY_MENU(const char* name, ...) {
		const char** p = &name;
		while (*p != 0)
		{
			create();//проверим наличия меню, создадим или расширим
			menu[count - 1].length_name = strlen(*p);
			menu[count - 1].name = *p;
			p++;
		}
	}

	//деструктор
	~MY_MENU() {
		//произвести очистку меню
		remove();
	}

	//функция инициализации пункта меню с одним параметром
	void init(const char* name) {
		create();
		menu[count - 1].length_name = strlen(name);
		menu[count - 1].name = name;
	}

	//функция создания или расширения нашего меню
	void create() {
		//если меню создано - расширяем
		if (menu != nullptr)
		{
			try {
				//создаем новое меню с одним добавочным пунктом
				MENU_NAME* tmp_menu = new MENU_NAME[++count];
				//скопируем все существующие пункты меню
				for (size_t i = 0; i < (count - 1); i++)
					tmp_menu[i] = menu[i];
				//удалим старое меню
				delete[] menu;
				//возьмем новое сформированное меню
				menu = tmp_menu;
			}
			catch (exception ex) {
				SetConsoleTextAttribute(hStdOut, wAttributeWarning);
				cout << "\n\n"
					<< "\t\t                                                       \n"
					<< "\t\t    [Ошибка(создание MY_MENU)]                         \n"
					<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
					<< "\t\t                                                       \n"
					<< "\n\n\n\n\n\n\n\n\n\n\n\n";
				SetConsoleTextAttribute(hStdOut, wAttributeNormal);
			}
		}
		else
			//создадим первый пункт меню
			menu = new MENU_NAME[++count];
	}

	//функция удаления меню после работы
	void remove() {
		if (menu != nullptr)
		{
			try {
				delete[] menu;
			}
			catch (exception ex) {
				SetConsoleTextAttribute(hStdOut, wAttributeWarning);
				cout << "\n\n"
					<< "\t\t                                                       \n"
					<< "\t\t    [Ошибка(удаление MY_MENU)]                         \n"
					<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
					<< "\t\t                                                       \n"
					<< "\n\n\n\n\n\n\n\n\n\n\n\n";
				SetConsoleTextAttribute(hStdOut, wAttributeNormal);
			}
		}

	}

	//функция вывода пунктов меню
	void display() {
		for (size_t i = 0; i < count; i++)
			cout << menu[i].name << endl;
	}

	//функция вывода полной информации о структуре меню
	void displayAll() {
		for (size_t i = 0; i < count; i++)
		{
			cout << "Name: " << menu[i].name << endl;
			cout << "Length: " << menu[i].length_name << endl;
		}
	}
};

typedef MY_MENU arguments;
typedef MY_MENU list_filename;
#endif //TYPESTRUCT_H
