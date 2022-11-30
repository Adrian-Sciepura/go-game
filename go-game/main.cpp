#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include "conio2.h"
#include "FileService.h"
#include "Menu.h"
#include "Board.h"
#define SPACE 10


void display(const Board *board, char board_position)
{
	clrscr();
	switch (board_position)
	{
		case 'r':
		{
			Menu::display(2, 2);
			board->display(Menu::get_longest_line_length() + SPACE, 2);
			gotoxy(Menu::get_longest_line_length() + SPACE + 1, 3);
			break;
		}
		case 'l':
		{
			Menu::display(board->get_board_size() + SPACE + 2, 2);
			board->display(2, 2);
			gotoxy(3, 3);
			break;
		}
	}
}

void new_game(Board*& board, int board_size, char board_position)
{
	if (board != NULL)
	{
		delete board;
	}
	board = new Board(board_size);
	display(board, board_position);
}

int main()
{
#ifndef __cplusplus
	Conio2_Init();
#endif
	Board* board = NULL;
	char board_position = 'r';
	int board_size, start_x, start_y, end_x, end_y, curr_x, curr_y;
	board_size = 19;

	settitle("Adrian Sciepura 193350");
	_setcursortype(_SOLIDCURSOR);
	new_game(board, board_size, board_position);
	start_x = wherex();
	start_y = wherey();
	end_x = start_x + board_size - 1;
	end_y = start_y + board_size - 1;
	curr_x = start_x;
	curr_y = start_y;

	int input = 0;
	while (input != 'q')
	{
		gotoxy(curr_x, curr_y);
		input = getch();

		if (input == 0) {
			input = getch();
			if (input == 0x48) 
			{
				if(curr_y != start_y)
					curr_y--;
			}
			else if (input == 0x50) 
			{
				if (curr_y != end_y)
					curr_y++;
			}
			else if (input == 0x4b) 
			{
				if (curr_x != start_x)
					curr_x--;
			}
			else if (input == 0x4d) 
			{
				if (curr_x != end_x)
					curr_x++;
			}
		}
	}
	return 0;
}
