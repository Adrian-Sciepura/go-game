#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include "conio2.h"
#include "FileService.h"
#include "Menu.h"
#include "Board.h"
#include "Point.h"
#include "Selection_Menu.h"
#include "Cursor.h"
#include "Player.h"
#define DISTANCE 10

void display(Board* board, Cursor& cursor, char board_location)
{
	Point menu_display_pos;
	Point board_display_pos;
	switch (board_location)
	{
		case 'r':
		{
			menu_display_pos.x = 2;
			menu_display_pos.y = 2;

			cursor.limit_1.x = Menu::get_longest_line_length() + DISTANCE+1;
			cursor.limit_1.y = 3;

			break;
		}
		case 'l':
		{
			menu_display_pos.x = board->get_board_size() + DISTANCE + 2;
			menu_display_pos.y = 2;

			cursor.limit_1.x = 2;
			cursor.limit_1.y = 2;
			break;
		}
	}

	cursor.limit_2 = {cursor.limit_1.x + board->get_board_size()-1, cursor.limit_1.y + board->get_board_size()-1 };
	Menu::display(menu_display_pos, cursor.current_pos, board->tour);
	board->display_area(cursor.limit_1);
}

void new_game(Board*& board, int board_size)
{
	if (board != NULL)
	{
		delete board;
	}
	board = new Board(board_size);
}

int select_size()
{
	int input;
	int result = -1;
	Cursor cursor;

	Selection_Menu_Element* elements = (Selection_Menu_Element*)malloc(4 * sizeof(Selection_Menu_Element));
	elements[0] = {"9x9", 9};
	elements[1] = {"13x13", 13};
	elements[2] = {"19x19", 19};
	elements[3] = {"Other", 0};

	Selection_Menu board_size_selector { elements, 4, "Choose board size", 0, 3};
	board_size_selector.display(cursor);

	while (result == -1)
	{
		input = getch();
		result = board_size_selector.move(cursor, input);
	}

	return result;
}

void init(Board*& board, int& board_size)
{
#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Adrian Sciepura 193350");
	_setcursortype(_NOCURSOR);
	board_size = select_size();
	new_game(board, board_size);
	clrscr();
}

int main()
{
	Board* board = NULL;
	Cursor cursor;
	Player p1(Board::PLAYER_1);
	Player p2(Board::PLAYER_2);
	char board_location = 'r';
	int board_size = 19;
	int input = 0;
	bool lock = false;

	init(board, board_size);
	
	display(board, cursor, board_location);
	Helper::display_border(cursor.limit_1 - 1, cursor.limit_1 + board->get_board_size() + 1);
	cursor.current_pos = cursor.limit_1;

	while (input != Helper::q)
	{
		display(board, cursor, board_location);
		cursor.display();
		input = getch();

		switch (input)
		{
			case 0:
			{
				if (lock == false)
				{
					input = getch();
					cursor.move(input);
				}
				break;
			}
			case Helper::i:
			{
				lock = true;
				break;
			}
			case Helper::ENTER:
			{
				Point temp(cursor.current_pos - cursor.limit_1);
				bool success;
				if (board->tour)
					success = p2.set_stone(board, temp);
				else
					success = p1.set_stone(board, temp);

				if (success)
				{
					board->tour = !board->tour;
					lock = false;
				}
				break;
			}
			case Helper::ESC:
			{
				lock = false;
				break;
			}
			case Helper::s:
			{
				board->save("gameState.bin");
				break;
			}
			case Helper::l:
			{
				board->load("gameState.bin");
				break;
			}
			case Helper::n:
			{
				new_game(board, board_size);
				break;
			}
		}
	}
	getch();
}