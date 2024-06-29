#pragma once

#include "Struct.h"

void GotoXY(short int x, short int y);

void TextColor(int Color);

void TextBgColor(int ColorText, int ColorBg);

void DrawRectangle(int PositionX, int PositionY, int Width, int Height, int Color);

int ReturnX();

int ReturnY();

void HidePointer();

void ShowPointer();

//void DrawAppName(int TextColor, int BgColor);

void DrawBoder(int PositionX, int PositionY, int Width, int Height, int Color);

void PrintText(string str, int x, int y);

void FixConsoleWindow();



