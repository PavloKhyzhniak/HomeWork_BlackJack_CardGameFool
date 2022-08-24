
#ifndef TELEVISOR_H /* Страж */
#define TELEVISOR_H /* единственности вхождения - начало */


#include "pch.h"
#include "Utils.h"


namespace classApp {
	

//	template <typename T>
//	void quickSortR(
//		T* array,
//		size_t end,
//		bool valid(const T,const T) =
//		[](const T A,const T B) {return(A < B); })
//	{
//		// На входе - массив a[], a[N] - его последний элемент.
//
//	//	display(end + 1, array, "\n\t1-D array(SubArray):\n");
//
//		// для работы алгоритма
//		intmax_t i = 0, j = end; //левая и правая граница определены
//
//		// расчет начального индекса середины массива
//		T value = array[end >> 1]; // середина - значение элемента в середине интервала
//
//		T temp; // вспомогательная переменная
//		// процедура разделения
//		do {
//			// движение от начала к середине, пока не найдем элемент не удовлетворяющий условию
//			//while (array[i] < p) i++;
//			while (valid(array[i], value)) i++;
//
//			// движение от конца к середине, пока не найдем элемент не удовлетворяющий условию
//			//while (array[j] > p) j--;
//			while (valid(value, array[j])) j--;
//
//			if (i <= j) {
//				//	swap(array[i],array[j]);
//				temp = array[i]; array[i++] = array[j]; array[j--] = temp;
//			}
//
//			//		display(end + 1, array, "\n\t1-D array(swap/iter):\n");
//
//		} while (i <= j);
//
//		// рекурсивные вызовы, если есть, что сортировать 
//		if (j > 0) quickSortR(array, j, valid); // от начала массива до cur
//		if (end > i) quickSortR(array + i, end - i, valid); // от cur+1 до конца массива
//	}// quickSortR

	//создадим структуру для удобства инициализации объектов Класса Televisor
	struct TV {

		const char manufacturer[20];
		const char model[20];

		double size;
		int resX;
		int resY;
		double price;

	};

	//Введем перечисление для удобства работы с Фильтром по полям объекта Televisor при работе с Классом ArrayTelevisor
	enum MyMethod_enum//:uint8_t
	{
		GET_MANUFACTURER = 0,
		GET_MANUFACTURER_LENGTH,
		GET_MODEL,
		GET_MODEL_LENGTH,
		GET_SIZE,
		GET_RESX,
		GET_RESY,
		GET_PRICE,
		ERROR_ENUM ,
	};
	
	//класс 
	class Televisor
	{
	private:
//статическая переменная, контроль созданных объектов в программе
		static int count_;

		//поле производитель
		char* manufacturer_;
		int manufacturer_length_;

		//поле модель
		char* model_;
		int model_length_;

		//поле размер(диагональ)
		double size_;
		//поля X и Y, разрешения соответственно
		int resX_;
		int resY_;
		//поле цена
		double price_;

		//перегрузка через дружественные функции ввода >> и вывода <<
		friend std::ostream& operator<<(std::ostream& os, const Televisor& object);
		friend std::istream& operator>>(std::istream& is, Televisor& object);


	public:
		//constructor
//конструктор по умолчанию
		Televisor();
		//конмтруктор с параметрами инициализации объекта
		Televisor(const char* manufacturer, const char* model, double size, int resX, int resY, double price);
		//конструктор копирующий
		Televisor(const Televisor& object);
		//destructor
		//деструктор
		~Televisor();

		//set
		//метод для инициализации объекта, задавая все поля
		int setConstructor(const char* manufacturer, const char* model, double size, int resX, int resY, double price);
		//метод для инициализации объекта, через структуру содержащую все поля объекта
		int setConstructor(TV newTV);

		//сеттеры установки полей объекта
		int setManufacturer(const char* name);
		int setModel(const char* name);

		int setSize(double size);
		int setResolution(int resX, int resY);
		int setPrice(double price);

		//get
		//геттеры для доступа к полям объекта
		const char* getManufacturer() const;
		int getManufacturerLength() const;
		const char* getModel() const;
		int getModelLength() const;

		double getSize() const;
		int getResX() const;
		int getResY() const;
		double getPrice() const;

		//methods
		
		// инспектор - возвращает true для пустой записи, т.е. созданной конструктором
		// по умолчанию
		bool IsEmpty() const { return ((!strcmp(manufacturer_,"_noname_")) && (!strcmp(model_,"_noname_")) && 
			(abs(size_) <= 0.1) && (resX_ == 0) && (resY_ == 0) && (abs(price_) <= 0.1)); }
		
		// чтение из текстового файла в объект
		void get(FILE* File);

		// запись объекта в текстовый файл
		void put(FILE* File) const;

		// служебный метод - приведение полей объекта в строковое представление
		char* toString() const;

		//работа с файлом в формате .csv
		void toCsv(char* str) const;
		void parseCsv(char* str);
		
		// Сохранение/запись в бинарный файл
		void Write(FILE* f) const;

		// Читать из бинарного файла в поля класса
		void Read(FILE* f);

		//operators

		// оператор присваивания копированием
		Televisor& operator=(const Televisor& object);

		// оператор присваивания перемещением
		Televisor& operator=(Televisor&& object) = default;

		
	};

	//класс 
	class ArrayTelevisor
	{
	private:
//статическая переменая для контролля созданных объектов в программе
		static int count_;

		//поле имя массива(списка)
		char* name_;
		int name_length_;

		int size_;          // размер массива
		Televisor* televisors_;  // массив

		//закрытый метод, быстрая сортировка
		void QuickSort(int start, int end, int compare(const Televisor& TV1, const Televisor& TV2));

		//предикаты для функции сортировки
		static int CompareManufacturer(const Televisor& TV1, const Televisor& TV2);
		static int CompareModel(const Televisor& TV1, const Televisor& TV2);

		static int CompareSize(const Televisor& TV1, const Televisor& TV2);
		static int CompareResolutionX(const Televisor& TV1, const Televisor& TV2);
		static int CompareResolutionY(const Televisor& TV1, const Televisor& TV2);
		static int ComparePrice(const Televisor& TV1, const Televisor& TV2);

		//закрытый метод, установка размера массива
		int setSize(int size);

		//закрытый метод, проверки корректности передачи условия фильтрования параметра-поля(метода) в Фильтр
		static	bool isCorrect(MyMethod_enum check)
		{
			return ((check >= GET_MANUFACTURER) && (check <= ERROR_ENUM));
		}
		
	public:
		//constructor
		//конструктор по умолчанию запретим
		ArrayTelevisor() = delete;
		//конструктор с параметрами
		ArrayTelevisor(int size, const char* name);
		//конструктор с параметрами(инициализация готовым массивом объектов)
		ArrayTelevisor(Televisor* TVs, int size, const char* name);
		//конструктор копирования
		ArrayTelevisor(const ArrayTelevisor& object);
		//destructor
		//деструктор
		~ArrayTelevisor();

		//set
		//функция корректоного создания(пересоздания) объекта
		int create(int size, const char* name);
		//функция корректного удаления содержимого объекта, для пересоздания
		void clear();

		//сеттен имени коллекции(массива)
		int setName(const char* name);

		//get
		//геттеры для доступа ко всем полям объекта
		char* getName() const;
		int getNameLength() const;

		int getSize() const;

		//methods

		// инспектор - возвращает true для пустой записи, т.е. созданной конструктором
		// по умолчанию
		bool IsEmpty() const { return ((name_ == nullptr) && (name_length_ == 0) && (size_ == 0) && (televisors_ == nullptr)); }

		// чтение из текстового файла в объект
		void get(FILE* File);

		// запись объекта в текстовый файл
		void put(FILE* File) const;

		// служебный метод - приведение полей объекта в строковое представление
		char* toString() const;

		//сортировка
		void OrderByManufacturer() { QuickSort(0, getSize() - 1, CompareManufacturer); }
		void OrderByModel() { QuickSort(0, getSize() - 1, CompareModel); }

		void OrderBySize() { QuickSort(0, getSize() - 1, CompareSize); }
		void OrderByResolutionX() { QuickSort(0, getSize() - 1, CompareResolutionX); }
		void OrderByResolutionY() { QuickSort(0, getSize() - 1, CompareResolutionY); }
		void OrderByPrice() { QuickSort(0, getSize() - 1, ComparePrice); }

		//работа с файлами
		static void WriteToCsv(const char* fileNameCsv, const ArrayTelevisor* TVs);
		static void ReadFromCsv(const char* fileNameCsv, ArrayTelevisor* TVs);
		static void AppendToCsv(const char* fileNameCsv, const Televisor* TV);

		void WriteArrayToBin(const char* fileNamePersons);
		void ReadArrayFromBin(const char* fileNamePersons);

		void writeToFile(FILE* File) const;

		// вывод автопарка в виде таблицы
		void show(const char* title = "_noname_");

		//шаблонный метод
		//фильтр по диапазонам значений чисел [min;max]
		template <typename T>
		static	void filter(ArrayTelevisor* arr, T(Televisor::* getMethod)() const, const T min, const T max)
		{
			//создаем временный массив, размер которого не больше исходного
			ArrayTelevisor tmpArr(arr->getSize(), arr->getName());

			int j;//счетчик отфильтрованных объектов
#pragma warning(suppress:4984)
			if constexpr (is_same_v<T, int>)
			{
				j = 0;//счетчик отфильтрованных объектов на ноль
				for (int i = 0; i < arr->getSize(); i++)//проверим все объекты переданной коллекции
					if (//проверяем диапазон по целым числам
						(((arr->televisors_[i]).*getMethod)() >= min) &&
						(((arr->televisors_[i]).*getMethod)() <= max)
						)
						//при вхождении в диапазон, объект записываеться во временный массив(результирующий)
						tmpArr.televisors_[j++] = arr->televisors_[i];
			}
#pragma warning(suppress:4984)
			else if constexpr (is_same_v<T, double>)
			{
				j = 0;//счетчик отфильтрованных объектов на ноль
				for (int i = 0; i < arr->getSize(); i++)//проверим все объекты переданной коллекции
					if (//проверяем диапазон по вещественным числам
						(((arr->televisors_[i]).*getMethod)() >= min) &&
						(((arr->televisors_[i]).*getMethod)() <= max)
						)
						//при вхождении в диапазон, объект записываеться во временный массив(результирующий)
						tmpArr.televisors_[j++] = arr->televisors_[i];
			}
			else
				throw exception("Unknown type variable passed.");

			//очищаем переданную коллекцию
			arr->clear();
			//подготавливаем указатель на переданную коллекцию к новому отфильтрованному содержимому
			arr->create(j, tmpArr.getName());

			//копируем все объекты из временного массива
			for (int i = 0; i < j; i++)
				(*arr)[i] = tmpArr[i];
			//временный массив удаляеться посредством вызова деструктора
		};

		//шаблонный метод
		// фильтр по списку названий (const char*)
		template <typename T>
		static	void filter(ArrayTelevisor* arr, T(Televisor::* getMethod)() const, char*** arrayName, const size_t N)
		{
			//создаем временный массив, размер которого не больше исходного
			ArrayTelevisor tmpArr(arr->getSize(), arr->getName());
	
			int j;//счетчик отфильтрованных объектов
	
	#pragma warning(suppress:4984)
			if constexpr (is_same_v<T, const char*>)
			{
				j = 0;//счетчик отфильтрованных объектов на ноль
				for (int i = 0; i < arr->getSize(); i++)//проверим все объекты переданной коллекции
					for (size_t k = 0; k < N; k++)//проверяем каждый объект переданной коллекции, с фильтрующими значениями(arrayName)
						if (!strcmp(((arr->televisors_[i]).*getMethod)(), (*arrayName)[k]))
						{
							//при совпадении(нахождении) объекта маркеру фильтра, сохраняем объект во временном массиве(результирующем)
							tmpArr.televisors_[j++] = arr->televisors_[i];
							break;//прерываем цикл поиска по фильтрующим маркера, переходим к следующему объекту коллекции
						}
			}
			else
				throw exception("Unknown type variable passed.");
	
			//очищаем переданную коллекцию
			arr->clear();
			//подготавливаем указатель на переданную коллекцию к новому отфильтрованному содержимому
			arr->create(j, tmpArr.getName());

			//копируем все объекты из временного массива
			for (int i = 0; i < j; i++)
				(*arr)[i] = tmpArr[i];
			//временный массив удаляеться посредством вызова деструктора
		};

		//функция заполнения динамического массива имен для фильтра по производителю и модели
		static void addArrayName(char*** arrayName, size_t* N, const char* Name) 
		{
			//проверяем существует ли массив маркеров фильтра
			if (*arrayName != nullptr)
			{
				size_t i;
				//поиск дубликатов
				for (i = 0; i < *N ; i++)//проверим все маркеры фильтра на совпадение с новым маркером(Name)
				{
					//при совпадении(нахождения дубликата),прерываем просмотр маркеров, выходим из цикла
					if (!strcmp((*arrayName)[i], Name)) break;
				}

				if (i == *N)//если был найден дубликат(не все элементы массива маркеров фильтра были просмотрены)
				{
					//создаем новый массив с дополнительным элементом
					char** newArray = new char* [++(*N)]{ 0 };
					//копируем все исходные значения
					for (i = 0; i < (*N - 1); i++)
					{
						try {
							newArray[i] = new char[strlen((*arrayName)[i]) + 1];
						}
						catch (exception ex)
						{
							throw exception("\n\t addArrayName():No memory to NEW name.\n");
						}

						strcpy(newArray[i], (*arrayName)[i]);
					}
					//сохраняем добавочный элемент
					try {
						newArray[i] = new char[strlen(Name) + 1];
					}
					catch (exception ex)
					{
						throw exception("\n\t addArrayName():No memory to NEW name.\n");
					}

					strcpy(newArray[i], Name);
					//удаляем старый массив
					if (*arrayName != nullptr)
						delete[] * arrayName;
					//утверждаем новый массив
					*arrayName = newArray;
				}
			}
			else
			{
				//вновь созданный массив
				*arrayName = new char* [(*N) = 1]{ 0 };

				try {
					(*arrayName)[0] = new char[strlen(Name) + 1];
				}
				catch (exception ex)
				{
					throw exception("\n\t addArrayName():No memory to NEW name.\n");
				}
				strcpy((*arrayName)[0], Name);
			}
		}

		//	ArrayTelevisor::showFilter(&c3, 2, GET_PRICE, GET_SIZE);
		//статический метод фильтрующий объекты заданной коллекции(arr), по заданным фильтрам(см. MyMethod_enum)
		static	void showFilter(ArrayTelevisor* arr, int n, int number, ...)
		{
			//
			va_list p;//переменная указатель на следующий переданный аргумент
			va_list copy_p;//переменная копия указателя на следующий переданный аргумент
			va_start(p, n);//инициализация указателя, на аргумент n

			//произведем копирование переданного объекта(защита от повреждения при фильтрации - удаление объектов вне диапазона фильтра)
			ArrayTelevisor resultArr(arr->getSize(), arr->getName());

			//скопируем все объекты исходного массива
			for (int i = 0; i < arr->getSize(); i++)
				resultArr[i] = (*arr)[i];

			//создадим указатель на скопированный исходный массив(коллекцию)
			ArrayTelevisor* tmpArr = &resultArr;

			//создаем указатель на массив маркеров фильтра для filter работающей с const char*
			char** arrayName = nullptr;
			size_t N = 0;//количество маркеров в массиве

			//вспомогательная переменная для считывания из переменного числа аргументов маркеров фильтра заданных как const char*
			const char* name{ 0 };

			//пока есть не обработанные аргументы
			while (n-->0) {

				//считаем следующий аргумент(всегда ожидаем вариант из MyMethod_enum
				int method = va_arg(p, int);

				//настраиваем фильтр согласно считанному критерию(выбранному полю объекта - метода доступа к данному полю)
				switch (method)
				{
				case GET_MANUFACTURER:
				case GET_MODEL:
					//по производителю 
					//по модели

					n--;//учитываем обработанный аргумент
					//считываем следующий аргумент(всегда ожидаем минимум один маркер вида const char*)
					name = va_arg(p, const char*);
					addArrayName(&arrayName, &N, name);//сохраним считанный маркер фильтра в массив фильтрующих значений по данному критерию

					while (n-- > 0)//пока есть аргументы, смотрим нет ли еще переданных маркеров по данному критерию
					{
						//делаем копию указателя на следующий аргумент, а вдруг больше нету аргументов, или дальше идет параметры следующего фильтра
						va_copy(copy_p, p);

						//считываем следующий аргумент(будем считать что дальше идет новый фильтр)
						int index = va_arg(p, int);

						//вернемся к исходному аргументу(сделаем шаг назад)
						va_copy(p, copy_p);

						//проверим считанное значение, если он корректен значениям из MyMethod_enum, то
						if (isCorrect(static_cast<MyMethod_enum>(index)))
						{
							//укажем что аргументов на 1 больше(компенсация учета считанного значения)
							n++;
							//выход из цикла
							break;
						}

						//в случае не корректности считанного значения MyMethod_enum, то видимо еще один маркер
						//считываем ожидая получить маркер(const char*)
						name = va_arg(p, const char*);

						addArrayName(&arrayName, &N, name);//сохраним считанный маркер фильтра в массив фильтрующих значений по данному критерию
					}
					
					if (method == GET_MANUFACTURER)
					{
						//filter(tmpArr, &Televisor::getManufacturer, "LG", "SAMSUNG");
						filter(tmpArr, &Televisor::getManufacturer, &arrayName, N);//вызовем функцию фильтра, передадим соответствующий метод(критерий) и массив маркеров для фильтра

						//удалим массив маркеров полученных из строки аргументов
						if (arrayName != nullptr)
						{
							if (*arrayName != nullptr)
								delete[] * arrayName;
							arrayName = nullptr;
						}
						//укажем промежуточное значение работы фильтра, сначала покажем после какого фильтра
						cout << "\nФильтр по производителю.\n";
						break;
					}

					if (method == GET_MODEL)
					{
						//filter(tmpArr, &Televisor::getModel, "S22B350", "34UM61");
						filter(tmpArr, &Televisor::getModel, &arrayName, N);//вызовем функцию фильтра, передадим соответствующий метод(критерий) и массив маркеров для фильтра

						//удалим массив маркеров полученных из строки аргументов
						if (arrayName != nullptr)
						{
							if (*arrayName != nullptr)
								delete[] * arrayName;
							arrayName = nullptr;
						}

						//укажем промежуточное значение работы фильтра, сначала покажем после какого фильтра
						cout << "\nФильтр по модели.\n";
						break; 
					}
					throw(exception("showFilter(): not correct method."));
					break;
				case GET_MANUFACTURER_LENGTH:
					filter(tmpArr, &Televisor::getManufacturerLength, 5, 10);
					cout << "\nФильтр по длинне имени производителя(от 5 до 10).\n";
					break;
				case GET_MODEL_LENGTH:
					filter(tmpArr, &Televisor::getModelLength, 5, 10);
					cout << "\nФильтр по длинне названия модели(от 5 до 10).\n";
					break;
				case GET_SIZE:
					filter(tmpArr, &Televisor::getSize, 25., 30.);
					cout << "\nФильтр по размеру(от 25. до 30.).\n";
					break;
				case GET_RESX:
					filter(tmpArr, &Televisor::getResX, 2000, 3000);
					cout << "\nФильтр по разрешению оси Y(от 2000 до 3000).\n";
					break;
				case GET_RESY:
					filter(tmpArr, &Televisor::getResY, 2000, 3000);
					cout << "\nФильтр по разрешению оси Y(от 2000 до 3000).\n";
					break;
				case GET_PRICE:
					filter(tmpArr, &Televisor::getPrice, 2500., 3000.);
					cout << "\nФильтр по цене(от 2500. до 3000.).\n";
					break;
				default:
					throw(exception("Wrong filter method."));
				}
				tmpArr->show(tmpArr->getName());

			}
			//удалим указатели на переменное число аргументов функции
			va_end(p);
			va_end(copy_p);

			//покажем отфильтрованную коллекцию
			tmpArr->show(tmpArr->getName());

			anyKey();
		};

		void showMinSize();

		Televisor& at(int index) const;
		void put(int index, const Televisor& TV);


		//operators

		// оператор присваивания копированием
		ArrayTelevisor& operator=(const ArrayTelevisor& object);

		// оператор присваивания перемещением
		ArrayTelevisor& operator=(ArrayTelevisor&& object) = default;

		// перегрузка операции индексирования
		Televisor& operator[](int index);

		//интерактивная справка
		const char* operator[](const char* word);

	};

	void TestClassTelevisor();
	void TestClassArrayTelevisor();

	void Exercises();

}// classApp


#endif //TELEVISOR_H

