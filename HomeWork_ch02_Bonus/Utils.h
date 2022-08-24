#ifndef UTILS_H /* Страж */
#define UTILS_H /* единственности вхождения - начало */

#include"TypeStruct.h"

void Line(const size_t,const char);

void CheckArguments(int argc, char* argv[],arguments* my_arguments);

char displayMenu(const char*, MY_MENU*, size_t* const);
void displayMenu(const char[1000], const size_t, const char[][40], const size_t);
char setMenu(size_t* k, const size_t roundIndex);
void setMenuC(char*, size_t*,const size_t);

bool inputKey(char* keyChar = nullptr, size_t size = 0, const char greeting[] = "\n\tДля подтверждения нажмите 'Y' или 'y'... ");
bool inputInvisibleKey(char* keyChar, size_t size);
bool keyMenuUpDown(char* key);
bool keyMenu(char* key);
bool keyMenuNumber(char* key);
bool keyRepeat();
bool keyExit();
bool keyEnter();
bool anyKey();
bool anyKey(short x, short y);
void Pause(unsigned short timePause = 3);


unsigned int myRand();



//
//bool valid(const int* const) = [](const int* const k) {return(((k >= 1) && (k <= 5)) ? true : false); };
//setValue(k, valid);
//
template <typename T>
bool setValue(
	T* n,
	const char greeting[] = "Введите: ",
	bool validation(const T* const) = [](const T* const) {return (true);},
	const char warning[] = "Значение введено не корректно. Повторите ввод.")
{
	bool keyLoop = false;
	while (true) {
		cout << "\t" << greeting;
		//проверим правильность считываемых данных
		if (!(cin >> *n)) {
			cin.clear();//сброс состояния ошибки буффера ввода
			cin.ignore(cin.rdbuf()->in_avail());//очистка буффера ввода от недопустимых символов
		}
		else {
			//проверка введенных данных - валидация ввода
			if (validation(n))
				break;
		}
		cout << "\t" << warning << "\r";
		Sleep(1000);
		cout << "\t                                                                                      \r";
		continue;
	}
	keyLoop = true;
	return keyLoop;
}

//
//bool valid(const int* const) = [](const int* const k) {return(((k >= 1) && (k <= 5)) ? true : false); };
//setValue(k, valid);
//
template <typename T>
bool setValue(
	std::istream& is,
	T* n,
	const char greeting[] = "Введите: ",
	bool validation(const T* const) = [](const T* const) {return (true); },
	const char warning[] = "Значение введено не корректно. Повторите ввод.")
{
	bool keyLoop = false;
	while (true) {
		cout << "\t" << greeting;
		//проверим правильность считываемых данных
		if (!(is >> *n)) {
			is.clear();//сброс состояния ошибки буффера ввода
			is.ignore(is.rdbuf()->in_avail());//очистка буффера ввода от недопустимых символов
		}
		else {
			//проверка введенных данных - валидация ввода
			if (validation(n))
				break;
		}
		cout << "\t" << warning << "\r";
		cout << "\t                                                                                      \r";
		continue;
	}
	keyLoop = true;
	return keyLoop;
}

#endif //UTILS_H



