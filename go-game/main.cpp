#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include "conio2.h"
#include "FileService.h"
#include "Menu.h"
#include "Board.h"
#include "Point.h"
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

void display(const Board *board, char board_position, Point current_pos, int tour)
{
	
	switch (board_position)
	{
		case 'r':
		{
			Menu::display(2, 2, current_pos.x, current_pos.y, tour);
			Point p(Menu::get_longest_line_length() + DISTANCE, 2);
			board->display_area(p);
			gotoxy(Menu::get_longest_line_length() + DISTANCE, 2);
			break;
		}
		case 'l':
		{
			Menu::display(board->get_board_size() + DISTANCE + 2, 2, current_pos.x, current_pos.y, tour);
			Point p(2, 2);
			board->display_area(p);
			gotoxy(2, 2);
			break;
		}
	}
}

void new_game(Board*& board, int board_size)
{
	if (board != NULL)
	{
		delete board;
	}
	board = new Board(board_size);
}

int main()
{
#ifndef __cplusplus
	Conio2_Init();
#endif
	Board* board = NULL;
	char board_position = 'r';
	int board_size = 19;
	bool lock = 0;

	settitle("Adrian Sciepura 193350");
	_setcursortype(_NOCURSOR);
	new_game(board, board_size);
	Point p(0, 0);
	display(board, board_position, p, board->tour);

	Point start(wherex(), wherey());
	Point end(start.x + board_size - 1, start.y + board_size - 1);
	Point curr(start.x, start.y);

	int input = 0;

	while (input != q)
	{
		display(board, board_position, curr, board->tour);

		gotoxy(curr.x, curr.y);
		textcolor(LIGHTBLUE);
		putch('X');
		gotoxy(curr.x, curr.y);
		textcolor(LIGHTGRAY);
		input = getch();

		switch (input) {
			case 0:
			{
				if (!lock)
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
				}
				break;
			}
			case n:
			{
				new_game(board, board_size);
				break;
			}
			case i:
			{
				lock = true;
				break;
			}
			case ENTER:
			{
				if (!board->tour)
				{
					Point p(curr.x - start.x, curr.y - start.y);
					board->set_value_by_pos(p, Board::values::PLAYER_1);
				}
				else
				{
					Point p(curr.x - start.x, curr.y - start.y);
					board->set_value_by_pos(p, Board::values::PLAYER_2);
				}
				board->tour = !board->tour;
				lock = false;
				break;
			}
			case ESC:
			{
				lock = false;
				break;
			}
			case s:
			{
				board->save("gameState.bin");
				break;
			}
			case l:
			{
				clrscr();
				board->load("gameState.bin");
				break;
			}
		}
	}

	delete board;
	return 0;
}