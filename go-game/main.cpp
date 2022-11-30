#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <windows.h>
#include "conio2.h"
#include "FileService.h"
#include "Menu.h"
#include "Board.h"



void new_game()
{
	Menu::display(2, 2);
	Board b(19);
	b.display(Menu::get_longest_line_length()+10, 2);
}

int main()
{
#ifndef __cplusplus
	Conio2_Init();
#endif
	CONSOLE_FONT_INFOEX cfi;
	cfi.dwFontSize.X = 10;
	cfi.dwFontSize.Y = 10;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	settitle("Adrian Sciepura 193350");
	_setcursortype(_NOCURSOR);
	new_game();
	getch();

	return 0;
}
