#include "ConsoleProcess.h"
#include "Struct.h"

void GotoXY(short int x, short int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void TextColor(int Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

void TextBgColor(int ColorText, int ColorBg)//Bg=Background
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (ColorBg << 4) | ColorText);
}

void DrawBoder(int PositionX, int PositionY, int Width, int Height, int Color)
{
	TextBgColor(0, Color);
	for (int x = 0; x < Width; x++)
	{
		GotoXY(PositionX + x, PositionY);
		cout << ".";
		GotoXY(PositionX + x, PositionY + Height - 1);
		cout << " ";
	}
	for (int y = 0; y < Height; y++)
	{
		GotoXY(PositionX, PositionY + y);
		cout << " ";
		GotoXY(PositionX + Width - 1, PositionY + y);
		cout << " ";
	}
	GotoXY(44, 0);
	TextBgColor(0, Color);
}

void DrawRectangle(int PositionX, int PositionY, int Width, int Height, int Color)
{
	TextBgColor(0, Color);
	GotoXY(PositionX, PositionY);
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			GotoXY(PositionX + x, PositionY + y);
			cout << " ";
		}
	}
	GotoXY(44, 0);
}

int ReturnX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

int ReturnY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void HidePointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void ShowPointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void PrintText(string str, int x, int y) {
	GotoXY(x, y);
	cout << str << endl;
}

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
