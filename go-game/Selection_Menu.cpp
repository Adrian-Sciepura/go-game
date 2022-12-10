#include "Selection_Menu.h"

Selection_Menu::Selection_Menu(Selection_Menu_Element* elements, int number_of_elements, int spacing, Cursor& cursor, const char* header, int border_color)
	: Menu(cursor, header, 6, border_color)
{
	this->elements = elements;
	this->number_of_elements = number_of_elements;
	this->spacing = spacing;
	this->position = 0;

	elements_length = (number_of_elements - 1) * spacing;
	for (int i = 0; i < number_of_elements; i++)
	{
		elements_length += elements[i].length;
	}

	if (strlen(header) > elements_length)
	{
		length = strlen(header) + 4;
	}
	else
	{
		length = elements_length + 2 * spacing;
	}
}

Selection_Menu::~Selection_Menu()
{
	delete[] elements;
	clrscr();
}

void Selection_Menu::update_cursor()
{
	textcolor(WHITE);
	int temp = cursor.limit_1.x - 1;

	for (int i = 0; i < number_of_elements; i++)
	{
		gotoxy(temp + i * spacing - 1, cursor.limit_1.y);
		putch(' ');
		if (i == position)
		{
			cursor.absolute_pos.x = temp + i * spacing - 1;
			cursor.absolute_pos.y = start_pos.y + 5;
		}
		temp += (elements[i].length);
		cputs(elements[i].content);
	}

	cursor.display();
}

void Selection_Menu::display()
{
	clrscr();
	Menu::display();
	cursor.limit_1.x = start_pos.x + (length - elements_length) / 2 + 1;
	cursor.limit_1.y = start_pos.y + 5;
	cursor.limit_2.x = start_pos.x + elements_length + 1;
	update_cursor();
}

char* Selection_Menu::handle_input(int input)
{
	switch (input)
	{
		case 0:
		{
			input = getch();
			switch (input)
			{
			case buttons::LEFT_ARROW:
			{
				if (position > 0)
					position--;
				break;
			}
			case buttons::RIGHT_ARROW:
			{
				if (position < number_of_elements - 1)
					position++;
				break;
			}
			}
			update_cursor();
			break;
		}
		case buttons::ENTER:
		{
			if (elements[position].type == SELECTION)
			{
				return elements[position].return_value;
			}
			else
			{
				Input_Menu input_menu(cursor, header, YELLOW);

				input_menu.display();

				char* text = NULL;
				while (text == NULL)
				{
					input = getch();
					text = input_menu.handle_input(input);
				}

				return text;
			}
			break;
		}
	}
	return NULL;
}