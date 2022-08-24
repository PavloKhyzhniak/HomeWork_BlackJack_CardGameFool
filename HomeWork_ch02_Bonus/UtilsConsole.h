#ifndef UTILSCONSOLE_H /* Страж */
#define UTILSCONSOLE_H /* единственности вхождения - начало */

void init();
void coutColor(const char* text, WORD attributes);
void setCursorPosition(short x, short y);
void myAddConsoleTitle(const wchar_t title[150] = L" ");


void HideConsole();
void ShowConsole();
bool IsConsoleVisible();

void ReDrawConsole(int x = 100, int y = 100, int width = 1024, int height = 600);
void positionClear(int x, int y, int n);
void placeClear(short x, short y, size_t N, size_t Nsetw);
void cls();
void setCursorVisible(bool mode);

void Draw
(
	COLORREF color = RGB(255, 0, 0),
	double min = -100.,
	double max = 100.,
	double delta = 1.,
	double Zero = 100.,
	double func(double, double) = [](double x, double bias) {return (sin(M_PI * x / 25.) + bias); },
	double bias = 0
);

void DrawV
(
	COLORREF color = RGB(255, 0, 0),
	double min = -100.,
	double max = 100.,
	double delta = 1.,
	double Zero = 100.,
	double func(double, double) = [](double x, double bias) {return (sin(M_PI * x / 25.) + bias); },
	double bias = 0
);

void DrawCard
(
	COLORREF color = RGB(255, 0, 0),
	int x0 = 400.,
	int y0 = 50.,
	const char* suitmark = "Hearts",
	int rank=6
);


#endif //UTILSCONSOLE_H

