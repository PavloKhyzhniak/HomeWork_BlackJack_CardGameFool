#ifndef FUNC_H /* ����� */
#define FUNC_H /* �������������� ��������� - ������ */

#include"pch.h"
#include"Utils.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;

//������� ������������� ��������� �������� � �������� [-min;max)
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

// ���������� ������� arr[] �� �����������
template <typename T>
void sortInsertion(size_t N,
	T *A,
	bool valid(T*, T*) =
	[](T *A, T *B) {return((*A).getVolume() > (*B).getVolume()); })
{

	// ������� ���� - ������� ��������� �������
	for (size_t i = 1; i < N; ++i) {
		size_t j;
		// ������� ������������� ������� ��������
		bool flag = false;     // ������������, ��� ������� �� �����

		// ���� ����� ��� ������� ���������� ������������ 
		// �������� ������� arr[i]
		for (j = 0; j <= i; ++j) {
			if (valid(&*(A+i), &*(A+j))) { // ������� ������� ��������� 
				flag = true;       // ���������� ������� �������
				break;
			} // if
		} // for j

		// ������� �� ����� - ��������� � ���������� �������� �������
		if (!flag) continue;

		// ����� ����� ������� ������, ������� ��������� �� ��������� �����
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
