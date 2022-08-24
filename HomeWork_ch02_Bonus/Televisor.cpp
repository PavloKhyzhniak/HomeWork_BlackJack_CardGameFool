
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

	//�������������� ����������� ����������-������� ��������� ��������
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
		os << "\n�������������: " << setw(20) << object.manufacturer_
			<< "\n������: " << setw(10) << object.model_
			<< "\n������: " << setw(10) << fixed << setprecision(2) << object.size_
			<< "\n����������(���): " << setw(5) << object.resX_
			<< " : " << setw(5) << object.resY_
			<< "\n����,$: " << setw(10) << fixed << setprecision(2) << object.price_
			;

		return os;
	}

	std::istream& operator>>(std::istream& is, Televisor& object)
	{
		int tmpInt;
		int tmpInt2;
		double tmpDouble;

		//���� �� ��������� ����� ������
		char* name = new char[100]{ 0 };
		setValue<char*>(is, &name, "�������������: ");
		object.setManufacturer(name);

		setValue<char*>(is, &name, "������: ");
		object.setModel(name);
		delete[] name;

		
		setValue<double>(is, &tmpDouble, "������: ", [](const double* const k) {return(((*k > 0.) && (*k <= 1000.)) ? true : false); });
		object.setSize(tmpDouble);

		setValue<int>(is, &tmpInt, "���������� �� ��� X: ", [](const int* const k) {return(((*k >= 640) && (*k <= 40000)) ? true : false); });
		setValue<int>(is, &tmpInt2, "���������� �� ��� Y: ", [](const int* const k) {return(((*k >= 480) && (*k <= 4000)) ? true : false); });
		object.setResolution(tmpInt,tmpInt2);

		setValue<double>(is, &tmpDouble, "����, $: ", [](const double* const k) {return((*k >= 0.) ? true : false); });
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
		cout << endl << "����������� �� ���������(��� ����������). ����� Televisor.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
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
		cout << endl << "����������� � �����������. ����� Televisor.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
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
		cout << endl << "����������� �����������. ����� Televisor.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
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
		cout << endl << "����������. ����� Televisor.\n";
		cout << "����� ���������� " << --count_ << " ��������\n";

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

	// ������ �� ���������� ����� � ������
	void Televisor::get(FILE* File)
	{
		// ��� ���������� ����� ����� �� ������ ������
		if (feof(File)) return;

		// ��������� ������ ������ fgets()
		//������������ ������, ��� ������ �� ����
		char* str = new char[2024];
		int i;

		//��������� �� ������� ���������� 
		fgets(str, 2024, File);
		//�������� ������� ����� ������ � ����������� ������-�����
		i = (strlen(str) - 1);
		if (str[i] == '\n')
			str[i] = '\0';
		setManufacturer(str);

		//��������� �� ������� ���������� 
		fgets(str, 1024, File);
		//�������� ������� ����� ������ � ����������� ������-�����
		i = (strlen(str) - 1);
		if (str[i] == '\n')
			str[i] = '\0';
		setModel(str);

		delete[] str;

		// �������� ������ ��������� ��������� ������ � ���������
		// ������� ������ ����� ������ ���������� �����

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

	// ������ ������� � ��������� ����
	void Televisor::put(FILE* File) const
	{
		// ������ ���� ������ ���������� � ��������� ������
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

	// ����������/������ � ������ ������� CSV - ��� ���� �
	// ����� ������, ���� �������� ���� �� ����� �������� ';'
	void Televisor::toCsv(char* str) const {
		sprintf(str, "%s;%s;%.2lf;%d;%d;%.2lf\n", manufacturer_, model_, size_, resX_, resY_, price_);
	} // toCsv

	// ��������� ������ � ������� CSV �� ���� ������
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


//	// ����������/������ � ������ ������� CSV - ��� ���� �
//	// ����� ������, ���� �������� ���� �� ����� �������� ';'
//	void Televisor::toCsvBIN(char* str) const {
//		fwrite(&tmp, sizeof(int), 1, File);
//		sprintf(str, "%d;%s;%d;%s;%.2lf;%d;%d;%.2lf\n", manufacturer_length_, manufacturer_, model_length_, model_, size_, resX_, resY_, price_);
//	} // toCsv


	// ����������/������ � �������� ����
	void Televisor::Write(FILE* File) const
	{		
		//���������� ������ ������ ������� � �������� ����
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

	// ������ �� ��������� ����� � ���� ������
	void Televisor::Read(FILE* File)
	{
		const int N_LEN(1024);
		char buf[N_LEN];

		//������� ������ �������
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
		cout << endl << "�������� ������������. ����� Televisor.\n";
		cout << "����� ���������� " << count_ << " ��������\n";
#endif
		return *this;
	} // Televisor::operator=

#pragma endregion

#pragma endregion


	void TestClassTelevisor() {

		cls();

		// ��������� ���������� ��������� ����
		SetConsoleTitle(title);
		// ��������� ���������� ��������� ����
		myAddConsoleTitle(L" ������������ ������ Televisor ");

		coutColor("\n�������� ��� ��������� �������\n", wAttributeSpecial);


		Televisor c1;
		Televisor c2("LG", "25UM61", 25, 2560, 1080, 800.);
		Televisor c3 = c2;

		coutColor("\n������� ���� �������.\n", wAttributeSpecial);
		cout << c1.toString();
		cout << c2.toString();
		cout << c3.toString();

		//************************
		coutColor("\n���������� � �������� �3\n", wAttributeSpecial);
		c3.setConstructor("LG", "34UM61", 34, 2560, 1060, 950.);
		cout << "\n����������������� ������ ������ �������: \n" << c3.toString();

		c3.setManufacturer("SAMSUNG");
		cout << "\n������ ������ �������������: \n" << c3.toString();
		c3.setModel("S22B350");
		cout << "\n������ ����� ������: \n" << c3.toString();

		c3.setSize(22);
		cout << "\n������ ����� ������: \n" << c3.toString();
		c3.setResolution(1920,1280);
		cout << "\n������ ����� ����������: \n" << c3.toString();
		c3.setPrice(1020.);
		cout << "\n������ ����� ����: \n" << c3.toString();


		coutColor("\n�������� ��� ���� ������� � �������������� ��������\n", wAttributeSpecial);
		//get
		cout << "\n��������� �������������: " << c3.getManufacturer();
		cout << "\n��������� ������ ����� �������������: " << c3.getManufacturerLength();

		cout << "\n��������� ������: " << c3.getModel();
		cout << "\n��������� ������ ����� ������: " << c3.getModelLength();

		cout << "\n��������� ������ ��������: " << c3.getSize();
		cout << "\n��������� ��� ���������� �� ��� X: " << c3.getResX();
		cout << "\n��������� ��� ���������� �� ��� Y: " << c3.getResY();
		cout << "\n��������� ����: " << c3.getPrice();

		anyKey();

		//*************************
		FILE* File = fopen("testTelevisor.txt", "w");
		if (!File) {
			cout << endl << "File not created.";
			throw exception("\n\tFile not created.\n");
		}

		coutColor("\n�������� � ����\n", wAttributeSpecial);
		c1.put(File);
		c2.put(File);
		c3.put(File);

		fclose(File);

		File = fopen("testTelevisor.txt", "r");
		if (!File) {
			cout << endl << "File not opened.";
			throw exception("\n\tFile not opened.\n");
		}

		coutColor("\n������� �� ����� � �������� �������\n", wAttributeSpecial);
		c3.get(File);
		c2.get(File);
		c1.get(File);

		//������� ���������� � ������������ �������� � �������
		cout << c1.toString();
		cout << c2.toString();
		cout << c3.toString();

		fclose(File);

		anyKey();

		//*************************
		coutColor("\n�������� ����� ������� ������(��������� �������������).\n", wAttributeSpecial);
		//������� ���������� � ������������ �������� � �������
		cout <<endl << "������ � 1: "<< boolalpha <<c1.IsEmpty();
		cout <<endl << "������ � 2: "<< boolalpha <<c2.IsEmpty();
		cout <<endl << "������ � 3: "<< boolalpha <<c3.IsEmpty();
		cout << noboolalpha;
		anyKey();

		//*************************

		coutColor("\n������������ ���������� ���������� �����\\������\n", wAttributeSpecial);
		cout << "������� ���������� �� ������� � 3 � ������ ���������� � ������ � 2.\n";
		cout << c3 << endl;
//		cin >> c2;

		coutColor("\n�������� ���������� ����� ��������\n", wAttributeSpecial);
		//������� ���������� � ������������ �������� � �������
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
	//�������������� ����������� ����������-������� ��������� ��������
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
		// ������ ������������ - ��������
		// ��� *��� = new  ���[����������������];
		televisors_ = new Televisor[size];
		setName(name);

#ifdef _DEBUG
		cout << endl << "����������� � �����������. ����� ArrayTelevisor.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	ArrayTelevisor::ArrayTelevisor(Televisor* TVs, int size, const char* name)
		: televisors_(TVs),
		size_(size),
		name_{ nullptr }
	{
		setName(name);

#ifdef _DEBUG
		cout << endl << "����������� � �����������(����� ������� ������). ����� ArrayTelevisor.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
#endif
	}

	ArrayTelevisor::ArrayTelevisor(const ArrayTelevisor& object)
		:name_{ nullptr }
	{
		create(object.getSize(), object.getName());

		for (int i = 0; i < getSize(); i++)
			televisors_[i] = object.televisors_[i];
#ifdef _DEBUG
		cout << endl << "����������� �����������. ����� ArrayTelevisor.\n";
		cout << "����� ���������� " << ++count_ << " ��������\n";
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
		cout << endl << "����������. ����� ArrayTelevisor.\n";
		cout << "����� ���������� " << --count_ << " ��������\n";

		if (count_ == 0) _getch();
#endif
	}

#pragma endregion

	//SET
#pragma region MUTATORS_SETTERS
	// �������� � ���������� ������������� ������� 
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
		// ������ ������������ - ��������
		// ��� *��� = new  ���[����������������];
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

	// ������ �� ���������� ����� � ������
	void ArrayTelevisor::get(FILE* File)
	{
		// ��� ���������� ����� ����� �� ������ ������
		if (feof(File)) return;

		// ��������� ������ ������ fgets()
		//������������ ������, ��� ������ �� ����
		char* str = new char[1024];
		int i;

		//��������� �� ������� ���������� 
		fgets(str, 1024, File);
		//�������� ������� ����� ������ � ����������� ������-�����
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

	// ������ ������� � ��������� ����
	void ArrayTelevisor::put(FILE* File) const
	{
		// ������ ���� ������ ���������� � ��������� ������
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
// televisors_ - ������ ��� ����������
// start - ������ ������ ����� �������
// end   - ������ ����� ����� �������
	void ArrayTelevisor::QuickSort(int start, int end, int compare(const Televisor& TV1, const Televisor& TV2)) {
		// ������� ���������� ��������
		if (start >= end) return;

		// ��������� �������� ���������� �� ��������� ������
		int i = start, j = end;              // ��� ������ ���������
		int baseElement = start + (end - start) / 2; // ������ ���������� ������� �������� �������

		// �������� �� �������������� ����� �������, ��������
		// ������� �������� �������� � ������ �������� ������� 
		// (�� �������� ��������), �������� ������� �������� 
		// �������� �� ������ �������� ������� (����� ��������)
		while (i < j) {
			// �������� - �������� �������� � �������� ���������
			// (������� �������)
			Televisor value(televisors_[baseElement]);  // !!! ����� ����������� ������������ !!!

			// �������� �� ������ � ��������, ���� �� ������ ������� => �������� 
			// (������� ��������)
			// while (i < baseElement && (array[i] <= value)) i++;
			while (i < baseElement && (compare(televisors_[i], value) <= 0)) i++;

			// �������� �� ����� � ��������, ���� �� ������ ������� <= ��������
			// ������ ��������
			// while (j > baseElement && (array[j] >= value)) j--;
			while (j > baseElement && (compare(televisors_[j], value) >= 0)) j--;

			// ���� ��� ��������, ����� ������� ��������� ��������
			// ������� --- ������� --- ������� ###>  ������� --- ������� --- �������
			if (i < j) {
				// ������ ������� �������� � ���������� �������
				//Swap(i, j);
				Televisor temp(televisors_[i]);
				televisors_[i] = televisors_[j];
				televisors_[j] = temp;


				// ���� ����� ����� �� �������� - ��� ��������� ��� ������
				// ���������� �������� ������, ����� ���������� ��������
				// �� �������
				if (i == baseElement) baseElement = j;

				// ���� ������ ����� �� �������� - ��� ��������� ��� ������
				// ���������� �������� ����� ��� ����������� ��������
				else if (j == baseElement)  baseElement = i;
			} // if
		} // while

		// ����������� ����� � ����� �������� ������
		QuickSort(start, baseElement, compare);        // �� ������ ������� �� cur
		QuickSort(baseElement + 1, end, compare);    // �� cur+1 �� ����� �������
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
			result = 1; // -1 ��� ��������
		else if (first.getSize() < second.getSize())
			result = -1; // 1 ��� ��������

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

	// ��� ���������� �� �������� - �������� ���� � ������ ������� �� ���������������
	int ArrayTelevisor::ComparePrice(const Televisor& first, const Televisor& second)
	{
		int result = 0;

		if (first.getPrice() > second.getPrice())
			result = 1; // -1 ��� ��������
		else if (first.getPrice() < second.getPrice())
			result = -1; // 1 ��� ��������

		return result;
	}

#pragma endregion

	// ����� ������ � �������
	void ArrayTelevisor::show(const char* title)
	{
		cout << title << fixed << setprecision(3) << endl
			<< "\t+�������+�����������������+��������������+���������+��������+��������+�����������+\n"
			<< "\t| N �/� |  �������������  | ������       | ������  | ���������� (���)| ��������� |\n"
			<< "\t+�������+�����������������+��������������+���������+��������+��������+�����������+\n";

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
		cout << "\t+�������+�����������������+��������������+���������+��������+��������+�����������+\n"
			<< "\n\n\n";
	} // show

	// ������ ������� persons � ������� CSV � ���� fileNameCsv
	void ArrayTelevisor::WriteToCsv(const char* fileNameCsv, const ArrayTelevisor* TVs) 
	{
		char buf[1024];

		FILE* File = fopen(fileNameCsv, "w");
		if (!File) {
			cout << endl << "File not opened.";
			sprintf(buf, "���� \"%s\" �� ������ ��� ������", fileNameCsv);
			throw exception(buf);
		}

		fprintf(File, "%s\n", TVs->getName());    // �������� �������� 
		fprintf(File, "%d\n", TVs->getSize()); // �������� ���������� ��������� � ������� 

		for (int i = 0; i < TVs->getSize(); i++) {
			TVs->televisors_[i].toCsv(buf);
			fputs(buf, File);
		} // for i

		fclose(File);
	} // WriteToCsv

	// ������ �� ����� � ������� CSV fileNameCsv � ������� persons 
	void ArrayTelevisor::ReadFromCsv(const char* fileNameCsv, ArrayTelevisor* TVs)
	{
		const int LEN_BUF(1024);
		char buf[LEN_BUF];

		FILE* File = fopen(fileNameCsv, "r");
		if (!File) {
			cout << endl << "File not opened.";
			sprintf(buf, "���� \"%s\" �� ������ ��� ������", fileNameCsv);
			throw exception(buf);
		}

		// ������ ��������, ������ \n �� ������ 
		fgets(buf, LEN_BUF, File);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;

		// ��������� ���������� ������� � ������ �����, ��������
		// ������ ��� ����� ����������, ��������� ������� ������
		int tmpInt;
		fscanf(File, "%d\n", &tmpInt);
//		fgets(buf, LEN_BUF, File);           // ������ ������, ������� \n �� ������

		if (TVs->getSize() != tmpInt) 
		{
			TVs->clear();
			TVs->create(tmpInt, buf);
		}

		// ������ ���� ������
		for (int i = 0; i < TVs->getSize(); i++) 
		{
			fgets(buf, LEN_BUF, File);
			if (feof(File)) break;

			TVs->televisors_[i].parseCsv(buf);
		} // for i

		fclose(File);
	} // ReadFromCsv


	// �������� ��������� person � ���� � ������� CSV, � ������ �������� persons
	void ArrayTelevisor::AppendToCsv(const char* fileNameCsv, const Televisor* TV)
	{
		const int LEN_BUF(1024);
		char buf[LEN_BUF];

		//������ �������� ������� �������
		FILE* FileOld = fopen(fileNameCsv, "a");
		if (!FileOld) {
			cout << endl << "File not opened.";
			sprintf(buf, "���� \"%s\" �� ������ ��� ������", fileNameCsv);
			throw exception(buf);
		}

		TV->toCsv(buf);
		fputs(buf, FileOld);

		fclose(FileOld);

		//������ �������� ����������� ��������� ����� �� ��������������� ����� ���������� ����������� ��������� +1
		FileOld = fopen(fileNameCsv, "r");
		if (!FileOld) {
			cout << endl << "File not opened.";
			sprintf(buf, "���� \"%s\" �� ������ ��� ������", fileNameCsv);
			throw exception(buf);
		}

		//���������������(��������������) ����
		FILE* FileNew = fopen("tmpFile.txt", "r");//������� �������, ����� �� ��� ����
		if (!FileNew) 
		{
			FileNew = fopen("tmpFile.txt", "w");
			if (!FileNew) {
				cout << endl << "File not opened.";
				sprintf(buf, "���� \"%s\" �� ������ ��� ������", "tmpFile.txt");
				throw exception(buf);
			}
		}
		else
		{
			cout << endl << "File exist.";
			sprintf(buf, "���� \"%s\" ����������.", "tmpFile.txt");
			throw exception(buf);
		}
		
		//!!! �� ������� ������ � ����� ��������
		// ������ ��������, ������ \n �� ������ 
		fgets(buf, LEN_BUF, FileOld);
		fputs(buf, FileNew);

		int tmpInt = 0;
		fscanf(FileOld, "%d\n", &tmpInt);
		tmpInt++;// ���������� ������� ������ ���� �� 1 ������!!!
		fprintf(FileNew, "%d\n", tmpInt); // �������� ���������� ��������� � ������� 

		// ������ ���� ������
		for (int i = 0; i < tmpInt; i++)
		{
			fgets(buf, LEN_BUF, FileOld);
			if (feof(FileOld)) break;

			fputs(buf, FileNew);
		} // for i

		fclose(FileOld);
		fclose(FileNew);

		//������ ��������, ������ ������ ����
		if (remove(fileNameCsv) != 0)
			cout << "Error deleting file.\n" << "Could not delete \"" << fileNameCsv << "\"" << endl;
		else
			cout << "File successfully deleted.\n" << "Delete \"" << fileNameCsv << "\"" << endl;

		//��������� ��������, ����������� ��������� ����
		if (rename("tmpFile.txt", fileNameCsv) == 0)            // �������������� �����
			cout << endl << "���� ������� ������������";
		else
		{
			cout << endl << "������ �������������� �����.";
			sprintf(buf, "���� \"%s\" ����� ������������ � \"%s\".", "tmpFile.txt", fileNameCsv);
			throw exception(buf);
		}

	} // AppendToCsv

	// ����� ������ � ����
	void ArrayTelevisor::writeToFile(FILE* File) const
	{
		// ������ ���� ������ ���������� � ��������� ������
		fprintf(File, "%d\n", size_);

		for (int i = 0; i < size_; i++)
		{
			fprintf(File, "%20s\n%20s\n", televisors_[i].getManufacturer(), televisors_[i].getModel());
			fprintf(File, "%10.2lf %5d %5d %10.2lf\n", televisors_[i].getSize(), televisors_[i].getResX(), televisors_[i].getResY(), televisors_[i].getPrice());
		}
	}

	// ������ ������� �������� � �������� ���� fileNamePersons
	void ArrayTelevisor::WriteArrayToBin(const char* fileNamePersons)
	{
		const int N_LEN(1024);
		char buf[N_LEN];

		// ������� �������� ���� ��� ������ 
		FILE* File = fopen(fileNamePersons, "wb");
		if (!File) {
			cout << endl << "File not opened."; 
			sprintf(buf, "�� ���� ������� ���� \"%s\" ��� ������", fileNamePersons);
			throw exception(buf);
		} // if
				
        //���������� ������ ������ ������� � �������� ����
		int tmpInt;
		tmpInt = getNameLength();
		fwrite(&tmpInt, sizeof(tmpInt), 1, File);
		fwrite(getName(), sizeof(char)*getNameLength(), 1, File);
		tmpInt = getSize();
		fwrite(&tmpInt, sizeof(tmpInt), 1, File);

		// ������ ������ � ���� � �������� �����
		for (int i = 0; i < getSize(); i++)
			televisors_[i].Write(File);
		fclose(File);

	} // WriteArrayToBin


	// ������ ������ �� ��������� ����� � ������ �������� Person
	void ArrayTelevisor::ReadArrayFromBin(const char* fileNamePersons)
	{
		const int N_LEN(1024);
		char buf[N_LEN];

		// ������� �������� ���� ��� ������ 
		FILE* File = fopen(fileNamePersons, "rb");
		if (!File) {
			cout << endl << "File not opened."; 
			sprintf(buf, "�� ���� ������� ���� \"%s\" ��� ������", fileNamePersons);
			throw exception(buf);
		} // if

		//������� ������ �������
		int tmpInt;
		fread(&tmpInt, sizeof(tmpInt), 1, File);
		fread(&buf, sizeof(char)*tmpInt, 1, File);
		buf[tmpInt] = '\0';
		fread(&tmpInt, sizeof(tmpInt), 1, File);

		// �������� ������� ������� n, ������ ������ �� ���������
	    // ����� � �������� ������� � �������� �����
		clear();
		create(tmpInt,buf);
		
		
		for (int i = 0; i < getSize(); i++)
			televisors_[i].Read(File);
		fclose(File);

	} // ReadArrayFromBin


	// ��� ������ ������� � �������
	// ������
	Televisor& ArrayTelevisor::at(int index) const
	{
		if ((index >= 0) && (index < size_))
			return televisors_[index];
		throw exception("\n ArrayTelevisor: Wrong index.");
	}

	// ������
	void ArrayTelevisor::put(int index, const Televisor& TV)
	{
		if (!((index >= 0) && (index < size_)))
			throw exception("\n ArrayTelevisor: Wrong index.");
		televisors_[index] = TV;
	} // put

#pragma endregion

	//����� ������ ���� �������� � ����������� ��������(����������)
	void ArrayTelevisor::showMinSize() 
	{
		int indexMin = 0;
		double minSize = televisors_[0].getSize();
		int cnt = 0;//���������� �����������
		double tmp_minSize;

		for(int i=1;i<getSize();i++)
			if (minSize >= (tmp_minSize=televisors_[i].getSize()))
			{
				if (minSize == tmp_minSize)
				{
					cnt++;//������� �����������, ���� �� ������ ����� �����������
					continue;//� ���������� �������
				}
				cnt = 1;//������ ��������� ����������� ������
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
		cout << endl << "�������� ������������. ����� ArrayTelevisor.\n";
		cout << "����� ���������� " << count_ << " ��������\n";
#endif
		return *this;
	} // ArrayAutomobile::operator=

	// ���������� �������� ��������������
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

		// ��������� ���������� ��������� ����
		SetConsoleTitle(title);
		// ��������� ���������� ��������� ����
		myAddConsoleTitle(L" ������������ ������ ArrayTelevisor ");

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


		coutColor("\n�������� 4e ��������� �������\n", wAttributeSpecial);

		int size_TVs = 5;
		Televisor* TVs = new Televisor[size_TVs];

		//		ArrayTelevisor c1;
		coutColor("\n����� �2.\n", wAttributeSpecial);
		ArrayTelevisor c2(5, "FirstTVsList");
		coutColor("\n����� �3.\n", wAttributeSpecial);
		ArrayTelevisor c3(TVs, size_TVs, "SecondTVsList");
		coutColor("\n����� �4.\n", wAttributeSpecial);
		ArrayTelevisor c4 = c2;
		coutColor("\n����� �5.\n", wAttributeSpecial);
		ArrayTelevisor c5 = c3;

		anyKey();

		//************************

		coutColor("\n������� ���� �������.\n", wAttributeSpecial);
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
		coutColor("\n���������� � �������� �4\n", wAttributeSpecial);
		c4.clear();
		c4.create(20, "NewTVsList");
		cout << "\n����������������� ������ ������ �������: \n" << c4.toString();

		c4.setName("SuperTVsList");
		cout << "\n������ ����� ���: \n" << c4.toString();

		for (int i = 0; i < c4.getSize(); i++)
			c4[i].setConstructor(my_TV[genRand(0, 19)]);

		coutColor("\n�������� ��� ���� ������� � �������������� ��������\n", wAttributeSpecial);
		//get
		cout << "\n��������� ��� ������: " << c4.getName();
		cout << "\n��������� ������ ����� ������: " << c4.getNameLength();

		cout << "\n��������� ���������� ����������� � ���: " << c4.getSize();

		anyKey();

		//*************************
		coutColor("\n����� �2.\n", wAttributeSpecial);
		c2.show(c2.getName());
		coutColor("\n����� �3.\n", wAttributeSpecial);
		c3.show(c3.getName());
		coutColor("\n����� �4.\n", wAttributeSpecial);
		c4.show(c4.getName());
		coutColor("\n����� �5.\n", wAttributeSpecial);
		c5.show(c5.getName());


		anyKey();

		//*************************
		FILE* File = fopen("testArrayTelevisor.txt", "w");
		if (!File) {
			cout << endl << "File not created.";
			throw exception("\n\tFile not created.\n");
		}

		coutColor("\n�������� � ����\n", wAttributeSpecial);
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

		coutColor("\n������� �� ����� � �������� �������\n", wAttributeSpecial);
		c5.get(File);
		c4.get(File);
		c3.get(File);
		c2.get(File);

		//������� ���������� � ������������ �������� � �������
		cout << c2.toString();
		cout << c3.toString();
		cout << c4.toString();
		cout << c5.toString();

		fclose(File);

		//*************************
		coutColor("\n����� �2.\n", wAttributeSpecial);
		c2.show(c2.getName());
		coutColor("\n����� �3.\n", wAttributeSpecial);
		c3.show(c3.getName());
		coutColor("\n����� �4.\n", wAttributeSpecial);
		c4.show(c4.getName());
		coutColor("\n����� �5.\n", wAttributeSpecial);
		c5.show(c5.getName());

		anyKey();
			   		 
		//*************************

		coutColor("\n�������� ������ ������ � .csv �������.\n", wAttributeSpecial);

		coutColor("\n����� �3(��������).\n", wAttributeSpecial);
		c3.show(c3.getName());
		ArrayTelevisor::WriteToCsv("testArrayTelevisor.csv",&c3) ;

		ArrayTelevisor::ReadFromCsv("testArrayTelevisor.csv",&c3);
		coutColor("\n����� �3(��������� �� �����).\n", wAttributeSpecial);
		c3.show(c3.getName());

		ArrayTelevisor::AppendToCsv("testArrayTelevisor.csv", &c3[0]);
		coutColor("\n����� �3(�������� ������� � ����).\n", wAttributeSpecial);
		c3.show(c3.getName());

		ArrayTelevisor::ReadFromCsv("testArrayTelevisor.csv", &c3);
		coutColor("\n����� �3(������� �� �����).\n", wAttributeSpecial);
		c3.show(c3.getName());

		File = fopen("ArrayTelevisor.txt", "w");
		if (!File) {
			cout << endl << "File not created.";
			throw exception("\n\tFile not created.\n");
		}

		coutColor("\n�������� � ���� ArrayTelevisor.txt\n", wAttributeSpecial);
		c4.writeToFile(File);

		fclose(File);
		anyKey();

		//*************************

		coutColor("\n�������� ������ put() �  at() ��� ������� �3.\n", wAttributeSpecial);

		for (int i = 0; i < c3.getSize(); i++)
			cout << c3.at(i).toString();
		coutColor("\n������ �3.\n", wAttributeSpecial);
		c3.show(c3.getName());

		c5 = c3;
		coutColor("\n������ �5.\n", wAttributeSpecial);
		c5.show(c5.getName());

		for (int i = 0; i < c3.getSize(); i++)
		{
			Televisor new_TV;
			new_TV.setConstructor(my_TV[genRand(0, 19)]);
			c3.put(i, new_TV);
		}
		coutColor("\n������ �3.\n", wAttributeSpecial);
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\n���� �3.(�� ����������)\n", wAttributeSpecial);
		c3.show(c3.getName());

		coutColor("\n���� �3.(���������� �� �������)\n", wAttributeSpecial);
		c3.OrderBySize();
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\n���� �3.(���������� �� ���������� ��� �)\n", wAttributeSpecial);
		c3.OrderByResolutionX();
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\n���� �3.(���������� �� ���������� �� ��� Y)\n", wAttributeSpecial);
		c3.OrderByResolutionY();
		c3.show(c3.getName());

		anyKey();

		//*************************

		coutColor("\n���� �3.(���������� �� ����)\n", wAttributeSpecial);
		c3.OrderByPrice();
		c3.show(c3.getName());

		anyKey();

		//*************************
		coutColor("\n���� �3. �������� ������ �� �������������. \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3, 4, GET_MANUFACTURER, c3[5].getManufacturer(), c3[7].getManufacturer(), c3[7].getManufacturer());
		c3.show(c3.getName());

		coutColor("\n���� �3. �������� ������ �� ����(�� 2500. �� 3000.). \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3,1,GET_PRICE);
		c3.show(c3.getName());

		coutColor("\n���� �3. �������� ������ �� ����(�� 2500. �� 3000.) � �� �������(�� 25. �� 30.). \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3, 2, GET_PRICE, GET_SIZE);
		c3.show(c3.getName());

		coutColor("\n���� �3. �������� ������ �� ������ � �� ������� ����� ������(�� 5 �� 10). \n", wAttributeSpecial);
		ArrayTelevisor::showFilter(&c3, 3, GET_MODEL, c3[5].getModel(), GET_MODEL_LENGTH);
		c3.show(c3.getName());

		anyKey();

		//*************************
		coutColor("\n�������� ������ << �  >> ��� ������� �4.\n", wAttributeSpecial);

		coutColor("\n����� ��� �4.(�� ����� ������)\n", wAttributeSpecial);
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



		coutColor("\n������ �4.(����� �������������)\n", wAttributeSpecial);
		c4.show(c4.getName());


		anyKey();

		//*************************

		coutColor("\n�������� ���������� [] ��� ������� �3.\n", wAttributeSpecial);

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
		//���� ������� ����� �������
		//����������� ���������� ����������
		anyKey(0, 26);

		//��������� ������ � ������ �������
		setCursorPosition(0, 26);

		//���������� ������� ������� ��� ����� ����������
		placeClear(0, 26, 300, 123);
	}


	void Exercises()
	{

		try
		{
			cls();

			// ��������� ���������� ��������� ����
			SetConsoleTitle(title);
			// ��������� ���������� ��������� ����
			myAddConsoleTitle(L" ������� ");

			//���������� ������ � �������� �������
			setCursorPosition(0, 1);
			Line(124, '*');
			//���������� �������� ��������� ����� ��� ����� ����������� ����� ������
			placeClear(0, 0, 40, 123);
			//������ ������ ��� ������� ������ ��������

			coutColor("\n\t\t�������� ���������� ���������� ��� ������� ������ �� ���� \"��� C++\".\n\t\
\t������� ������ ��� ������� ������.����������� ����� �� �������.� ������ ����������� :  \n\t\
- ������������ : �� ���������, � �����������, ����������, ����������                     \n\t\
- ������� � ������� ��� ���� ����� ������                                                \n\t\
- ���������� �������� �����, ������                                                      \n\t\
- ������ ����� �� ���������� �����(������ �������� �������� ���� ������ �����) � ������  \n\t\
� ���������	����                                                                         \n\t\
\t� ������� main() ������� ������������ ������ �� �������� ������(�� ����� 10 ���������),\n\t\
������� ��� ������ ������ ��� ������������ �� ������, �������� ������� � ��������� ����, \n\t\
��������� ������� �� ���������� �����, ������ ������ ����� � ���������� ������� � �����. \n\t\
��������������� ���� � ������������ �������.                                             \n\t\
                                                                                         \n\t\
                                                                                         \n\t\
\t����� ��������� � ������ ��� ��������                                                  \n\t\
- ������������� � ���� ����������,                                                       \n\t\
- ��������� ������,                                                                      \n\t\
- ���������� �� ���������,                                                               \n\t\
- ���������� �� �����������,                                                             \n\t\
- ����.                                                                                  \n\t\
� ������� �������� ���������� ���������� � ����������� ����������, ����������� ������ �� \n\t\
�������� ������������� � ���� ���������� � ������� ����������.                           \n\t\
\n", wAttributeSpecial);

			//������� ������ �� ������� *************************
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

			// ��������
			coutColor("\n�������� ������ ��������.\n", wAttributeSpecial);

			ArrayTelevisor TVs(10, "FirstTVsList");

			menuVisio();

//������������ ���������� ��� ������ ����������
			coutColor("\n�������� ������ ��������.\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			// �������������
			coutColor("\n�������������� ������ �������� ��������� ���������� ��������� ������������\n", wAttributeSpecial);

			for (int i = 0; i < TVs.getSize(); i++)
				TVs[i].setConstructor(my_TV[genRand(0, 19)]);

			//*************************
			FILE* File = fopen("ArrayTelevisor.txt", "w");
			if (!File) {
				cout << endl << "File not created.";
				throw exception("\n\tFile not created.\n");
			}

			// ������ � ���� 
			coutColor("\n�������� � ���� ArrayTelevisor.txt\n", wAttributeSpecial);
			TVs.writeToFile(File);

			fclose(File);

			menuVisio();

			//*************************

// ������ � ���������� � ���� � ������� .csv 

			coutColor("\n����� �3(������ � ����).\n", wAttributeSpecial);
			ArrayTelevisor::WriteToCsv("testArrayTelevisor.csv", &TVs);

			coutColor("\n����� �3(�������� ������� � ����).\n", wAttributeSpecial);
			ArrayTelevisor::AppendToCsv("testArrayTelevisor.csv", &TVs[0]);

			coutColor("\n����� �3(��������� �� �����).\n", wAttributeSpecial);
			ArrayTelevisor::ReadFromCsv("testArrayTelevisor.csv", &TVs);

			// ����� � �������
			TVs.show(TVs.getName());

			menuVisio();

			//������������ ���������� ��� ������ ����������
			coutColor("\n����� �3(��������� �� ����� c ����������� ���������).\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			//*************************
						
// ������ � ���������� � �������� ���� 

			coutColor("\n����� �3(������ � �������� ����).\n", wAttributeSpecial);
			TVs.WriteArrayToBin("testArrayTelevisor.bin");
			
			coutColor("\n����� �3(��������� �� ��������� �����).\n", wAttributeSpecial);
			TVs.ReadArrayFromBin("testArrayTelevisor.bin");
						
			// ����� � �������
			TVs.show(TVs.getName());

			menuVisio();

			//������������ ���������� ��� ������ ����������
			coutColor("\n����� �3(��������� �� ��������� �����).\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

// ������ � �������� � ������� ���������� �������� �������������� [ ]
			coutColor("\n�������� ���������� [] ��� �������.\n", wAttributeSpecial);

			for (int i = 0; i < TVs.getSize(); i++)
				cout << TVs[i].toString();


			menuVisio();
			
			//*************************
//����������
			coutColor("\nC��������� �� �������������.\n", wAttributeSpecial);
			TVs.OrderByManufacturer();
			TVs.show(TVs.getName());

			menuVisio();

//������������ ���������� ��� ������ ����������
			coutColor("\nC��������� �� �������������.\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			//*************************

			coutColor("\nC��������� �� ������.\n", wAttributeSpecial);
			TVs.OrderByModel();
			TVs.show(TVs.getName());

			menuVisio();

//������������ ���������� ��� ������ ����������
			coutColor("\nC��������� �� ������.\n", wAttributeSpecial);
			TVs.show(TVs.getName());
			anyKey();

			//*************************
//������
			coutColor("\n�������� ������ �� ����(�� 2500. �� 3000.) � �� �������(�� 25. �� 30.). \n", wAttributeSpecial);
			ArrayTelevisor::showFilter(&TVs, 2, GET_PRICE, GET_SIZE);
			TVs.show(TVs.getName());

			menuVisio();

			//*************************

			coutColor("\n�������� ������ �� �������������(��� �������� 5 � 7) � �� ������(��� �������� 5 � 7). \n", wAttributeSpecial);
			ArrayTelevisor::showFilter(&TVs, 8, GET_MANUFACTURER, TVs[5].getManufacturer(), TVs[7].getManufacturer(), TVs[7].getManufacturer(),GET_MODEL, TVs[5].getModel(), TVs[7].getModel(), TVs[7].getModel());
			TVs.show(TVs.getName());

			menuVisio();
			
			//*************************
//����� �������� � ����������� ����������(��������)
			coutColor("\n������� ��� ������� � ����������� ����������.\n", wAttributeSpecial);
			TVs.showMinSize();

			coutColor("\n�������� ������.\n", wAttributeSpecial);
			TVs.show(TVs.getName());

			menuVisio();

			//*************************

			cls();

			//throw exception(" "); // ������������� ����������
		}
		catch (exception ex) {  // ��������� ����������

			//���������� ������ � �������� �������
			setCursorPosition(0, 0);
			//���������� ������� ������� ��� ����� ����������
			placeClear(0, 0, 80, 123);


			SetConsoleTextAttribute(hStdOut, wAttributeWarning);
			cout << "\n\n"
				<< "\t\t                                                       \n"
				<< "\t\t    [������(������� ������)]                           \n"
				<< "\t\t    " << left << setw(48) << ex.what() << right << "   \n"
				<< "\t\t                                                       \n"
				<< "\n\n\n\n\n\n\n\n\n\n\n\n";
			//throw; // ������������� ���������� �� ����
			Sleep(1000);
			SetConsoleTextAttribute(hStdOut, wAttributeNormal);
			//continue;
		}

	}

#pragma endregion

}

