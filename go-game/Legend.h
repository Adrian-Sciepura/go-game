#include <cstdio>
#include "conio2.h"
#include "Helper.h"
#include "Point.h"
#ifndef Legend_H
#define Legend_H

class Legend
{
private:
	static char* menu_text;
	static int menu_text_lines;
	static int longest_line;

	static void Init()
	{
		if (menu_text != NULL)
		{
			return;
		}

		menu_text = Helper::read_text_file("menuContent.txt");
		
		int i = 0;
		int longest = 0;
		int current = 0;
		while (menu_text[i] != '\0')
		{
			if (menu_text[i] == '\n')
			{
				if (longest < current)
				{
					longest = current;
				}
				current = 0;
			}
			else
			{
				current++;
			}
			i++;
		}
		longest_line = longest;
	}

public:

	static void display(Point start_pos, Point absolute_pos, int tour)
	{
		Init();
		int i = 0;
		gotoxy(start_pos.x, start_pos.y);
		while (menu_text[i] != '\0')
		{
			if (menu_text[i] == '\n')
			{
				gotoxy(start_pos.x, start_pos.y+=2);
			}
			else
			{
				putch(menu_text[i]);
			}
			i++;
		}
		char current_coords_text[30];
		sprintf(current_coords_text, "x: %d y: %d \n\n", absolute_pos.x, absolute_pos.y);
		cputs(current_coords_text);
		gotoxy(start_pos.x, start_pos.y+=2);
		char actual_tour_text[30];
		sprintf(actual_tour_text, "Tour: Player %d", tour+1);
		cputs(actual_tour_text);
	}

	static int get_longest_line_length()
	{
		Init();
		return longest_line;
	}
};

char* Legend::menu_text = NULL;
int Legend::longest_line = -1;
int Legend::menu_text_lines = -1;

#endif