#pragma once
#include "Point.h"
#include "Helper.h"
struct Cursor
{
	Point limit_1;
	Point limit_2;
	Point absolute_pos;
	Point relative_pos;
	char symbol = 'X';
	int jumpX = 2;
	int jumpY = 1;

	void display()
	{
		gotoxy(absolute_pos.x, absolute_pos.y);
		textcolor(YELLOW);
		putch(symbol);
		gotoxy(absolute_pos.x, absolute_pos.y);
		textcolor(LIGHTGRAY);
	}

	void move(int input)
	{
		switch (input)
		{
			case buttons::UP_ARROW:
			{
				if (absolute_pos.y != limit_1.y)
					absolute_pos.y -= jumpY;
				break;
			}
			case buttons::DOWN_ARROW:
			{
				if (absolute_pos.y != limit_2.y)
					absolute_pos.y += jumpY;
				break;
			}
			case buttons::LEFT_ARROW:
			{
				if (absolute_pos.x != limit_1.x)
					absolute_pos.x -= jumpX;
				break;
			}
			case buttons::RIGHT_ARROW:
			{
				if (absolute_pos.x != limit_2.x)
					absolute_pos.x += jumpX;
				break;
			}
		}

		relative_pos = { (absolute_pos.x - limit_1.x) /2, absolute_pos.y - limit_1.y};
	}
};