#include <Windows.h>
#include <string>

using namespace std;

void setConsoleColor(string color) {
	if (color == "white") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	else if (color == "yellow") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	else if (color == "purple") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	else if (color == "red") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else if (color == "cyan") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	else if (color == "green") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	else if (color == "blue") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}

void setConsoleSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setConsoleFontSize(int size) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = size;                // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void setConsoleTitle(string name) {
	string title(name);
	SetConsoleTitle(title.c_str());
}