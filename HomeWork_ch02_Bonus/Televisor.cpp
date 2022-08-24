
#pragma once

#include "Televisor.h"


#include "pch.h"
#include "Utils.h"
#include "UtilsConsole.h"
#include "Func.h"

extern wchar_t title[150];

namespace classApp {


#pragma region Televisor
	//STATIC data
#pragma region STATIC_data

	//инициализируем статическую переменную-счетчик созданных объектов
	int Televisor::count_ = 0;

#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

	std::ostream& operator<<(std::ostream& os, const Televisor& object)
	{
		os << "\nПроизводитель: " << setw(20) << object.manufacturer_
			<< "\nМодель: " << setw(10) << object.model_
			<< "\nРазмер: " << setw(10) << fixed << setprecision(2) << object.size_
			<< "\nРазрешение(ШхВ): " << setw(5) << object.resX_
			<< " : " << setw(5) << object.resY_
			<< "\nЦена,$: " << setw(10) << fixed << setprecision(2) << object.price_
			;

		return os;
	}

	std::istream& operator>>(std::istream& is, Televisor& object)
	{
		int tmpInt;
		int tmpInt2;
		double tmpDouble;

		//Один из вариантов ввода данных
		char* name = new char[100]{ 0 };
		setValue<char*>(is, &name, "Производитель: ");
		object.setManufacturer(name);

		setValue<char*>(is, &name, "Модель: ");
		object.setModel(name);
		delete[] name;

		
		setValue<double>(is, &tmpDouble, "Размер: ", [](const double* const k) {return(((*k > 0.) && (*k <= 1000.)) ? true : false); });
		object.setSize(tmpDouble);

		setValue<int>(is, &tmpInt, "Разрешение по оси X: ", [](const int* const k) {return(((*k >= 640) && (*k <= 40000)) ? true : false); });
		setValue<int>(is, &tmpInt2, "Разрешение по оси Y: ", [](const int* const k) {return(((*k >= 480) && (*k <= 4000)) ? true : false); });
		object.setResolution(tmpInt,tmpInt2);

		setValue<double>(is, &tmpDouble, "Цена, $: ", [](const double* const k) {return((*k >= 0.) ? true : false); });
		object.setPrice(tmpDouble);
			
		return is;
	}

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor
	Televisor::Televisor()
		:manufacturer_{ nullptr }, model_{ nullptr }
	{
		setManufacturer("_noname_");
		setModel("_noname_");

		setSize(0);
		setResolution(0,0);
		setPrice(.0);

#ifdef _DEBUG
		cout << endl << "Конструктор по умолчанию(без параметров). Класс Televisor.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	Televisor::Televisor(const char* manufacturer, const char* model, double size, int resX, int resY, double price)
		:manufacturer_{ nullptr }, model_{ nullptr }
	{

		setManufacturer(manufacturer);
		setModel(model);

		setSize(size);
		setResolution(resX,resY);
		setPrice(price);

#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами. Класс Televisor.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	Televisor::Televisor(const Televisor& object)
		:manufacturer_{ nullptr }, model_{ nullptr }
	{
		char* tmp_str = nullptr;

		tmp_str = new char[object.manufacturer_length_ + 1];
		strcpy(tmp_str, object.manufacturer_);
		if ((*this).manufacturer_)
			delete[] this->manufacturer_;
		this->manufacturer_ = tmp_str;
		this->manufacturer_length_ = strlen(tmp_str);

		tmp_str = new char[object.model_length_ + 1];
		strcpy(tmp_str, object.model_);
		if ((*this).model_)
			delete[] this->model_;
		this->model_ = tmp_str;
		this->model_length_ = strlen(tmp_str);

		this->size_ = object.size_;
		this->resX_ = object.resX_;
		this->resY_ = object.resY_;
		this->price_ = object.price_;

#ifdef _DEBUG
		cout << endl << "Конструктор копирования. Класс Televisor.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//destructor
	Televisor::~Televisor() {

		if (this->manufacturer_)
		{
			delete[] this->manufacturer_;
			manufacturer_ = nullptr;
		}
		if (this->model_)
		{
			delete[] this->model_;
			model_ = nullptr;
		}
#ifdef _DEBUG
		cout << endl << "Деструктор. Класс Televisor.\n";
		cout << "Всего существует " << --count_ << " объектов\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS
	int Televisor::setConstructor(const char* manufacturer, const char* model, double size, int resX, int resY, double price)
	{

		setManufacturer(manufacturer);
		setModel(model);

		setSize(size);
		setResolution(resX,resY);
		setPrice(price);

		return 0;
	}

	int Televisor::setConstructor(TV myTV)
	{

		setManufacturer(myTV.manufacturer);
		setModel(myTV.model);

		setSize(myTV.size);
		setResolution(myTV.resX, myTV.resY);
		setPrice(myTV.price);

		return 0;
	}

	int Televisor::setManufacturer(const char* name) {
		this->manufacturer_length_ = strlen(name);
		try {
			if (this->manufacturer_)
				delete[](*this).manufacturer_;
		}
		catch (exception ex)
		{
			throw exception("\n\t Televisor:Cannot DELETE[] manufacturer.\n");
		}
		try {
			this->manufacturer_ = new char[this->manufacturer_length_ + 1];
		}
		catch (exception ex)
		{
			throw exception("\n\t Televisor:No memory to NEW manufacturer.\n");
		}

		strcpy(this->manufacturer_, name);

		return 0;
	}

	int Televisor::setModel(const char* name) {
		this->model_length_ = strlen(name);
		try {
			if (this->model_)
				delete[](*this).model_;
		}
		catch (exception ex)
		{
			throw exception("\n\t Televisor:Cannot DELETE[] model.\n");
		}
		try {
			this->model_ = new char[this->model_length_ + 1];
		}
		catch (exception ex)
		{
			throw exception("\n\t Televisor:No memory to NEW model.\n");
		}

		strcpy(this->model_, name);

		return 0;
	}

	int Televisor::setSize(double number) {
		if (number < 0)
			throw exception("\n\t Televisor:Wrong size.\n");

		this->size_ = number;

		return 0;
	}
	
	int Televisor::setResolution(int resX, int resY) {
		if (resX < 0)
			throw exception("\n\t Televisor:Wrong resolution X.\n");
		if (resY < 0)
			throw exception("\n\t Televisor:Wrong resolution Y.\n");

		this->resX_ = resX;
		this->resY_ = resY;

		return 0;
	}

	int Televisor::setPrice(double number) {
		if (number < 0)
			throw exception("\n\t Televisor:Wrong price.\n");

		this->price_ = number;

		return 0;
	}


#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER

	const char* Televisor::getManufacturer() const {
		return this->manufacturer_;
	}

	int Televisor::getManufacturerLength() const {
		return this->manufacturer_length_;
	}

	const char* Televisor::getModel() const {
		return this->model_;
	}

	int Televisor::getModelLength() const {
		return this->model_length_;
	}

	double Televisor::getSize() const {
		return this->size_;
	}

	int Televisor::getResX() const {
		return this->resX_;
	}

	int Televisor::getResY() const {
		return this->resY_;
	}

	double Televisor::getPrice() const {
		return this->price_;
	}


#pragma endregion

	//METHODS
#pragma region METHODS

	// чтение из текстового файла в объект
	void Televisor::get(FILE* File)
	{
		// при достижении конце файла не читаем данные
		if (feof(File)) return;

		// строковые данные читаем fgets()
		//динамическая строка, для чтения из файл
		char* str = new char[2024];
		int i;

		//считываем по строчно информацию 
		fgets(str, 2024, File);
		//удаление символа новой строки у считываемой строки-имени
		i = (strlen(str) - 1);
		if (str[i] == '\n')
			str[i] = '\0';
		setManufacturer(str);

		//считываем по строчно информацию 
		fgets(str, 1024, File);
		//удаление символа новой строки у считываемой строки-имени
		i = (strlen(str) - 1);
		if (str[i] == '\n')
			str[i] = '\0';
		setModel(str);

		delete[] str;

		// числовые данные считываем форматным вводом и учитываем
		// перевод строки после чтения последнего числа

		int tmpNumberInt;
		int tmpNumberInt2;
		double tmpNumberDouble;


		if (!fscanf(File, "%lf\n ", &tmpNumberDouble))
			throw exception("\n Televisor: get() fscanf() error.\n");
		setSize(tmpNumberDouble);

		if (!fscanf(File, "%d\n ", &tmpNumberInt))
			throw exception("\n Televisor: get() fscanf() error.\n");

		if (!fscanf(File, "%d\n ", &tmpNumberInt2))
			throw exception("\n Televisor: get() fscanf() error.\n");
		setResolution(tmpNumberInt, tmpNumberInt2);

		if (!fscanf(File, "%lf\n ", &tmpNumberDouble))
			throw exception("\n Televisor: get() fscanf() error.\n");
		setPrice(tmpNumberDouble);

	}

	// запись объекта в текстовый файл
	void Televisor::put(FILE* File) const
	{
		// каждое поле класса записываем в отдельную строку
		fprintf(File, "%s\n%s\n%lf\n%d\n%d\n%lf\n", manufacturer_, model_, size_, resX_, resY_, price_);
	}

	char* Televisor::toString() const
	{
		char* buf = new char[1024];
		sprintf(buf, "Manufacturer: %20s; Model: \"%10s\"; %8.2lf\"; %5d x %5d; %8.2lf $; \n", manufacturer_, model_, size_, resX_, resY_, price_);
		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

	// сохранение/запись в строку формата CSV - все поля в
	// одной строке, поля отделены друг от друга символом ';'
	void Televisor::toCsv(char* str) const {
		sprintf(str, "%s;%s;%.2lf;%d;%d;%.2lf\n", manufacturer_, model_, size_, resX_, resY_, price_);
	} // toCsv

	// разобрать строку в формате CSV на поля класса
	void Televisor::parseCsv(char* str)
	{
		char* temp = new char[strlen(str) + 1];
		strcpy(temp, str);
		const char* delims = ";\n";

		int tmpInt;
		int tmpInt2;
		double tmpDouble;

		char* token = strtok(str, delims);
		for (int field = 0; field < 6; field++) {
			switch (field) {
			case 0:
				setManufacturer(token);
				break;

			case 1:
				setModel(token);
				break;

			case 2:
				sscanf(token, "%lf", &tmpDouble); // atof()
				setSize(tmpDouble);
				break;

			case 3:
				sscanf(token, "%d", &tmpInt); // atoi()
				break;

			case 4:
				sscanf(token, "%d", &tmpInt2); // atoi()
				setResolution(tmpInt,tmpInt2);
				break;

			case 5:
				sscanf(token, "%lf", &tmpDouble); // atof()
				setPrice(tmpDouble);
				break;
			} // switch

			token = strtok(0, delims);
		} // for i

		delete[] temp;
	} // Person::parseCsv


//	// сохранение/запись в строку формата CSV - все поля в
//	// одной строке, поля отделены друг от друга символом ';'
//	void Televisor::toCsvBIN(char* str) const {
//		fwrite(&tmp, sizeof(int), 1, File);
//		sprintf(str, "%d;%s;%d;%s;%.2lf;%d;%d;%.2lf\n", manufacturer_length_, manufacturer_, model_length_, model_, size_, resX_, resY_, price_);
//	} // toCsv


	// Сохранение/запись в бинарный файл
	void Televisor::Write(FILE* File) const
	{		
		//записываем данные нашего объекта в бинарный файл
		int tmpInt;
		double tmpDouble;

		tmpInt = getManufacturerLength();
		fwrite(&tmpInt, sizeof(int), 1, File);
		fwrite(getManufacturer(), sizeof(char) * tmpInt, 1, File);

		tmpInt = getModelLength();
		fwrite(&tmpInt, sizeof(int), 1, File);
		fwrite(getModel(), sizeof(char) * tmpInt, 1, File);

		tmpDouble = getSize();
		fwrite(&tmpDouble, sizeof(tmpDouble), 1, File);

		tmpInt = getResX();
		fwrite(&tmpInt, sizeof(tmpInt), 1, File);

		tmpInt = getResY();
		fwrite(&tmpInt, sizeof(tmpInt), 1, File);

		tmpDouble = getPrice();
		fwrite(&tmpDouble, sizeof(tmpDouble), 1, File);
		
	} // Write

	// Читать из бинарного файла в поля класса
	void Televisor::Read(FILE* File)
	{
		const int N_LEN(1024);
		char buf[N_LEN];

		//считаем данные массива
		int tmpInt;
		int tmpInt2;
		double tmpDouble;

		fread(&tmpInt, sizeof(tmpInt), 1, File);
		fread(&buf, sizeof(char) * tmpInt, 1, File);
		buf[tmpInt] = '\0';
		setManufacturer(buf);

		fread(&tmpInt, sizeof(tmpInt), 1, File);
		fread(&buf, sizeof(char) * tmpInt, 1, File);
		buf[tmpInt] = '\0';
		setModel(buf);

		fread(&tmpDouble, sizeof(tmpDouble), 1, File);
		setSize(tmpDouble);
		
		fread(&tmpInt, sizeof(tmpInt), 1, File);
		fread(&tmpInt2, sizeof(tmpInt2), 1, File);
		setResolution(tmpInt, tmpInt2);
		
		fread(&tmpDouble, sizeof(tmpDouble), 1, File);
		setPrice(tmpDouble);
		
	} // Read
#pragma endregion

#pragma region OPERATORS
	Televisor& Televisor::operator=(const Televisor& object)
	{
		if (&object == this) return *this;

		char* tmp_str;

		tmp_str = new char[object.manufacturer_length_ + 1];
		strcpy(tmp_str, object.manufacturer_);
		if ((*this).manufacturer_)
			delete[] this->manufacturer_;
		this->manufacturer_ = tmp_str;
		this->manufacturer_length_ = strlen(tmp_str);

		tmp_str = new char[object.model_length_ + 1];
		strcpy(tmp_str, object.model_);
		if ((*this).model_)
			delete[] this->model_;
		this->model_ = tmp_str;
		this->model_length_ = strlen(tmp_str);

		this->size_ = object.size_;
		this->resX_ = object.resX_;
		this->resY_ = object.resY_;
		this->price_ = object.price_;

#ifdef _DEBUG
		cout << endl << "Оператор присваивания. Класс Televisor.\n";
		cout << "Всего существует " << count_ << " объектов\n";
#endif
		return *this;
	} // Televisor::operator=

#pragma endregion

#pragma endregion


	void TestClassTelevisor() {

		cls();

		// Установим актуальный заголовок окна
		SetConsoleTitle(title);
		// Установим актуальный заголовок окна
		myAddConsoleTitle(L" Тестирование Класса Televisor ");

		coutColor("\nСоздадим три отдельных объекта\n", wAttributeSpecial);


		Televisor c1;
		Televisor c2("LG", "25UM61", 25, 2560, 1080, 800.);
		Televisor c3 = c2;

		coutColor("\nПокажем наши объекты.\n", wAttributeSpecial);
		cout << c1.toString();
		cout << c2.toString();
		cout << c3.toString();

		//************************
		coutColor("\nПоработаем с объектом №3\n", wAttributeSpecial);
		c3.setConstructor("LG", "34UM61", 34, 2560, 1060, 950.);
		cout << "\nПроинициализируем объект новыми данными: \n" << c3.toString();

		c3.setManufacturer("SAMSUNG");
		cout << "\nУкажем нового производителя: \n" << c3.toString();
		c3.setModel("S22B350");
		cout << "\nУкажем новую модель: \n" << c3.toString();

		c3.setSize(22);
		cout << "\nУкажем новый размер: \n" << c3.toString();
		c3.setResolution(1920,1280);
		cout << "\nУкажем новое разрешение: \n" << c3.toString();
		c3.setPrice(1020.);
		cout << "\nУкажем новую цену: \n" << c3.toString();


		coutColor("\nЗапросим все поля объекта с использованием геттеров\n", wAttributeSpecial);
		//get
		cout << "\nПосмотрим производителя: " << c3.getManufacturer();
		cout << "\nПосмотрим длинну имени производителя: " << c3.getManufacturerLength();

		cout << "\nПосмотрим модель: " << c3.getModel();
		cout << "\nПосмотрим длинну имени модели: " << c3.getModelLength();

		cout << "\nПосмотрим размер монитора: " << c3.getSize();
		cout << "\nПосмотрим его разрешение по оси X: " << c3.getResX();
		cout << "\nПосмотрим его разрешение по оси Y: " << c3.getResY();
		cout << "\nПосмотрим цену: " << c3.getPrice();

		anyKey();

		//*************************
		FILE* File = fopen("testTelevisor.txt", "w");
		if (!File) {
			cout << endl << "File not created.";
			throw exception("\n\tFile not created.\n");
		}

		coutColor("\nЗаписали в файл\n", wAttributeSpecial);
		c1.put(File);
		c2.put(File);
		c3.put(File);

		fclose(File);

		File = fopen("testTelevisor.txt", "r");
		if (!File) {
			cout << endl << "File not opened.";
			throw exception("\n\tFile not opened.\n");
		}

		coutColor("\nСчитали из файла в обратном порядке\n", wAttributeSpecial);
		c3.get(File);
		c2.get(File);
		c1.get(File);

		//выведем информацию о существующих объектов в массиве
		cout << c1.toString();
		cout << c2.toString();
		cout << c3.toString();

		fclose(File);

		anyKey();

		//*************************
		coutColor("\nПроверим какие объекты пустые(созданные конструктором).\n", wAttributeSpecial);
		//выведем информацию о существующих объектов в массиве
		cout <<endl << "Объект № 1: "<< boolalpha <<c1.IsEmpty();
		cout <<endl << "Объект № 2: "<< boolalpha <<c2.IsEmpty();
		cout <<endl << "Объект № 3: "<< boolalpha <<c3.IsEmpty();
		cout << noboolalpha;
		anyKey();

		//*************************

		coutColor("\nПротестируем перегрузку операторов ввода\\вывода\n", wAttributeSpecial);
		cout << "Выведем информацию об объекте № 3 и введем информацию в объект № 2.\n";
		cout << c3 << endl;
//		cin >> c2;

		coutColor("\nПроверим содержимое наших объектов\n", wAttributeSpecial);
		//выведем информацию о существующих объектов в массиве
		cout << c1.toString();
		cout << c2.toString();
		cout << c3.toString();


		anyKey();

		cls();

	}
#pragma endregion

#pragma region ArrayTelevisor
	//STATIC data
#pragma region STATIC_data
	//инициализируем статическую переменную-счетчик созданных объектов
	int ArrayTelevisor::count_ = 0;

#pragma endregion

	//PRIVATE metods
#pragma region PRIVATE_metods
	//**************

#pragma endregion

	//friend metods(recomended PRIVATE)
#pragma region friend_metods
	//**************

#pragma endregion

	//PUBLIC metods
#pragma region PUBLIC_metods

#pragma region CONSTRUCTORS_DESTRUCTOR
	//constructor

	ArrayTelevisor::ArrayTelevisor(int size, const char* name)
		:name_{ nullptr }
	{
		if (size < 0)
			throw exception("\n ArrayTelevisor: Wrong index.");
		size_ = size;
		// массив динамический - создание
		// Тип *имя = new  Тип[РазмерВЭлементах];
		televisors_ = new Televisor[size];
		setName(name);

#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами. Класс ArrayTelevisor.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	ArrayTelevisor::ArrayTelevisor(Televisor* TVs, int size, const char* name)
		: televisors_(TVs),
		size_(size),
		name_{ nullptr }
	{
		setName(name);

#ifdef _DEBUG
		cout << endl << "Конструктор с параметрами(берем готовый массив). Класс ArrayTelevisor.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	ArrayTelevisor::ArrayTelevisor(const ArrayTelevisor& object)
		:name_{ nullptr }
	{
		create(object.getSize(), object.getName());

		for (int i = 0; i < getSize(); i++)
			televisors_[i] = object.televisors_[i];
#ifdef _DEBUG
		cout << endl << "Конструктор копирования. Класс ArrayTelevisor.\n";
		cout << "Всего существует " << ++count_ << " объектов\n";
#endif
	}

	//destructor
	ArrayTelevisor::~ArrayTelevisor() {

		if (this->name_)
		{
			delete[] this->name_;
			name_ = nullptr;
		}
		if (televisors_ != nullptr)
		{
			delete[] televisors_;
			televisors_ = nullptr;
		}
		

#ifdef _DEBUG
		cout << endl << "Деструктор. Класс ArrayTelevisor.\n";
		cout << "Всего существует " << --count_ << " объектов\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS
	// создание и заполнение динамического массива 
	int ArrayTelevisor::create(int n, const char* name)
	{
		if (n < 0)
			throw exception("\n ArrayTelevisor: Wrong index.");

		if (televisors_ != nullptr)
		{
			delete[] televisors_;
			televisors_ = nullptr;
		}
		
		size_ = n;
		// массив динамический - создание
		// Тип *имя = new  Тип[РазмерВЭлементах];
		televisors_ = new Televisor[n];
		setName(name);

		return 0;
	} // create

	void ArrayTelevisor::clear() {

		if (this->name_)
		{
			delete[] this->name_;
			name_ = nullptr;
		}

		if (televisors_ != nullptr)
		{
			delete[] televisors_;
			televisors_ = nullptr;
		}
		
	}//remove

	int ArrayTelevisor::setName(const char* name) {
		this->name_length_ = strlen(name);
		try {
			if (this->name_)
				delete[](*this).name_;
		}
		catch (exception ex)
		{
			throw exception("\n\t ArrayTelevisor:Cannot DELETE[] name.\n");
		}
		try {
			this->name_ = new char[this->name_length_ + 1];
		}
		catch (exception ex)
		{
			throw exception("\n\t ArrayTelevisor:No memory to NEW name.\n");
		}

		strcpy(this->name_, name);

		return 0;
	}

	int ArrayTelevisor::setSize(int size) {
		if (size < 0)
			throw exception("\n\t ArrayTelevisor:Wrong size.\n");

		this->size_ = size;

		return 0;
	}

#pragma endregion

	//GET
#pragma region ACCESSORS_GETTER
	char* ArrayTelevisor::getName() const {
		return this->name_;
	}

	int ArrayTelevisor::getNameLength() const {
		return this->name_length_;
	}

	int ArrayTelevisor::getSize() const {
		return this->size_;
	}


#pragma endregion

	//METHODS
#pragma region METHODS

	// чтение из текстового файла в объект
	void ArrayTelevisor::get(FILE* File)
	{
		// при достижении конце файла не читаем данные
		if (feof(File)) return;

		// строковые данные читаем fgets()
		//динамическая строка, для чтения из файл
		char* str = new char[1024];
		int i;

		//считываем по строчно информацию 
		fgets(str, 1024, File);
		//удаление символа новой строки у считываемой строки-имени
		i = (strlen(str) - 1);
		if (str[i] == '\n')
			str[i] = '\0';
		//		setName(str);

		int tmpNumberInt;
		if (!fscanf(File, "%d\n ", &tmpNumberInt))
			throw exception("\n Televisor: get() fscanf() error.\n");

		if (tmpNumberInt != (*this).size_)
		{
			this->clear();
			this->create(tmpNumberInt, str);
		}

		setName(str);

		delete[] str;

		for (int i = 0; i < size_; i++)
			televisors_[i].get(File);

	}

	// запись объекта в текстовый файл
	void ArrayTelevisor::put(FILE* File) const
	{
		// каждое поле класса записываем в отдельную строку
		fprintf(File, "%s\n", name_);
		fprintf(File, "%d\n", size_);

		for (int i = 0; i < size_; i++)
			televisors_[i].put(File);
	}

	char* ArrayTelevisor::toString() const
	{
		char* buf = new char[1024];
		sprintf(buf, "Name: %20s. Counts: %3d. \n", name_, size_);
		char* tmp = new char[strlen(buf) + 1];
		strcpy(tmp, buf);
		delete[] buf;

		return tmp;
	} // toString

#pragma region Sort
// televisors_ - массив для сортировки
// start - индекс начала части массива
// end   - индекс конца части массива
	void ArrayTelevisor::QuickSort(int start, int end, int compare(const Televisor& TV1, const Televisor& TV2)) {
		// условие завершения рекурсии
		if (start >= end) return;

		// начальные значения переменных на очередном вызове
		int i = start, j = end;              // для работы алгоритма
		int baseElement = start + (end - start) / 2; // расчет начального индекса середины массива

		// проходим по обрабатываемой части массива, элементы
		// меньшие базового помещаем в первую половину массива 
		// (до базового элемента), элементы бОльшие базового 
		// помещаем во вторую половину массива (после базового)
		while (i < j) {
			// середина - значение элемента в середине интервала
			// (базовый элемент)
			Televisor value(televisors_[baseElement]);  // !!! вызов копирующего конструктора !!!

			// движение от начала к середине, пока не найдем элемент => середины 
			// (бОльший базового)
			// while (i < baseElement && (array[i] <= value)) i++;
			while (i < baseElement && (compare(televisors_[i], value) <= 0)) i++;

			// движение от конца к середине, пока не найдем элемент <= середины
			// меньше базового
			// while (j > baseElement && (array[j] >= value)) j--;
			while (j > baseElement && (compare(televisors_[j], value) >= 0)) j--;

			// если это возможно, меням местами найденные элементы
			// бОльший --- базовый --- меньший ###>  меньший --- базовый --- бОльший
			if (i < j) {
				// меняем местами элементы в половинках массива
				//Swap(i, j);
				Televisor temp(televisors_[i]);
				televisors_[i] = televisors_[j];
				televisors_[j] = temp;


				// если слева дошли до середины - нет элементов для обмена
				// отодвигаем середину вправо, чтобы продолжать движение
				// по массиву
				if (i == baseElement) baseElement = j;

				// если справа дошли до середины - нет элементов для обмена
				// отодвигаем середину влево для продолжения движения
				else if (j == baseElement)  baseElement = i;
			} // if
		} // while

		// рекурсивный вызов в новых границах поиска
		QuickSort(start, baseElement, compare);        // от начала массива до cur
		QuickSort(baseElement + 1, end, compare);    // от cur+1 до конца массива
	} // QuickSort

	int ArrayTelevisor::CompareManufacturer(const Televisor& first, const Televisor& second)
	{
		return strcmp(first.getManufacturer(), second.getManufacturer());
	}

	int ArrayTelevisor::CompareModel(const Televisor& first, const Televisor& second)
	{
		return strcmp(first.getModel(), second.getModel());
	}

	int ArrayTelevisor::CompareSize(const Televisor& first, const Televisor& second)
	{
		int result = 0;

		if (first.getSize() > second.getSize())
			result = 1; // -1 для убывания
		else if (first.getSize() < second.getSize())
			result = -1; // 1 для убывания

		return result;
	}

	int ArrayTelevisor::CompareResolutionX(const Televisor& first, const Televisor& second)
	{
		return first.getResX() - second.getResX();
	}

	int ArrayTelevisor::CompareResolutionY(const Televisor& first, const Televisor& second)
	{
		return first.getResY() - second.getResY();
	}

	// для сортировки по убыванию - поменять знак у каждой единицы на противоположный
	int ArrayTelevisor::ComparePrice(const Televisor& first, const Televisor& second)
	{
		int result = 0;

		if (first.getPrice() > second.getPrice())
			result = 1; // -1 для убывания
		else if (first.getPrice() < second.getPrice())
			result = -1; // 1 для убывания

		return result;
	}

#pragma endregion

	// вывод данных в консоль
	void ArrayTelevisor::show(const char* title)
	{
		cout << title << fixed << setprecision(3) << endl
			<< "\t+———————+—————————————————+——————————————+—————————+————————+————————+———————————+\n"
			<< "\t| N п/п |  Производитель  | Модель       | Размер  | Разрешение (ШхВ)| Стоимость |\n"
			<< "\t+———————+—————————————————+——————————————+—————————+————————+————————+———————————+\n";

		for (int i = 0; i < size_; ++i) {
			cout << "\t| " << setw(5) << i << " | ";
			cout << setw(15) << televisors_[i].getManufacturer() << " | "
				<< setw(12) << televisors_[i].getModel() << " | "
				<< setw(7) << televisors_[i].getSize() << " | "
				<< setw(6) << televisors_[i].getResX() << " : "
				<< setw(6) << televisors_[i].getResY() << " | "
				<< setw(9) << televisors_[i].getPrice()
				;
			cout << " |\n";
		} // for i
		cout << "\t+———————+—————————————————+——————————————+—————————+————————+————————+———————————+\n"
			<< "\n\n\n";
	} // show

	// Запись массива persons в формате CSV в файл fileNameCsv
	void ArrayTelevisor::WriteToCsv(const char* fileNameCsv, const ArrayTelevisor* TVs) 
	{
		char buf[1024];

		FILE* File = fopen(fileNameCsv, "w");
		if (!File) {
			cout << endl << "File not opened.";
			sprintf(buf, "Файл \"%s\" не открыт для записи", fileNameCsv);
			throw exception(buf);
		}

		fprintf(File, "%s\n", TVs->getName());    // записать название 
		fprintf(File, "%d\n", TVs->getSize()); // записать количество элементов в массиве 

		for (int i = 0; i < TVs->getSize(); i++) {
			TVs->televisors_[i].toCsv(buf);
			fputs(buf, File);
		} // for i

		fclose(File);
	} // WriteToCsv

	// Чтение из файла в формате CSV fileNameCsv в массива persons 
	void ArrayTelevisor::ReadFromCsv(const char* fileNameCsv, ArrayTelevisor* TVs)
	{
		const int LEN_BUF(1024);
		char buf[LEN_BUF];

		FILE* File = fopen(fileNameCsv, "r");
		if (!File) {
			cout << endl << "File not opened.";
			sprintf(buf, "Файл \"%s\" не открыт для записи", fileNameCsv);
			throw exception(buf);
		}

		// чтение названия, убрать \n из строки 
		fgets(buf, LEN_BUF, File);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;

		// прочитать количество записей о членах клуба, выделить
		// память под новое количество, освободив занятую память
		int tmpInt;
		fscanf(File, "%d\n", &tmpInt);
//		fgets(buf, LEN_BUF, File);           // пустое чтение, забрать \n из строки

		if (TVs->getSize() != tmpInt) 
		{
			TVs->clear();
			TVs->create(tmpInt, buf);
		}

		// читать сами записи
		for (int i = 0; i < TVs->getSize(); i++) 
		{
			fgets(buf, LEN_BUF, File);
			if (feof(File)) break;

			TVs->televisors_[i].parseCsv(buf);
		} // for i

		fclose(File);
	} // ReadFromCsv


	// дозапись структуры person в файл в формате CSV, в массив структур persons
	void ArrayTelevisor::AppendToCsv(const char* fileNameCsv, const Televisor* TV)
	{
		const int LEN_BUF(1024);
		char buf[LEN_BUF];

		//ПЕРВОЕ ДЕЙСТВИЕ ДОБАВИМ ЭЛЕМЕНТ
		FILE* FileOld = fopen(fileNameCsv, "a");
		if (!FileOld) {
			cout << endl << "File not opened.";
			sprintf(buf, "Файл \"%s\" не открыт для записи", fileNameCsv);
			throw exception(buf);
		}

		TV->toCsv(buf);
		fputs(buf, FileOld);

		fclose(FileOld);

		//ВТОРОЕ ДЕЙСТВИЕ КОПИРОВАНИЕ ИСХОДНОГО ФАЙЛА ВО ВСПОМОГАТЕЛЬНЫЙ МЕНЯЯ КОЛИЧЕСТВО СОХРАНЕННЫХ ЭЛЕМЕНТОВ +1
		FileOld = fopen(fileNameCsv, "r");
		if (!FileOld) {
			cout << endl << "File not opened.";
			sprintf(buf, "Файл \"%s\" не открыт для записи", fileNameCsv);
			throw exception(buf);
		}

		//вспомогательный(результирующий) файл
		FILE* FileNew = fopen("tmpFile.txt", "r");//пробуем открыть, вдруг он уже есть
		if (!FileNew) 
		{
			FileNew = fopen("tmpFile.txt", "w");
			if (!FileNew) {
				cout << endl << "File not opened.";
				sprintf(buf, "Файл \"%s\" не открыт для записи", "tmpFile.txt");
				throw exception(buf);
			}
		}
		else
		{
			cout << endl << "File exist.";
			sprintf(buf, "Файл \"%s\" существует.", "tmpFile.txt");
			throw exception(buf);
		}
		
		//!!! ИЗ СТАРОГО ЧИАТЕМ В НОВЫЙ ЗАПИСУЕМ
		// чтение названия, убрать \n из строки 
		fgets(buf, LEN_BUF, FileOld);
		fputs(buf, FileNew);

		int tmpInt = 0;
		fscanf(FileOld, "%d\n", &tmpInt);
		tmpInt++;// количество записей должно быть на 1 больше!!!
		fprintf(FileNew, "%d\n", tmpInt); // записать количество элементов в массиве 

		// читать сами записи
		for (int i = 0; i < tmpInt; i++)
		{
			fgets(buf, LEN_BUF, FileOld);
			if (feof(FileOld)) break;

			fputs(buf, FileNew);
		} // for i

		fclose(FileOld);
		fclose(FileNew);

		//ТРЕТЬЕ ДЕЙСТВИЕ, УДАЛИМ СТАРЫЙ ФАЙЛ
		if (remove(fileNameCsv) != 0)
			cout << "Error deleting file.\n" << "Could not delete \"" << fileNameCsv << "\"" << endl;
		else
			cout << "File successfully deleted.\n" << "Delete \"" << fileNameCsv << "\"" << endl;

		//ЧЕТВЕРТОЕ ДЕЙСТВИЕ, ПЕРЕИМЕНУЕМ СОЗДАННЫЙ ФАЙЛ
		if (rename("tmpFile.txt", fileNameCsv) == 0)            // переименование файла
			cout << endl << "Файл успешно переименован";
		else
		{
			cout << endl << "Ошибка переименования файла.";
			sprintf(buf, "Файл \"%s\" небыл переименован в \"%s\".", "tmpFile.txt", fileNameCsv);
			throw exception(buf);
		}

	} // AppendToCsv

	// вывод данных в файл
	void ArrayTelevisor::writeToFile(FILE* File) const
	{
		// каждое поле класса записываем в отдельную строку
		fprintf(File, "%d\n", size_);

		for (int i = 0; i < size_; i++)
		{
			fprintf(File, "%20s\n%20s\n", televisors_[i].getManufacturer(), televisors_[i].getModel());
			fprintf(File, "%10.2lf %5d %5d %10.2lf\n", televisors_[i].getSize(), televisors_[i].getResX(), televisors_[i].getResY(), televisors_[i].getPrice());
		}
	}

	// Запись массива структур в бинарный файл fileNamePersons
	void ArrayTelevisor::WriteArrayToBin(const char* fileNamePersons)
	{
		const int N_LEN(1024);
		char buf[N_LEN];

		// Открыть бинарный файл для записи 
		FILE* File = fopen(fileNamePersons, "wb");
		if (!File) {
			cout << endl << "File not opened."; 
			sprintf(buf, "не могу открыть файл \"%s\" для записи", fileNamePersons);
			throw exception(buf);
		} // if
				
        //записываем данные нашего массива в бинарный файл
		int tmpInt;
		tmpInt = getNameLength();
		fwrite(&tmpInt, sizeof(tmpInt), 1, File);
		fwrite(getName(), sizeof(char)*getNameLength(), 1, File);
		tmpInt = getSize();
		fwrite(&tmpInt, sizeof(tmpInt), 1, File);

		// запись данных в файл и закрытие файла
		for (int i = 0; i < getSize(); i++)
			televisors_[i].Write(File);
		fclose(File);

	} // WriteArrayToBin


	// чтение данных из бинарного файла в массив объектов Person
	void ArrayTelevisor::ReadArrayFromBin(const char* fileNamePersons)
	{
		const int N_LEN(1024);
		char buf[N_LEN];

		// Открыть бинарный файл для чтения 
		FILE* File = fopen(fileNamePersons, "rb");
		if (!File) {
			cout << endl << "File not opened."; 
			sprintf(buf, "не могу открыть файл \"%s\" для чтения", fileNamePersons);
			throw exception(buf);
		} // if

		//считаем данные массива
		int tmpInt;
		fread(&tmpInt, sizeof(tmpInt), 1, File);
		fread(&buf, sizeof(char)*tmpInt, 1, File);
		buf[tmpInt] = '\0';
		fread(&tmpInt, sizeof(tmpInt), 1, File);

		// создание массива размера n, чтение данных из бинарного
	    // файла в элементы массива и закрытие файла
		clear();
		create(tmpInt,buf);
		
		
		for (int i = 0; i < getSize(); i++)
			televisors_[i].Read(File);
		fclose(File);

	} // ReadArrayFromBin


	// два метода доступа к массиву
	// чтение
	Televisor& ArrayTelevisor::at(int index) const
	{
		if ((index >= 0) && (index < size_))
			return televisors_[index];
		throw exception("\n ArrayTelevisor: Wrong index.");
	}

	// запись
	void ArrayTelevisor::put(int index, const Televisor& TV)
	{
		if (!((index >= 0) && (index < size_)))
			throw exception("\n ArrayTelevisor: Wrong index.");
		televisors_[index] = TV;
	} // put

#pragma endregion

	//метод поиска всех объектов с минимальным размером(диагональю)
	void ArrayTelevisor::showMinSize() 
	{
		int indexMin = 0;
		double minSize = televisors_[0].getSize();
		int cnt = 0;//количество минимальных
		double tmp_minSize;

		for(int i=1;i<getSize();i++)
			if (minSize >= (tmp_minSize=televisors_[i].getSize()))
			{
				if (minSize == tmp_minSize)
				{
					cnt++;//подсчет минимальных, пока не найден более минимальный
					continue;//к следующему объекту
				}
				cnt = 1;//первый найденный минимальный объект
				indexMin = i;
				minSize = tmp_minSize;
			}

		for (int i = 0; i < getSize(); i++)
			if (minSize == televisors_[i].getSize())
			{
				cout << televisors_[i].toString();
				if (--cnt == 0)break;
			}

		anyKey();
	}





#pragma region OPERATORS
	//**********************************

	ArrayTelevisor& ArrayTelevisor::operator=(const ArrayTelevisor& object)
	{
		if (&object == this) return *this;
		
		clear();
		create(object.getSize(), object.getName());

		for (int i = 0; i < size_; i++)
			televisors_[i] = object.televisors_[i];

#ifdef _DEBUG
		cout << endl << "Оператор присваивания. Класс ArrayTelevisor.\n";
		cout << "Всего существует " << count_ << " объектов\n";
#endif
		return *this;
	} // ArrayAutomobile::operator=

	// перегрузка операции индексирования
	Televisor& ArrayTelevisor::operator[](int index)
	{
		if (televisors_ == nullptr)
			throw exception("\n ArrayTelevisor: Not exist.");

		if (!((index >= 0) && (index < size_)))
			throw exception("\n ArrayTelevisor: Wrong index.");

		return televisors_[index];
	} // operator[]

	const char* ArrayTelevisor::operator[](const char* request)
	{
	static	char tmp_str[2000]{ 0 };

		if (!strcmp(request, "-help"))
		{
			strcpy(tmp_str, "This is easy way to take help.\n");
			return tmp_str;
		}
		if (!strcmp(request, "-size"))
		{
			char* buf = new char[10]{ 0 };
			_itoa(size_, buf, 10);
			strcpy(tmp_str, "Size: ");
			strcat(tmp_str, buf);
			strcat(tmp_str, ".\n");
			delete[] buf;
			return tmp_str;
		}
		if (!strcmp(request, "-name"))
		{
			strcpy(tmp_str, "Name: ");
			strcat(tmp_str, name_);
			strcat(tmp_str, ".\n");
			return tmp_str;
		}
		if (!strcmp(request, "\\?"))
		{
			strcpy(tmp_str, "Write \"-help\" to know more.\nWrite \"-size\" to take size of array.\nWrite \"-name\" to know name of array.\n");
			return tmp_str;
		}

		return "request not find? try \"\\?\"\n";
	}

#pragma endregion

#pragma endregion

	
	void TestClassArrayTelevisor() {

		cls();

		// Установим актуальный заголовок окна
		SetConsoleTitle(title);
		// Установим актуальный заголовок окна
		myAddConsoleTitle(L" Тестирование Класса ArrayTelevisor ");

		TV my_TV[20] = {
			{"LG","34UM61",34,2560,1080,8500},
			{"SAMSUNG","S22B350",22,1920,1280,1300},
			{"FLATRON","QL977",19,800,640,700},
			{"SONY","uM710",17,640,480,500},
			{"BENQ","Q22",22,1600,900,1500},
			{"SIEMENS","s7B22",22,1280,920,8500},
			{"HORIZONT","20100",20,800,640,1350},
			{"POLAR","S7s11",17,640,480,3500},
			{"ECON","5 series",27,1280,900,2500},
			{"JVC","007",26,1280,900,4900},
			{"BBK","_7",17,1920,1280,2500},
			{"TCL","560_",25,1920,1280,2100},
			{"TOSHIBA","cbr_01",36,2560,1920,3450},
			{"AKAI","7s",17,1920,1600,1950},
			{"DIGMA","Q10",26,1280,900,2970},
			{"LG","25UM51",25,2560,1080,2650},
			{"SAMSUNG","22C450",22,1280,1080,5900},
			{"SIEMENS","jx008",15,800,640,2500},
			{"VEKTA","vV09",19,800,640,3560},
			{"TELEFUNKEN","_fFF",31,1280,900,9500},
		};


		coutColor("\nСоздадим 4e отдельных объекта\n", wAttributeSpecial);

		int size_TVs = 5;
		Televisor* TVs = new Televisor[size_TVs];

		//		ArrayTelevisor c1;
		coutColor("\nНабор №2.\n", wAttributeSpecial);
		ArrayTelevisor c2(5, "FirstTVsList");
		coutColor("\nНабор №3.\n", wAttributeSpecial);
		ArrayTelevisor c3(TVs, size_TVs, "SecondTVsList");
		coutColor("\nНабор №4.\n", wAttributeSpecial);
		ArrayTelevisor c4 = c2;
		coutColor("\nНабор №5.\n", wAttributeSpecial);
		ArrayTelevisor c5 = c3;

		anyKey();

		//************************

		coutColor("\nПокажем наши объекты.\n", wAttributeSpecial);
		cout << c2.toString();
		cout << c3.toString();
		cout << c4.toString();
		cout << c5.toString();

		c2.show(c2.getName());
		c3.show(c3.getName());
		c4.show(c4.getName());
		c5.show(c5.getName());


		anyKey();

		//************************
		coutColor("\nПоработаем с объектом №4\n", wAttributeSpecial);
		c4.clear();
		c4.create(20, "NewTVsList");
		cout << "\nПроинициализируем объект новыми данными: \n" << c4.toString();

		c4.setName("SuperTVsList");
		cout << "\nУкажем новое имя: \n" << c4.toString();

		for (int i = 0; i < c4.getSize(); i++)
			c4[i].setConstructor(my_TV[genRand(0, 19)]);

		coutColor("\nЗапросим все поля объекта с использованием геттеров\n", wAttributeSpecial);
		//get
		cout << "\nПосмотрим имя списка: " << c4.getName();
		cout << "\nПосмотрим длинну имени списка: " << c4.getNameLength();

		cout << "\nПосмотрим количество телевизоров в нем: " << c4.getSize();

		anyKey();

		//*************************
		coutColor("\nНабор №2.\n", wAttributeSpecial);
		c2.show(c2.getName());
		coutColor("\nНабор №3.\n", wAttributeSpecial);
		c3.show(c3.getName());
		coutColor("\nНабор №4.\n", wAttributeSpecial);
		c4.show(c4.getName());
		coutColor("\nНабор №5.\n", wAttributeSpecial);
		c5.show(c5.getName());


		anyKey();

		//*************************
		FILE* File = fopen("testArrayTelevisor.txt", "w");
		if (!File) {
			cout << endl << "File not created.";
			throw exception("\n\tFile not created.\n");
		}

		coutColor("\nЗаписали в файл\n", wAttributeSpecial);
		c2.put(File);
		c3.put(File);
		c4.put(File);
		c5.put(File);

		fclose(File);

		File = fopen("testArrayTelevisor.txt", "r");
		if (!File) {
			cout << endl << "File not opened.";
			throw exception("\n\tFile not opened.\n");
		}

		coutColor("\nСчитали из файла в обратном порядке\n", wAttributeSpecial);
		c5.get(File);
		c4.get(File);
		c3.get(File);
		c2.get(File);

		//выведем информацию о существующих объектов в массиве
		cout << c2.toString();
		cout << c3.toString();
		cout << c4.toString();
		cout << c5.toString();

		fclose(File);

		//*************************
		coutColor("\nНабор №2.\n", wAttributeSpecial);
		c2.show(c2.getName());
		coutColor("\nНабор №3.\n", wAttributeSpecial);
		c3.show(c3.getName());
		coutColor("\nНабор №4.\n", wAttributeSpecial);
		c4.show(c4.getName());
		coutColor("\nНабор №5.\n", wAttributeSpecial);
		c5.show(c5.getName());

		anyKey();
			   		 
		//*************************

		coutColor("\nПроверим методы работы с .csv файлами.\n", wAttributeSpecial);

		coutColor("\nНабор №3(исходный).\n", wAttributeSpecial);
		c3.show(c3.getName());
		ArrayTelevisor::WriteToCsv("testArrayTelevisor.csv",&c3) ;

		ArrayTelevisor::ReadFromCsv("testArrayTelevisor.csv",&c3);
		coutColor("\nНабор №3(считанный из файла).\n", wAttributeSpecial);
		c3.show(c3.getName());

		ArrayTelevisor::AppendToCsv("testArrayTelevisor.csv", &c3[0]);
		coutColor("\nНабор №3(добавили элемент в файл).\n", wAttributeSpecial);
		c3.show(c3.getName());

		ArrayTelevisor::ReadFromCsv("testArrayTelevisor.csv", &c3);
		coutColor("\nНабор №3(считали из файла).\n", wAttributeSpecial);
		c3.show(c3.getName());

		File = fopen("ArrayTelevisor.txt", "w");
		if (!File) {
			cout << endl << "File not created.";
			throw exception("\n\tFile not created.\n");
		}

		coutColor("\nЗаписали в файл ArrayTelevisor.txt\n", wAttributeSpecial);
		c4.writeToFile(File);

		fclose(File);
		anyKey();

		//*************************

		coutColor("\nПроверим методы put() и  at() для объекта №3.\n", wAttributeSpecial);

		for (int i = 0; i < c3.getSize(); i++)
			cout << c3.at(i).toString();
		coutColor("\nСписок №3.\n", wAttributeSpecial);
		c3.show(c3.getName());

		c5 = c3;
		coutColor("\nСписок №5.\n", wAttributeSpecial);
		c5.show(c5.getName());

		for (int i = 0; i < c3.getSize(); i++)
		{
			Televisor new_TV;
			new_TV.setConstructor(my_TV[genRand(0, 19)]);
			c3.put(i, new_TV);
		}
		coutColor("\nСписок №3.\n", wAttributeSpecial);
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\nЛист №3.(до сортировки)\n", wAttributeSpecial);
		c3.show(c3.getName());

		coutColor("\nЛист №3.(сортировка по размеру)\n", wAttributeSpecial);
		c3.OrderBySize();
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\nЛист №3.(сортировка по разрешению оси Х)\n", wAttributeSpecial);
		c3.OrderByResolutionX();
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\nЛист №3.(сортировка по разрешению по оси Y)\n", wAttributeSpecial);
		c3.OrderByResolutionY();
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\nЛист №3.(сортировка по цене)\n", wAttributeSpecial);
		c3.OrderByPrice();
		c3.show(c3.getName());

		anyKey();

		//*************************
		coutColor("\nЛист №3. Применим фильтр по производителю. \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3, 4, GET_MANUFACTURER, c3[5].getManufacturer(), c3[7].getManufacturer(), c3[7].getManufacturer());
		c3.show(c3.getName());

		coutColor("\nЛист №3. Применим фильтр по цене(от 2500. до 3000.). \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3,1,GET_PRICE);
		c3.show(c3.getName());

		coutColor("\nЛист №3. Применим фильтр по цене(от 2500. до 3000.) и по размеру(от 25. до 30.). \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3, 2, GET_PRICE, GET_SIZE);
		c3.show(c3.getName());

		coutColor("\nЛист №3. Применим фильтр по модели и по размеру имени модели(от 5 до 10). \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3, 3, GET_MODEL, c3[5].getModel(), GET_MODEL_LENGTH);
		c3.show(c3.getName());

		anyKey();

		//*************************
		coutColor("\nПроверим методы << и  >> для объекта №4.\n", wAttributeSpecial);

		coutColor("\nГараж под №4.(до ввода данных)\n", wAttributeSpecial);
		c4.show(c4.getName());

//		cin >> c4[0];
		//for (int i = 0; i < c4.getSize(); i++)
		//{
		//	cin >> c4[i];
		//}

		for (int i = 0; i < c4.getSize(); i++)
		{
			cout << c4[i];
		}



		coutColor("\nСписок №4.(после инициализации)\n", wAttributeSpecial);
		c4.show(c4.getName());


		anyKey();

		//*************************

		coutColor("\nПроверим перегрузку [] для объекта №3.\n", wAttributeSpecial);

		for (int i = 0; i < c3.getSize(); i++)
			cout << c3[i].toString();

		cout << c3["-help"];
		cout << c3["\\?"];
		cout << c3["-size"];
		cout << c3["-name"];
		cout << c3["-super"];


		anyKey();

		//*************************

		cls();

	}


	inline void menuVisio() {
		//ждем нажатия любой клавиши
		//анализируем полученные результаты
		anyKey(0, 26);

		//установим курсор в нужную позицию
		setCursorPosition(0, 26);

		//произведем очистку области под новую информацию
		placeClear(0, 26, 300, 123);
	}


	void Exercises()
	{

		try
		{
			cls();

			// Установим актуальный заголовок окна
			SetConsoleTitle(title);
			// Установим актуальный заголовок окна
			myAddConsoleTitle(L" Задание ");

			//переместим курсор в заданную позицию
			setCursorPosition(0, 1);
			Line(124, '*');
			//произведем очиистку заданного места под вывод результатов нашей работы
			placeClear(0, 0, 40, 123);
			//укажем задачу над которой сейчас работаем

			coutColor("\n\t\tНапишите консольное приложение для решения задачи по теме \"ООП C++\".\n\t\
\tСоздать проект для решения задачи.Разработать класс по заданию.В классе разработать :  \n\t\
- Конструкторы : по умолчанию, с параметрами, копирующий, деструктор                     \n\t\
- Геттеры и сеттеры для всех полей класса                                                \n\t\
- Перегрузка операций ввода, вывода                                                      \n\t\
- Методы ввода из текстового файла(каждый параметр занимает одну строку файла) и вывода  \n\t\
в текстовый	файл                                                                         \n\t\
\tВ функции main() создать динамический массив из объектов класса(не менее 10 элементов),\n\t\
вызвать все методы класса для демонстрации их работы, записать объекты в текстовый файл, \n\t\
прочитать объекты из текстового файла, первая строка файла – количество записей в файле. \n\t\
Комментирование кода – обязательное условие.                                             \n\t\
                                                                                         \n\t\
                                                                                         \n\t\
\tКласс Телевизор с полями для хранения                                                  \n\t\
- производителя и типа телевизора,                                                       \n\t\
- диагональ экрана,                                                                      \n\t\
- разрешения по вертикали,                                                               \n\t\
- разрешения по горизонтали,                                                             \n\t\
- цена.                                                                                  \n\t\
В массиве объектов определить телевизоры с минимальной диагональю, упорядочить массив по \n\t\
убыванию производителя и типа телевизора – быстрая сортировка.                           \n\t\
\n", wAttributeSpecial);

			//отделим задачу от решения *************************
			Line(124, '*');

			menuVisio();

			TV my_TV[20] = {
			{"LG","34UM61",34,2560,1080,8500},
			{"SAMSUNG","S22B350",22,1920,1280,1300},
			{"FLATRON","QL977",19,800,640,700},
			{"SONY","uM710",17,640,480,500},
			{"BENQ","Q22",22,1600,900,1500},
			{"SIEMENS","s7B22",22,1280,920,8500},
			{"HORIZONT","20100",20,800,640,1350},
			{"POLAR","S7s11",17,640,480,3500},
			{"ECON","5 series",27,1280,900,2500},
			{"JVC","007",26,1280,900,4900},
			{"BBK","_7",17,1920,1280,2500},
			{"TCL","560_",25,1920,1280,2100},
			{"TOSHIBA","cbr_01",36,2560,1920,3450},
			{"AKAI","7s",17,1920,1600,1950},
			{"DIGMA","Q10",26,1280,900,2970},
			{"LG","25UM51",25,2560,1080,2650},
			{"SAMSUNG","22C450",22,1280,1080,5900},
			{"SIEMENS","jx008",15,800,640,2500},
			{"VEKTA","vV09",19,800,640,3560},
			{"TELEFUNKEN","_fFF",31,1280,900,9500},
			};

			int N = 10;

			// СОЗДАНИЕ
			coutColor("\nСоздадим массив объектов.\n", wAttributeSpecial);

			ArrayTelevisor TVs(10, "FirstTVsList");

			menuVisio();

//Продублируем результаты без лишней информации
			coutColor("\nСоздадим массив объектов.\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			// ИНИЦИАЛИЗАЦИЯ
			coutColor("\nИнициализируем массив объектов используя перегрузку оператора присваивания\n", wAttributeSpecial);

			for (int i = 0; i < TVs.getSize(); i++)
				TVs[i].setConstructor(my_TV[genRand(0, 19)]);

			//*************************
			FILE* File = fopen("ArrayTelevisor.txt", "w");
			if (!File) {
				cout << endl << "File not created.";
				throw exception("\n\tFile not created.\n");
			}

			// ЗАПИСЬ В ФАЙЛ 
			coutColor("\nЗаписали в файл ArrayTelevisor.txt\n", wAttributeSpecial);
			TVs.writeToFile(File);

			fclose(File);

			menuVisio();

			//*************************

// ЗАПИСЬ И СЧИТЫВАНИЕ В ФАЙЛ В ФОРМАТЕ .csv 

			coutColor("\nНабор №3(запись в файл).\n", wAttributeSpecial);
			ArrayTelevisor::WriteToCsv("testArrayTelevisor.csv", &TVs);

			coutColor("\nНабор №3(добавили элемент в файл).\n", wAttributeSpecial);
			ArrayTelevisor::AppendToCsv("testArrayTelevisor.csv", &TVs[0]);

			coutColor("\nНабор №3(считанный из файла).\n", wAttributeSpecial);
			ArrayTelevisor::ReadFromCsv("testArrayTelevisor.csv", &TVs);

			// ВЫВОД В КОНСОЛЬ
			TVs.show(TVs.getName());

			menuVisio();

			//Продублируем результаты без лишней информации
			coutColor("\nНабор №3(считанный из файла c добавленным элементом).\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			//*************************
						
// ЗАПИСЬ И СЧИТЫВАНИЕ В БИНАРНЫЙ ФАЙЛ 

			coutColor("\nНабор №3(запись в бинарный файл).\n", wAttributeSpecial);
			TVs.WriteArrayToBin("testArrayTelevisor.bin");
			
			coutColor("\nНабор №3(считанный из бинарного файла).\n", wAttributeSpecial);
			TVs.ReadArrayFromBin("testArrayTelevisor.bin");
						
			// ВЫВОД В КОНСОЛЬ
			TVs.show(TVs.getName());

			menuVisio();

			//Продублируем результаты без лишней информации
			coutColor("\nНабор №3(считанный из бинарного файла).\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

// ДОСТУП К ОБЪЕКТАМ С ПОМОЩЬЮ ПЕРЕГРУЗКИ ОПЕРАЦИИ ИНДЕКСИРОВАНИЯ [ ]
			coutColor("\nПроверим перегрузку [] для объекта.\n", wAttributeSpecial);

			for (int i = 0; i < TVs.getSize(); i++)
				cout << TVs[i].toString();


			menuVisio();
			
			//*************************
//СОРТИРОВКА
			coutColor("\nCортировка по производителю.\n", wAttributeSpecial);
			TVs.OrderByManufacturer();
			TVs.show(TVs.getName());

			menuVisio();

//Продублируем результаты без лишней информации
			coutColor("\nCортировка по производителю.\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			//*************************

			coutColor("\nCортировка по модели.\n", wAttributeSpecial);
			TVs.OrderByModel();
			TVs.show(TVs.getName());

			menuVisio();

//Продублируем результаты без лишней информации
			coutColor("\nCортировка по модели.\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			//*************************
//ФИЛЬТР
			coutColor("\nПрименим фильтр по цене(от 2500. до 3000.) и по размеру(от 25. до 30.). \n", wAttributeSpecial);
			ArrayTelevisor::showFilter(&TVs, 2, GET_PRICE, GET_SIZE);
			TVs.show(TVs.getName());

			menuVisio();

			//*************************

			coutColor("\nПрименим фильтр по производителю(под индексом 5 и 7) и по модели(под индексом 5 и 7). \n", wAttributeSpecial);
			ArrayTelevisor::showFilter(&TVs, 8, GET_MANUFACTURER, TVs[5].getManufacturer(), TVs[7].getManufacturer(), TVs[7].getManufacturer(),GET_MODEL, TVs[5].getModel(), TVs[7].getModel(), TVs[7].getModel());
			TVs.show(TVs.getName());

			menuVisio();
			
			//*************************
//ПОИСК ОБЪЕКТОВ С МИНИМАЛЬНОЙ ДИАГОНАЛЬЮ(РАЗМЕРОМ)
			coutColor("\nВыведем все объекты с минимальной диагональю.\n", wAttributeSpecial);
			TVs.showMinSize();

			coutColor("\nИсходный массив.\n", wAttributeSpecial);
			TVs.show(TVs.getName());

			menuVisio();

			//*************************

			cls();

			//throw exception(" "); // генерирование исключения
		}
		catch (exception ex) {  // обработка исключения

			//переместим курсор в заданную позицию
			setCursorPosition(0, 0);
			//произведем очистку области под новую информацию
			placeClear(0, 0, 80, 123);


			SetConsoleTextAttribute(hStdOut, wAttributeWarning);
			cout << "\n\n"
				<< "\t\t                                                       \n"
				<< "\t\t    [Ошибка(уровень задачи)]                           \n"
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

}

