#pragma once
#include "Point.h"
#include "Helper.h"
#include "Board.h"
struct Cursor
{
	Point limit_1;
	Point limit_2;
	Point absolute_pos;
	Point relative_pos;
	char symbol;
	int pageX;
	int pageY;
	int board_size;
	bool refresh;

	Cursor()
	{
		this->symbol = 'X';
		this->pageX = 0;
		this->pageY = 0;
		this->refresh = false;
	}

	void display()
	{
		gotoxy(absolute_pos.x, absolute_pos.y);
		textcolor(YELLOW);
		putch(symbol);
		gotoxy(absolute_pos.x, absolute_pos.y);
		textcolor(LIGHTGRAY);
	}

	void move(Board*& board, int input)
	{
		switch (input)
		{
			case buttons::UP_ARROW:
			{
				if (absolute_pos.y != limit_1.y)
					absolute_pos.y -= 1;
				else
					if (pageY > 0)
					{
						pageY--;
						board->start.y = pageY * board->display_size;
						int temp = (pageY + 1) * board->display_size;
						board->end.y = temp >= board_size ? board_size : temp;
						limit_2 = { limit_1.x + ((board->end.x - 1) % board->display_size) * 2, limit_1.y + ((board->end.y - 1) % board->display_size) };
						absolute_pos.y = limit_2.y;
						refresh = true;
					}
				break;
			}
			case buttons::DOWN_ARROW:
			{
				if (absolute_pos.y != limit_2.y)
					absolute_pos.y += 1;
				else
					if (relative_pos.y + 1 < board_size)
					{
						pageY++;
						board->start.y = pageY * board->display_size;
						int temp = (pageY + 1) * board->display_size;
						board->end.y = temp >= board_size ? board_size : temp;
						limit_2 = { limit_1.x + ((board->end.x - 1) % board->display_size) * 2, limit_1.y + ((board->end.y - 1) % board->display_size) };
						absolute_pos.y = limit_1.y;
						refresh = true;
					}
				break;
			}
			case buttons::LEFT_ARROW:
			{
				if (absolute_pos.x != limit_1.x)
					absolute_pos.x -= 2;
				else
					if (pageX > 0)
					{
						pageX--;
						board->start.x = pageX * board->display_size;
						int temp = (pageX + 1) * board->display_size;
						board->end.x = temp >= board_size ? board_size : temp;
						limit_2 = { limit_1.x + ((board->end.x - 1) % board->display_size) * 2, limit_1.y + ((board->end.y - 1) % board->display_size) };
						absolute_pos.x = limit_2.x;
						refresh = true;
					}
				break;
			}
			case buttons::RIGHT_ARROW:
			{
				if (absolute_pos.x != limit_2.x)
					absolute_pos.x += 2;
				else
					if (relative_pos.x + 1 < board_size)
					{
						pageX++;
						board->start.x = pageX * board->display_size;
						int temp = (pageX + 1) * board->display_size;
						board->end.x = temp >= board_size ? board_size : temp;
						limit_2 = { limit_1.x + ((board->end.x - 1) % board->display_size) * 2, limit_1.y + ((board->end.y - 1) % board->display_size) };
						absolute_pos.x = limit_1.x;
						refresh = true;
					}
				break;
			}
		}

		relative_pos = { ((absolute_pos.x - limit_1.x) / 2) + pageX * PAGE_LENGTH, (absolute_pos.y - limit_1.y) + pageY * PAGE_LENGTH };
	}
};