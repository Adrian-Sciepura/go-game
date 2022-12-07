#pragma once
#include "Point.h"

enum buttons
{
	UP_ARROW = 0x48,
	LEFT_ARROW = 0x4B,
	DOWN_ARROW = 0x50,
	RIGHT_ARROW = 0x4D,
	ENTER = 0x0d,
	ESC = 0x1B,
	BACKSPACE = 0x8,
	q = 0x71,
	n = 0x6E,
	i = 0x69,
	s = 0x73,
	l = 0x6C,
	f = 0x66
};

class Helper
{
public:
	static void display_border(Point start_pos, Point end_pos, int border_color)
	{
		Point corners[4] =
		{
			start_pos, {end_pos.x-1, start_pos.y},
			{start_pos.x, end_pos.y-1}, end_pos-1
		};

		unsigned char symbols[4] =
		{
			218, 191, 192, 217
		};

		gotoxy(start_pos.x, start_pos.y);
		Point temp{ (end_pos.x - start_pos.x), (end_pos.y - start_pos.y) };
		for (int x = 1; x <= temp.y; x++)
		{
			for (int y = 1; y <= temp.x; y++)
			{
				if (x == 1 || x == temp.y)
				{
					textcolor(border_color);
					putch(196);
				}
				else if (y == 1 || y == temp.x)
				{
					textcolor(border_color);
					putch(179);
				}
				else
					putch(' ');
				textcolor(WHITE);
			}
			gotoxy(start_pos.x, ++start_pos.y);
		}

		for (int i = 0; i < 4; i++)
		{
			textcolor(border_color);
			gotoxy(corners[i].x, corners[i].y);
			putch(symbols[i]);
		}
	}

	static int convert_string_to_int(const char* str)
	{
		char* end;
		return strtol(str, &end, 10);
	}
};

