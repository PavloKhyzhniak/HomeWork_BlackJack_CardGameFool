
#ifndef TELEVISOR_H /* ����� */
#define TELEVISOR_H /* �������������� ��������� - ������ */


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
//		// �� ����� - ������ a[], a[N] - ��� ��������� �������.
//
//	//	display(end + 1, array, "\n\t1-D array(SubArray):\n");
//
//		// ��� ������ ���������
//		intmax_t i = 0, j = end; //����� � ������ ������� ����������
//
//		// ������ ���������� ������� �������� �������
//		T value = array[end >> 1]; // �������� - �������� �������� � �������� ���������
//
//		T temp; // ��������������� ����������
//		// ��������� ����������
//		do {
//			// �������� �� ������ � ��������, ���� �� ������ ������� �� ��������������� �������
//			//while (array[i] < p) i++;
//			while (valid(array[i], value)) i++;
//
//			// �������� �� ����� � ��������, ���� �� ������ ������� �� ��������������� �������
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
//		// ����������� ������, ���� ����, ��� ����������� 
//		if (j > 0) quickSortR(array, j, valid); // �� ������ ������� �� cur
//		if (end > i) quickSortR(array + i, end - i, valid); // �� cur+1 �� ����� �������
//	}// quickSortR

	//�������� ��������� ��� �������� ������������� �������� ������ Televisor
	struct TV {

		const char manufacturer[20];
		const char model[20];

		double size;
		int resX;
		int resY;
		double price;

	};

	//������ ������������ ��� �������� ������ � �������� �� ����� ������� Televisor ��� ������ � ������� ArrayTelevisor
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
	
	//����� 
	class Televisor
	{
	private:
//����������� ����������, �������� ��������� �������� � ���������
		static int count_;

		//���� �������������
		char* manufacturer_;
		int manufacturer_length_;

		//���� ������
		char* model_;
		int model_length_;

		//���� ������(���������)
		double size_;
		//���� X � Y, ���������� ��������������
		int resX_;
		int resY_;
		//���� ����
		double price_;

		//���������� ����� ������������� ������� ����� >> � ������ <<
		friend std::ostream& operator<<(std::ostream& os, const Televisor& object);
		friend std::istream& operator>>(std::istream& is, Televisor& object);


	public:
		//constructor
//����������� �� ���������
		Televisor();
		//����������� � ����������� ������������� �������
		Televisor(const char* manufacturer, const char* model, double size, int resX, int resY, double price);
		//����������� ����������
		Televisor(const Televisor& object);
		//destructor
		//����������
		~Televisor();

		//set
		//����� ��� ������������� �������, ������� ��� ����
		int setConstructor(const char* manufacturer, const char* model, double size, int resX, int resY, double price);
		//����� ��� ������������� �������, ����� ��������� ���������� ��� ���� �������
		int setConstructor(TV newTV);

		//������� ��������� ����� �������
		int setManufacturer(const char* name);
		int setModel(const char* name);

		int setSize(double size);
		int setResolution(int resX, int resY);
		int setPrice(double price);

		//get
		//������� ��� ������� � ����� �������
		const char* getManufacturer() const;
		int getManufacturerLength() const;
		const char* getModel() const;
		int getModelLength() const;

		double getSize() const;
		int getResX() const;
		int getResY() const;
		double getPrice() const;

		//methods
		
		// ��������� - ���������� true ��� ������ ������, �.�. ��������� �������������
		// �� ���������
		bool IsEmpty() const { return ((!strcmp(manufacturer_,"_noname_")) && (!strcmp(model_,"_noname_")) && 
			(abs(size_) <= 0.1) && (resX_ == 0) && (resY_ == 0) && (abs(price_) <= 0.1)); }
		
		// ������ �� ���������� ����� � ������
		void get(FILE* File);

		// ������ ������� � ��������� ����
		void put(FILE* File) const;

		// ��������� ����� - ���������� ����� ������� � ��������� �������������
		char* toString() const;

		//������ � ������ � ������� .csv
		void toCsv(char* str) const;
		void parseCsv(char* str);
		
		// ����������/������ � �������� ����
		void Write(FILE* f) const;

		// ������ �� ��������� ����� � ���� ������
		void Read(FILE* f);

		//operators

		// �������� ������������ ������������
		Televisor& operator=(const Televisor& object);

		// �������� ������������ ������������
		Televisor& operator=(Televisor&& object) = default;

		
	};

	//����� 
	class ArrayTelevisor
	{
	private:
//����������� ��������� ��� ��������� ��������� �������� � ���������
		static int count_;

		//���� ��� �������(������)
		char* name_;
		int name_length_;

		int size_;          // ������ �������
		Televisor* televisors_;  // ������

		//�������� �����, ������� ����������
		void QuickSort(int start, int end, int compare(const Televisor& TV1, const Televisor& TV2));

		//��������� ��� ������� ����������
		static int CompareManufacturer(const Televisor& TV1, const Televisor& TV2);
		static int CompareModel(const Televisor& TV1, const Televisor& TV2);

		static int CompareSize(const Televisor& TV1, const Televisor& TV2);
		static int CompareResolutionX(const Televisor& TV1, const Televisor& TV2);
		static int CompareResolutionY(const Televisor& TV1, const Televisor& TV2);
		static int ComparePrice(const Televisor& TV1, const Televisor& TV2);

		//�������� �����, ��������� ������� �������
		int setSize(int size);

		//�������� �����, �������� ������������ �������� ������� ������������ ���������-����(������) � ������
		static	bool isCorrect(MyMethod_enum check)
		{
			return ((check >= GET_MANUFACTURER) && (check <= ERROR_ENUM));
		}
		
	public:
		//constructor
		//����������� �� ��������� ��������
		ArrayTelevisor() = delete;
		//����������� � �����������
		ArrayTelevisor(int size, const char* name);
		//����������� � �����������(������������� ������� �������� ��������)
		ArrayTelevisor(Televisor* TVs, int size, const char* name);
		//����������� �����������
		ArrayTelevisor(const ArrayTelevisor& object);
		//destructor
		//����������
		~ArrayTelevisor();

		//set
		//������� ������������ ��������(������������) �������
		int create(int size, const char* name);
		//������� ����������� �������� ����������� �������, ��� ������������
		void clear();

		//������ ����� ���������(�������)
		int setName(const char* name);

		//get
		//������� ��� ������� �� ���� ����� �������
		char* getName() const;
		int getNameLength() const;

		int getSize() const;

		//methods

		// ��������� - ���������� true ��� ������ ������, �.�. ��������� �������������
		// �� ���������
		bool IsEmpty() const { return ((name_ == nullptr) && (name_length_ == 0) && (size_ == 0) && (televisors_ == nullptr)); }

		// ������ �� ���������� ����� � ������
		void get(FILE* File);

		// ������ ������� � ��������� ����
		void put(FILE* File) const;

		// ��������� ����� - ���������� ����� ������� � ��������� �������������
		char* toString() const;

		//����������
		void OrderByManufacturer() { QuickSort(0, getSize() - 1, CompareManufacturer); }
		void OrderByModel() { QuickSort(0, getSize() - 1, CompareModel); }

		void OrderBySize() { QuickSort(0, getSize() - 1, CompareSize); }
		void OrderByResolutionX() { QuickSort(0, getSize() - 1, CompareResolutionX); }
		void OrderByResolutionY() { QuickSort(0, getSize() - 1, CompareResolutionY); }
		void OrderByPrice() { QuickSort(0, getSize() - 1, ComparePrice); }

		//������ � �������
		static void WriteToCsv(const char* fileNameCsv, const ArrayTelevisor* TVs);
		static void ReadFromCsv(const char* fileNameCsv, ArrayTelevisor* TVs);
		static void AppendToCsv(const char* fileNameCsv, const Televisor* TV);

		void WriteArrayToBin(const char* fileNamePersons);
		void ReadArrayFromBin(const char* fileNamePersons);

		void writeToFile(FILE* File) const;

		// ����� ��������� � ���� �������
		void show(const char* title = "_noname_");

		//��������� �����
		//������ �� ���������� �������� ����� [min;max]
		template <typename T>
		static	void filter(ArrayTelevisor* arr, T(Televisor::* getMethod)() const, const T min, const T max)
		{
			//������� ��������� ������, ������ �������� �� ������ ���������
			ArrayTelevisor tmpArr(arr->getSize(), arr->getName());

			int j;//������� ��������������� ��������
#pragma warning(suppress:4984)
			if constexpr (is_same_v<T, int>)
			{
				j = 0;//������� ��������������� �������� �� ����
				for (int i = 0; i < arr->getSize(); i++)//�������� ��� ������� ���������� ���������
					if (//��������� �������� �� ����� ������
						(((arr->televisors_[i]).*getMethod)() >= min) &&
						(((arr->televisors_[i]).*getMethod)() <= max)
						)
						//��� ��������� � ��������, ������ ������������� �� ��������� ������(��������������)
						tmpArr.televisors_[j++] = arr->televisors_[i];
			}
#pragma warning(suppress:4984)
			else if constexpr (is_same_v<T, double>)
			{
				j = 0;//������� ��������������� �������� �� ����
				for (int i = 0; i < arr->getSize(); i++)//�������� ��� ������� ���������� ���������
					if (//��������� �������� �� ������������ ������
						(((arr->televisors_[i]).*getMethod)() >= min) &&
						(((arr->televisors_[i]).*getMethod)() <= max)
						)
						//��� ��������� � ��������, ������ ������������� �� ��������� ������(��������������)
						tmpArr.televisors_[j++] = arr->televisors_[i];
			}
			else
				throw exception("Unknown type variable passed.");

			//������� ���������� ���������
			arr->clear();
			//�������������� ��������� �� ���������� ��������� � ������ ���������������� �����������
			arr->create(j, tmpArr.getName());

			//�������� ��� ������� �� ���������� �������
			for (int i = 0; i < j; i++)
				(*arr)[i] = tmpArr[i];
			//��������� ������ ���������� ����������� ������ �����������
		};

		//��������� �����
		// ������ �� ������ �������� (const char*)
		template <typename T>
		static	void filter(ArrayTelevisor* arr, T(Televisor::* getMethod)() const, char*** arrayName, const size_t N)
		{
			//������� ��������� ������, ������ �������� �� ������ ���������
			ArrayTelevisor tmpArr(arr->getSize(), arr->getName());
	
			int j;//������� ��������������� ��������
	
	#pragma warning(suppress:4984)
			if constexpr (is_same_v<T, const char*>)
			{
				j = 0;//������� ��������������� �������� �� ����
				for (int i = 0; i < arr->getSize(); i++)//�������� ��� ������� ���������� ���������
					for (size_t k = 0; k < N; k++)//��������� ������ ������ ���������� ���������, � ������������ ����������(arrayName)
						if (!strcmp(((arr->televisors_[i]).*getMethod)(), (*arrayName)[k]))
						{
							//��� ����������(����������) ������� ������� �������, ��������� ������ �� ��������� �������(��������������)
							tmpArr.televisors_[j++] = arr->televisors_[i];
							break;//��������� ���� ������ �� ����������� �������, ��������� � ���������� ������� ���������
						}
			}
			else
				throw exception("Unknown type variable passed.");
	
			//������� ���������� ���������
			arr->clear();
			//�������������� ��������� �� ���������� ��������� � ������ ���������������� �����������
			arr->create(j, tmpArr.getName());

			//�������� ��� ������� �� ���������� �������
			for (int i = 0; i < j; i++)
				(*arr)[i] = tmpArr[i];
			//��������� ������ ���������� ����������� ������ �����������
		};

		//������� ���������� ������������� ������� ���� ��� ������� �� ������������� � ������
		static void addArrayName(char*** arrayName, size_t* N, const char* Name) 
		{
			//��������� ���������� �� ������ �������� �������
			if (*arrayName != nullptr)
			{
				size_t i;
				//����� ����������
				for (i = 0; i < *N ; i++)//�������� ��� ������� ������� �� ���������� � ����� ��������(Name)
				{
					//��� ����������(���������� ���������),��������� �������� ��������, ������� �� �����
					if (!strcmp((*arrayName)[i], Name)) break;
				}

				if (i == *N)//���� ��� ������ ��������(�� ��� �������� ������� �������� ������� ���� �����������)
				{
					//������� ����� ������ � �������������� ���������
					char** newArray = new char* [++(*N)]{ 0 };
					//�������� ��� �������� ��������
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
					//��������� ���������� �������
					try {
						newArray[i] = new char[strlen(Name) + 1];
					}
					catch (exception ex)
					{
						throw exception("\n\t addArrayName():No memory to NEW name.\n");
					}

					strcpy(newArray[i], Name);
					//������� ������ ������
					if (*arrayName != nullptr)
						delete[] * arrayName;
					//���������� ����� ������
					*arrayName = newArray;
				}
			}
			else
			{
				//����� ��������� ������
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
		//����������� ����� ����������� ������� �������� ���������(arr), �� �������� ��������(��. MyMethod_enum)
		static	void showFilter(ArrayTelevisor* arr, int n, int number, ...)
		{
			//
			va_list p;//���������� ��������� �� ��������� ���������� ��������
			va_list copy_p;//���������� ����� ��������� �� ��������� ���������� ��������
			va_start(p, n);//������������� ���������, �� �������� n

			//���������� ����������� ����������� �������(������ �� ����������� ��� ���������� - �������� �������� ��� ��������� �������)
			ArrayTelevisor resultArr(arr->getSize(), arr->getName());

			//��������� ��� ������� ��������� �������
			for (int i = 0; i < arr->getSize(); i++)
				resultArr[i] = (*arr)[i];

			//�������� ��������� �� ������������� �������� ������(���������)
			ArrayTelevisor* tmpArr = &resultArr;

			//������� ��������� �� ������ �������� ������� ��� filter ���������� � const char*
			char** arrayName = nullptr;
			size_t N = 0;//���������� �������� � �������

			//��������������� ���������� ��� ���������� �� ����������� ����� ���������� �������� ������� �������� ��� const char*
			const char* name{ 0 };

			//���� ���� �� ������������ ���������
			while (n-->0) {

				//������� ��������� ��������(������ ������� ������� �� MyMethod_enum
				int method = va_arg(p, int);

				//����������� ������ �������� ���������� ��������(���������� ���� ������� - ������ ������� � ������� ����)
				switch (method)
				{
				case GET_MANUFACTURER:
				case GET_MODEL:
					//�� ������������� 
					//�� ������

					n--;//��������� ������������ ��������
					//��������� ��������� ��������(������ ������� ������� ���� ������ ���� const char*)
					name = va_arg(p, const char*);
					addArrayName(&arrayName, &N, name);//�������� ��������� ������ ������� � ������ ����������� �������� �� ������� ��������

					while (n-- > 0)//���� ���� ���������, ������� ��� �� ��� ���������� �������� �� ������� ��������
					{
						//������ ����� ��������� �� ��������� ��������, � ����� ������ ���� ����������, ��� ������ ���� ��������� ���������� �������
						va_copy(copy_p, p);

						//��������� ��������� ��������(����� ������� ��� ������ ���� ����� ������)
						int index = va_arg(p, int);

						//�������� � ��������� ���������(������� ��� �����)
						va_copy(p, copy_p);

						//�������� ��������� ��������, ���� �� ��������� ��������� �� MyMethod_enum, ��
						if (isCorrect(static_cast<MyMethod_enum>(index)))
						{
							//������ ��� ���������� �� 1 ������(����������� ����� ���������� ��������)
							n++;
							//����� �� �����
							break;
						}

						//� ������ �� ������������ ���������� �������� MyMethod_enum, �� ������ ��� ���� ������
						//��������� ������ �������� ������(const char*)
						name = va_arg(p, const char*);

						addArrayName(&arrayName, &N, name);//�������� ��������� ������ ������� � ������ ����������� �������� �� ������� ��������
					}
					
					if (method == GET_MANUFACTURER)
					{
						//filter(tmpArr, &Televisor::getManufacturer, "LG", "SAMSUNG");
						filter(tmpArr, &Televisor::getManufacturer, &arrayName, N);//������� ������� �������, ��������� ��������������� �����(��������) � ������ �������� ��� �������

						//������ ������ �������� ���������� �� ������ ����������
						if (arrayName != nullptr)
						{
							if (*arrayName != nullptr)
								delete[] * arrayName;
							arrayName = nullptr;
						}
						//������ ������������� �������� ������ �������, ������� ������� ����� ������ �������
						cout << "\n������ �� �������������.\n";
						break;
					}

					if (method == GET_MODEL)
					{
						//filter(tmpArr, &Televisor::getModel, "S22B350", "34UM61");
						filter(tmpArr, &Televisor::getModel, &arrayName, N);//������� ������� �������, ��������� ��������������� �����(��������) � ������ �������� ��� �������

						//������ ������ �������� ���������� �� ������ ����������
						if (arrayName != nullptr)
						{
							if (*arrayName != nullptr)
								delete[] * arrayName;
							arrayName = nullptr;
						}

						//������ ������������� �������� ������ �������, ������� ������� ����� ������ �������
						cout << "\n������ �� ������.\n";
						break; 
					}
					throw(exception("showFilter(): not correct method."));
					break;
				case GET_MANUFACTURER_LENGTH:
					filter(tmpArr, &Televisor::getManufacturerLength, 5, 10);
					cout << "\n������ �� ������ ����� �������������(�� 5 �� 10).\n";
					break;
				case GET_MODEL_LENGTH:
					filter(tmpArr, &Televisor::getModelLength, 5, 10);
					cout << "\n������ �� ������ �������� ������(�� 5 �� 10).\n";
					break;
				case GET_SIZE:
					filter(tmpArr, &Televisor::getSize, 25., 30.);
					cout << "\n������ �� �������(�� 25. �� 30.).\n";
					break;
				case GET_RESX:
					filter(tmpArr, &Televisor::getResX, 2000, 3000);
					cout << "\n������ �� ���������� ��� Y(�� 2000 �� 3000).\n";
					break;
				case GET_RESY:
					filter(tmpArr, &Televisor::getResY, 2000, 3000);
					cout << "\n������ �� ���������� ��� Y(�� 2000 �� 3000).\n";
					break;
				case GET_PRICE:
					filter(tmpArr, &Televisor::getPrice, 2500., 3000.);
					cout << "\n������ �� ����(�� 2500. �� 3000.).\n";
					break;
				default:
					throw(exception("Wrong filter method."));
				}
				tmpArr->show(tmpArr->getName());

			}
			//������ ��������� �� ���������� ����� ���������� �������
			va_end(p);
			va_end(copy_p);

			//������� ��������������� ���������
			tmpArr->show(tmpArr->getName());

			anyKey();
		};

		void showMinSize();

		Televisor& at(int index) const;
		void put(int index, const Televisor& TV);


		//operators

		// �������� ������������ ������������
		ArrayTelevisor& operator=(const ArrayTelevisor& object);

		// �������� ������������ ������������
		ArrayTelevisor& operator=(ArrayTelevisor&& object) = default;

		// ���������� �������� ��������������
		Televisor& operator[](int index);

		//������������� �������
		const char* operator[](const char* word);

	};

	void TestClassTelevisor();
	void TestClassArrayTelevisor();

	void Exercises();

}// classApp


#endif //TELEVISOR_H

