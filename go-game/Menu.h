#include <cstdio>
#include"conio2.h"
#include "FileService.h"
#ifndef Menu_H
#define Menu_H

class Menu
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

		menu_text = FileService::read_file("menuContent.txt");
		
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

	static void display(int start_x, int start_y, int current_x, int current_y, int tour = 0)
	{
		Init();
		int i = 0;
		gotoxy(start_x, start_y);
		while (menu_text[i] != '\0')
		{
			if (menu_text[i] == '\n')
			{
				gotoxy(start_x, start_y+=2);
			}
			else
			{
				putch(menu_text[i]);
			}
			i++;
		}
		char current_coords_text[30];
		sprintf(current_coords_text, "x: %d y: %d \n\n", current_x, current_y);
		cputs(current_coords_text);

		char actual_tour_text[30];
		sprintf(actual_tour_text, " Tour: Player %d", tour+1);
		cputs(actual_tour_text);
	}

	static int get_longest_line_length()
	{
		return longest_line;
	}
};

char* Menu::menu_text = NULL;
int Menu::longest_line = -1;
int Menu::menu_text_lines = -1;

#endif