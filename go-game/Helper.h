#pragma once
#include "Point.h"
class Helper
{
public:
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

	static void display_border(Point start_pos, Point end_pos)
	{
		gotoxy(start_pos.x, start_pos.y);
		Point temp{ (end_pos.x - start_pos.x), (end_pos.y - start_pos.y) };
		for (int x = 1; x <= temp.y; x++)
		{
			for (int y = 1; y <= temp.x; y++)
			{
				if (x == 1 || x == temp.y)
				{
					textbackground(WHITE);
					putch(' ');
				}
				else if (y == 1 || y == temp.x)
				{
					textbackground(WHITE);
					putch(' ');
				}
				else
					putch(' ');
				textbackground(BLACK);
			}
			gotoxy(start_pos.x, ++start_pos.y);
		}
	}
};

