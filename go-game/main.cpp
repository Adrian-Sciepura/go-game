#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "conio2.h"
#include "Menu.h"
#include "Cursor.h"
#include "Game_Controller.h"
#include "Input_Menu.h"
#include "Selection_Menu.h"

int size_selector()
{
	Cursor cursor;
	_setcursortype(_NOCURSOR);
	int input;
	char* result = NULL;

	Selection_Menu_Element* elements = new Selection_Menu_Element[4]{ 
		{ SELECTION, "9x9", "9" },
		{ SELECTION, "13x13", "13" },
		{ SELECTION, "19x19", "19" },
		{ INPUT, "Other" }
	};

	Selection_Menu board_size_selector
	{
		elements, 4, 3,
		cursor,
		"Choose board size",
		YELLOW
	};

	board_size_selector.display();

	while (result == NULL)
	{
		input = getch();
		result = board_size_selector.handle_input(input);
	}

	return Helper::convert_string_to_int(result);
}

char* file_selector()
{
	Cursor cursor;
	_setcursortype(_NOCURSOR);
	Input_Menu file_selector{ cursor, "Enter file name", YELLOW };
	file_selector.display();
	char* buffer = NULL;
	int input;

	while (buffer == NULL)
	{
		input = getch();
		buffer = file_selector.handle_input(input);
	}

	int i = 0;
	char* result = new char[16];

	return strcat(buffer, ".bin");
}

void show_message(const char* message)
{
	Cursor cursor;
	Selection_Menu_Element* elements = new Selection_Menu_Element[1]
	{
		{ SELECTION, "OK", 0 }
	};

	Selection_Menu sm
	{
		elements, 1, 0, cursor, message, RED
	};
	sm.display();
	getch();
}

int main()
{
	Game_Controller game(size_selector(), BOARD_LOCATION);
	int input = 0;
	game.setup_points();
	game.display();
	settitle("Adrian Sciepura 193350");
	_setcursortype(_NOCURSOR);

	while (input != buttons::q)
	{
		game.update();
		input = getch();
		switch (input)
		{
			case buttons::s:
			{
				char* file_name = file_selector();
				if (game.save(file_name) == false)
				{
					show_message("An error has occurred while saving the file");
				}
				game.display();
				break;
			}
			case buttons::l:
			{
				char* file_name = file_selector();
				if (game.load(file_name) == false)
				{
					show_message("An error has occurred while reading the file");
				}
				game.setup_points();
				game.display();
				break;
			}
			case buttons::n:
			{
				game.new_game();
				break;
			}
			default:
			{
				game.handle_input(input);
				break;
			}
		}
	}
	show_message("Thanks for playing");
}