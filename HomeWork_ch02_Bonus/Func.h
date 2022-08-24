#ifndef FUNC_H /* —траж */
#define FUNC_H /* единственности вхождени€ - начало */

#include"pch.h"
#include"Utils.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;

//функци€ генерировани€ случайных значений в пределах [-min;max)
template <typename T>
T genRand(T min, T max) {
	// Uncomment the following line or use /std:c++17 to fix
#pragma warning(suppress:4984)
	if constexpr (is_same_v<T, int>)
		return static_cast<T>(min + rand1() % (max - min + 1));
#pragma warning(suppress:4984)
	else if constexpr (is_same_v<T, short>)
		return static_cast<T>(min + rand1() % (max - min + 1));
#pragma warning(suppress:4984)
	else if constexpr (is_same_v<T, double>)
		return static_cast<T>(min + (max - min) * rand1() / (static_cast<double>(UINT_MAX) + 1) + 1);
#pragma warning(suppress:4984)
	else if constexpr (is_same_v<T, float>)
		return static_cast<T>(min + (max - min) * rand1() / (static_cast<double>(UINT_MAX) + 1) + 1);
#pragma warning(suppress:4984)
	else if constexpr (is_same_v<T, char>)
		return static_cast<T>(65 + rand1() % 26 + rand1() % 2 * 32);
	else
		throw exception("Unknown type variable passed.");
	return rand1();
}

// —ортировка массива arr[] по возрастанию
template <typename T>
void sortInsertion(size_t N,
	T *A,
	bool valid(T*, T*) =
	[](T *A, T *B) {return((*A).getVolume() > (*B).getVolume()); })
{

	// ¬нешний цикл - перебор элементов массива
	for (size_t i = 1; i < N; ++i) {
		size_t j;
		// признак необходимости вставки элемента
		bool flag = false;     // предполагаем, что вставка не нужна

		// ищем место дл€ вставки очередного провер€емого 
		// элемента массива arr[i]
		for (j = 0; j <= i; ++j) {
			if (valid(&*(A+i), &*(A+j))) { // условие вставки сработало 
				flag = true;       // установить признак вставки
				break;
			} // if
		} // for j

		// вставка не нужна - переходим к следующему элементу массива
		if (!flag) continue;

		// сдвиг части массива вправо, вставка кандидата на найденное место
		T temp;
		temp = *(A + i);
		for (intmax_t k = i; k > j; --k)
			*(A+k) = *(A+k - 1);
		*(A+j) = temp;

	} // for i
} // sortInsertionAscend

template <typename T>
intmax_t find
(
	size_t N,
	T *A,
	bool valid(T*, T*) = [](T* A, T* B) {return((*A).getVolume() > (*B).getVolume()); }
	)
{
	intmax_t i_tmp = 0;
	for (size_t i = 1; i < N; i++) {
		if (valid(&*(A+i_tmp), &*(A+i))) i_tmp = i;
	}
	return i_tmp;
}

#endif //FUNC_H
