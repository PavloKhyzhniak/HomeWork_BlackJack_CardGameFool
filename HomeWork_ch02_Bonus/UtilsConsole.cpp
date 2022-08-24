#include "pch.h"
#include "UtilsConsole.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
extern WORD wOldColorAttrs;
extern RECT r;
extern HWND console;

// ��������� ��������� ������������� ���������
void init() {

	//**************************************************************************
	// ��� ����������� ������ �� ������� �����
	SetConsoleOutputCP(CODE_PAGE);
	// ��� ����������� ����� �� ������� �����
	SetConsoleCP(CODE_PAGE);

	//**************************************************************************

	// Get handles to STDIN and STDOUT. 

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	console = GetConsoleWindow();

	// Save the current text colors. 

	GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);

	wOldColorAttrs = csbiInfo.wAttributes;

	// Set the text attributes to draw red text on black background. 

	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);

	//**************************************************************************
	ReDrawConsole(100, 100);	
}

void coutColor(const char* text, WORD attributes) {
	// Save the current text colors. 
	CONSOLE_SCREEN_BUFFER_INFO tmp_csbiInfo;
	WORD tmp_wOldColorAttrs;
	
	GetConsoleScreenBufferInfo(hStdOut, &tmp_csbiInfo);

	tmp_wOldColorAttrs = tmp_csbiInfo.wAttributes;
	
	SetConsoleTextAttribute(hStdOut, attributes);
	cout << text ;
	SetConsoleTextAttribute(hStdOut, tmp_wOldColorAttrs);
}

// x is the column, y is the row. The origin (0,0) is top-left. 
void setCursorPosition(short x, short y)
{
	cout.flush();
	COORD coord = { x, y };
	SetConsoleCursorPosition(hStdOut, coord);
}

//������� ��������� ����������� ��������� ����������� ���������� ����������
void myAddConsoleTitle(const wchar_t title[150]) {
	wchar_t titleAct[150];
	GetConsoleTitle(titleAct, 150);
	wcscat_s(titleAct, title);
	SetConsoleTitle(titleAct);
}

//������� ������ �������
void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

//������� �������� �������
void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

//������� �������� ��������� ������� ������/������
bool IsConsoleVisible()
{
	return (::IsWindowVisible(::GetConsoleWindow()) != FALSE);
}

//������� ����������� ������� � �������� ����� ���������(x,y) � ���������� ����� �� ������ � ������
void ReDrawConsole(int x, int y, int width, int height) {
	GetWindowRect(console, &r); //stores the console's current dimensions

	COORD bufferSize = { 80, 50 };
	SetConsoleScreenBufferSize(hStdOut, bufferSize);

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, x, y, width, height, TRUE);
}

// �������� �������� � �������� �������...
// ... n - ���������� ��������� ��������
void positionClear(int x, int y, int n)			
{								
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hStdOut, coord);

	for (int i = 0; i < n; i++)
		cout << " ";

}  // position()

// �������� �������� � ������� ������� � ��������� � �������� �������
// N - ���������� ��������� ��������
// Nsetw - ����� ������ �������
void placeClear(short x, short y, size_t Nrows, size_t Ncolums)
{
	// ��������� ����� ������
	ostringstream oss;
	oss.str("");

	for (size_t i = 0; i < Nrows; i++)
	{
		for (size_t j = 0; j < Ncolums; j++)
			oss << " ";
		oss << endl;
	}

	setCursorPosition(x, y);
	cout << oss.str().c_str();

	setCursorPosition(x, y);
}  // position()

// ������� ������ �������
void cls()
{
	COORD coordScreen = { 0, 0 }; // �������� ������� ��� �������
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	// ������� ����� ���������� ����� � ������� ������.

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;

	// ������ ���� ������� � ��������
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// �������� ��������� ����� ��������� - ��� � ���� �������
	// cCharsWritten - ������� ���������� ��������
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	// ��������� ��������������� �������� ������ �� ������� ���������.
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// �������� ������ � ��������� ������� ����� ������� ������ - ������� ����� ����
	SetConsoleCursorPosition(hStdOut, coordScreen);
} // Cls

// ��������� ��� ���������� ������� �������
// mode: true  - �������� ������
//       false - ��������� ������
void setCursorVisible(bool mode)
{
	// ��� ���� ��������� winAPI
	CONSOLE_CURSOR_INFO info;

	// ��������� ������ � ��� ���������
	GetConsoleCursorInfo(hStdOut, &info);

	info.bVisible = mode;
	SetConsoleCursorInfo(hStdOut, &info);
} // void setCursorVisible

//������� ��������� �� ������ �������� �������������� ������� - �������������� ������������
void Draw(COLORREF color, double min, double max, double delta, double Zero, double func(double,double), double bias)
{
	HDC hdc = GetDC(GetConsoleWindow());
	double x, y;
	COLORREF penColor = color;

	// ������ ������ ��������� �� ������
	for (x = min; x < max; x+=delta)
	{
		y = func(x,bias);
		SetPixel(hdc, int(x), int(Zero) + int(50 * y), penColor);
	}
	ReleaseDC(NULL, hdc);

//	HDC hdc = GetDC(GetConsoleWindow());
//	// ������� ���� ��� ���������
//	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
//	SelectObject(hdc, Pen);
//	// ������ ��������� �� ��������
//	int xScale = 10, yScale = 50;
//	// �������������X �Y
//	int xO = 300, yO = 100;
//	// ��������� ������ ���������
//	// �������� ��������� ��������
//	float xBeg = min, xEnd = max;
//	// ��������� � ��������� ����� ������
//	MoveToEx(hdc, xO + xScale * xBeg, yO + yScale * func(xBeg), NULL);
//	//������ ������� �� ����� � �����
//	for (x = xBeg; x <= xEnd; x += delta)
//		LineTo(hdc, xO + xScale * x, yO + yScale * func(x));
//	DeleteObject(Pen);
//	ReleaseDC(NULL, hdc);
}

//������� ��������� �� ������ �������� �������������� ������� - ������������ ������������
void DrawV(COLORREF color, double min, double max, double delta, double Zero, double func(double,double), double bias)
{
	HDC hdc = GetDC(GetConsoleWindow());
	double x, y;
	COLORREF penColor = color;

	// ������ ������ ��������� �� ������
	for (x = min; x < max; x += delta)
	{
		y = func(x,bias);
		SetPixel(hdc, int(Zero) + int(50 * y), int(x), penColor);
	}
	ReleaseDC(NULL, hdc);
}

//������� ��������� �� ������ ��������� ����� 
void DrawCard
(
	COLORREF color ,
	int x0 ,
	int y0 ,
	const char* suitmark,
	int rank
) 
{
	

	setCursorPosition(0,14);
	if (!strcmp("Hearts", suitmark))
	{
		cout << "\t\t\t\t\t       000      000     \n";
		cout << "\t\t\t\t\t      00000    00000    \n";
		cout << "\t\t\t\t\t      00000000000000    \n";
		cout << "\t\t\t\t\t       000000000000     \n";
		cout << "\t\t\t\t\t        0000000000      \n";
		cout << "\t\t\t\t\t          000000        \n";
		cout << "\t\t\t\t\t            00          \n";
	}
	if (!strcmp("Clubs",suitmark))
	{
		cout << "\t\t\t\t\t            000         \n";
		cout << "\t\t\t\t\t           0 o 0        \n";
		cout << "\t\t\t\t\t            000         \n";
		cout << "\t\t\t\t\t       000   0   000    \n";
		cout << "\t\t\t\t\t      0 o 000o000 o 0   \n";
		cout << "\t\t\t\t\t       000   0   000    \n";
		cout << "\t\t\t\t\t             0          \n";
		cout << "\t\t\t\t\t            0o0         \n";
		cout << "\t\t\t\t\t           00000        \n";
	}
	if (!strcmp("Diamonds",suitmark))
	{
		cout << "\t\t\t\t\t             0          \n";
		cout << "\t\t\t\t\t            000         \n";
		cout << "\t\t\t\t\t           00000        \n";
		cout << "\t\t\t\t\t          0000000       \n";
		cout << "\t\t\t\t\t         000000000      \n";
		cout << "\t\t\t\t\t          0000000       \n";
		cout << "\t\t\t\t\t           00000        \n";
		cout << "\t\t\t\t\t            000         \n";
		cout << "\t\t\t\t\t             0          \n";
	}
	if (!strcmp("Pikes",suitmark))
	{
		cout << "\t\t\t\t\t             0          \n";
		cout << "\t\t\t\t\t            000         \n";
		cout << "\t\t\t\t\t          0000000       \n";
		cout << "\t\t\t\t\t        00000000000     \n";
		cout << "\t\t\t\t\t      000000000000000   \n";
		cout << "\t\t\t\t\t      000000000000000   \n";
		cout << "\t\t\t\t\t        0000 0 0000     \n";
		cout << "\t\t\t\t\t            000         \n";
		cout << "\t\t\t\t\t           00000        \n";
	}

	setCursorPosition(0, 4);
	switch (rank)
	{
	case 6:
		cout << "\t\t\t\t\t          0000000       \n";
		cout << "\t\t\t\t\t         00    000      \n";
		cout << "\t\t\t\t\t        00              \n";
		cout << "\t\t\t\t\t       0000000          \n";
		cout << "\t\t\t\t\t      00    0000        \n";
		cout << "\t\t\t\t\t      00      000       \n";
		cout << "\t\t\t\t\t      00       00       \n";
		cout << "\t\t\t\t\t       00     00        \n";
		cout << "\t\t\t\t\t        0000000         \n";
		break;
	case 7:
		cout << "\t\t\t\t\t     0000000000         \n";
		cout << "\t\t\t\t\t    000      00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t            00          \n";
		cout << "\t\t\t\t\t           00           \n";
		cout << "\t\t\t\t\t          00            \n";
		cout << "\t\t\t\t\t          00            \n";
		cout << "\t\t\t\t\t          00            \n";
		cout << "\t\t\t\t\t          00            \n";
		break;
	case 8:
		cout << "\t\t\t\t\t     000000000          \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t     00     00          \n";
		cout << "\t\t\t\t\t       00000            \n";
		cout << "\t\t\t\t\t     00     00          \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t     000000000          \n";
		break;
	case 9:
		cout << "\t\t\t\t\t     000000000          \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t      000000000         \n";
		cout << "\t\t\t\t\t             00         \n";
		cout << "\t\t\t\t\t             00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t     000000000          \n";
		break;
	case 10:
		cout << "\t\t\t\t\t    00     00000000     \n";
		cout << "\t\t\t\t\t   000   000      000   \n";
		cout << "\t\t\t\t\t  0000   00     0  00   \n";
		cout << "\t\t\t\t\t 00 00   00    0   00   \n";
		cout << "\t\t\t\t\t    00   00   0    00   \n";
		cout << "\t\t\t\t\t    00   00  0     00   \n";
		cout << "\t\t\t\t\t    00   00 0      00   \n";
		cout << "\t\t\t\t\t    00   000      000   \n";
		cout << "\t\t\t\t\t    00     00000000     \n";
		break;
	case 11:
		cout << "\t\t\t\t\t    00000000            \n";
		cout << "\t\t\t\t\t    00     00    JACK   \n";
		cout << "\t\t\t\t\t    00      00          \n";
		cout << "\t\t\t\t\t    00     00           \n";
		cout << "\t\t\t\t\t    000000000           \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    000000000           \n";
		break;
	case 12:
		cout << "\t\t\t\t\t      0000000           \n";
		cout << "\t\t\t\t\t     00     00          \n";
		cout << "\t\t\t\t\t    00       00  QUEEN  \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t    00       00         \n";
		cout << "\t\t\t\t\t   0000000000000        \n";
		cout << "\t\t\t\t\t  00           00       \n";
		cout << "\t\t\t\t\t  00           00       \n";
		break;
	case 13:
		cout << "\t\t\t\t\t    00      00000       \n";
		cout << "\t\t\t\t\t    00    000  00  KING \n";
		cout << "\t\t\t\t\t    00  000             \n";
		cout << "\t\t\t\t\t    00000               \n";
		cout << "\t\t\t\t\t    00 00               \n";
		cout << "\t\t\t\t\t    00  00              \n";
		cout << "\t\t\t\t\t    00   00             \n";
		cout << "\t\t\t\t\t    00    00   00       \n";
		cout << "\t\t\t\t\t    00     000000       \n";
		break;
	case 14:
		cout << "\t\t\t\t\t          00            \n";
		cout << "\t\t\t\t\t         0000      ACE  \n";
		cout << "\t\t\t\t\t        00  00          \n";
		cout << "\t\t\t\t\t       00    00         \n";
		cout << "\t\t\t\t\t      00      00        \n";
		cout << "\t\t\t\t\t     00        00       \n";
		cout << "\t\t\t\t\t    00 00000000 00      \n";
		cout << "\t\t\t\t\t   00            00     \n";
		cout << "\t\t\t\t\t  00              00    \n";
		break;

	}

	HDC hdc = GetDC(GetConsoleWindow());
	double x, y;
	COLORREF penColor = color;

	// ������ ������������� ��������� �����
	y = y0;
	for (x = x0; x < x0 + 250; x += 1)
	{
		SetPixel(hdc, int(x), int(y), penColor);
		SetPixel(hdc, int(x), 400 + int(y), penColor);
	}

	x = x0;
	for (y = y0; y < y0 + 400; y += 1)
	{
		SetPixel(hdc, int(x), int(y), penColor);
		SetPixel(hdc, 250 + int(x), int(y), penColor);
	}


	ReleaseDC(NULL, hdc);


}