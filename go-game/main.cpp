#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include "conio2.h"
#include "FileService.h"
#include "Menu.h"
#include "Board.h"
#define DISTANCE 10

enum buttons
{
	UP_ARROW = 0x48,
	LEFT_ARROW = 0x4B,
	DOWN_ARROW = 0x50,
	RIGHT_ARROW = 0x4D,
	ENTER = 0x0d,
	ESC = 0x1B,
	q = 0x71,
	n = 0x6E,
	i = 0x69,
	s = 0x73,
	l = 0x6C,
	f = 0x66
};

struct Point
{
	int x;
	int y;

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

void display(const Board *board, char board_position)
{
	switch (board_position)
	{
		case 'r':
		{
			Menu::display(2, 2);
			board->display(Menu::get_longest_line_length() + DISTANCE, 2);
			gotoxy(Menu::get_longest_line_length() + DISTANCE + 1, 3);
			break;
		}
		case 'l':
		{
			Menu::display(board->get_board_size() + DISTANCE + 2, 2);
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
	int board_size;
	board_size = 19;

	settitle("Adrian Sciepura 193350");
	_setcursortype(_NOCURSOR);
	new_game(board, board_size, board_position);

	Point start(wherex(), wherey());
	Point end(start.x + board_size - 1, start.y + board_size - 1);
	Point curr(start.x, start.y);

	int input = 0;

	while (input != q)
	{
		display(board, board_position);

		gotoxy(curr.x, curr.y);
		textcolor(LIGHTBLUE);
		putch('X');
		gotoxy(curr.x, curr.y);
		textcolor(LIGHTGRAY);
		input = getch();


		switch (input) {
			case 0:
			{
				input = getch();

				switch (input)
				{
					case UP_ARROW:
					{
						if (curr.y != start.y)
							curr.y--;
						break;
					}
					case DOWN_ARROW:
					{
						if (curr.y != end.y)
							curr.y++;
						break;
					}
					case LEFT_ARROW:
					{
						if (curr.x != start.x)
							curr.x--;
						break;
					}
					case RIGHT_ARROW:
					{
						if (curr.x != end.x)
							curr.x++;
						break;
					}
				}
				break;
			}
			case n:
			{
				new_game(board, board_size, board_position);
				break;
			}
			case i:
			{
				board->set_element_by_pos(curr.x - start.x, curr.y - start.y, 'o');
				break;
			}
		}
	}

	delete board;
	return 0;
}