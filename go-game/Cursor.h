#pragma once
#include "Point.h"
#include "Helper.h"
struct Cursor
{
	Point limit_1;
	Point limit_2;
	Point current_pos;
	char symbol = 'X';
	int jump = 1;

	void display()
	{
		gotoxy(current_pos.x, current_pos.y);
		textcolor(LIGHTBLUE);
		putch(symbol);
		gotoxy(current_pos.x, current_pos.y);
		textcolor(LIGHTGRAY);
	}

	void move(int input)
	{
		switch (input)
		{
			case Helper::UP_ARROW:
			{
				if (current_pos.y != limit_1.y)
					current_pos.y--;
				break;
			}
			case Helper::DOWN_ARROW:
			{
				if (current_pos.y != limit_2.y)
					current_pos.y++;
				break;
			}
			case Helper::LEFT_ARROW:
			{
				if (current_pos.x != limit_1.x)
					current_pos.x--;
				break;
			}
			case Helper::RIGHT_ARROW:
			{
				if (current_pos.x != limit_2.x)
					current_pos.x++;
				break;
			}
		}
	}
};