#include "Input_Menu.h"

Input_Menu::Input_Menu(Cursor& cursor, const char* header, int border_color)
	: Menu(cursor, header, 5, border_color)
{
	this->buffer = new char[11];
	this->index = 0;
	length = 25;

	int header_len = strlen(header);
	if (header_len > length)
		length = header_len + 4;
}

Input_Menu::~Input_Menu()
{
	clrscr();
}

void Input_Menu::display()
{
	clrscr();
	Menu::display();
}

char* Input_Menu::handle_input(int input)
{
	if (input == buttons::ENTER)
	{
		return buffer;
	}
	else if (input == buttons::BACKSPACE)
	{
		if (index > 0)
		{
			buffer[index] = '\0';
			index--;
			gotoxy(start_pos.x + 7 + index, start_pos.y + 4);
			putch(' ');
		}
	}
	else
	{
		if (index < 11)
		{
			buffer[index] = input;
			gotoxy(start_pos.x + 7 + index, start_pos.y + 4);
			putch(input);
			index++;
			buffer[index] = '\0';
		}
	}
	return NULL;
}