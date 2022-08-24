#ifndef TYPESTRUCT_H /* ����� */
#define TYPESTRUCT_H /* �������������� ��������� - ������ */

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;

//������� ����� ��� ��� ����� ����
struct MENU_NAME {
	const char* name;
	size_t length_name;
};

//������� ����� ��� ��� ����
struct MY_MENU {
	MENU_NAME* menu = nullptr;
	size_t count = 0;

	//����������� ��� ����������
	MY_MENU(void) {
		menu = nullptr;
		count = 0;
	}
	
	// MY_MENU menu1("00 - ","01 - ","02 - ", 0);
		//����������� � ���������� ������ ���������� - ��� ������ ����
	MY_MENU(const char* name, ...) {
		const char** p = &name;
		while (*p != 0)
		{
			create();//�������� ������� ����, �������� ��� ��������
			menu[count - 1].length_name = strlen(*p);
			menu[count - 1].name = *p;
			p++;
		}
	}

	//����������
	~MY_MENU() {
		//���������� ������� ����
		remove();
	}

	//������� ������������� ������ ���� � ����� ����������
	void init(const char* name) {
		create();
		menu[count - 1].length_name = strlen(name);
		menu[count - 1].name = name;
	}

	//������� �������� ��� ���������� ������ ����
	void create() {
		//���� ���� ������� - ���������
		if (menu != nullptr)
		{
			try {
				//������� ����� ���� � ����� ���������� �������
				MENU_NAME* tmp_menu = new MENU_NAME[++count];
				//��������� ��� ������������ ������ ����
				for (size_t i = 0; i < (count - 1); i++)
					tmp_menu[i] = menu[i];
				//������ ������ ����
				delete[] menu;
				//������� ����� �������������� ����
				menu = tmp_menu;
			}
			catch (exception ex) {
				SetConsoleTextAttribute(hStdOut, wAttributeWarning);
				cout << "\n\n"
					<< "\t\t                                                       \n"
					<< "\t\t    [������(�������� MY_MENU)]                         \n"
					<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
					<< "\t\t                                                       \n"
					<< "\n\n\n\n\n\n\n\n\n\n\n\n";
				SetConsoleTextAttribute(hStdOut, wAttributeNormal);
			}
		}
		else
			//�������� ������ ����� ����
			menu = new MENU_NAME[++count];
	}

	//������� �������� ���� ����� ������
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
					<< "\t\t    [������(�������� MY_MENU)]                         \n"
					<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
					<< "\t\t                                                       \n"
					<< "\n\n\n\n\n\n\n\n\n\n\n\n";
				SetConsoleTextAttribute(hStdOut, wAttributeNormal);
			}
		}

	}

	//������� ������ ������� ����
	void display() {
		for (size_t i = 0; i < count; i++)
			cout << menu[i].name << endl;
	}

	//������� ������ ������ ���������� � ��������� ����
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
