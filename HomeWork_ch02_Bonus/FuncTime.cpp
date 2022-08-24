
#include "pch.h"
#include "FuncTime.h"

//функции предоставления системного времени
char* displaySystemTime(void) {
	SYSTEMTIME st;

	GetSystemTime(&st);
	char* buf = new char[10];
	sprintf_s(buf, 10, "%02d:%02d", st.wHour, st.wMinute);

	return buf;
}

//функции предоставления локального времени
char* displayLocalTime(void) {
	SYSTEMTIME lt;

	GetLocalTime(&lt);
	char* buf = new char[10];
	sprintf_s(buf, 10, "%02d:%02d", lt.wHour, lt.wMinute);

	return buf;
}

//функции предоставления локального времени полученного из RAW формата
char* displayLocalTimeRAW(void) {
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	_localtime64_s(&timeinfo, &rawtime);
	char* buf = new char[6];
	strftime(buf, 6, "%H:%M", &timeinfo);

	return buf;
}

//функция преобразования переданного имени с добавлением к нему локального времени
char* name_time(const char* name, const char* type) {
	char* buf = new char[100];
	// ------- name_HH_MM.type --------------
	strcpy(buf,name);
	strcat(buf, "_");
	strcat(buf, displayLocalTime());
	buf[strlen(buf) - 3] = '_';
	strcat(buf, ".");
	strcat(buf,type);

	return buf;
}

