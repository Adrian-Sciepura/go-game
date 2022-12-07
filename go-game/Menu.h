#pragma once
#include <string.h>
#include "Point.h"
#include "Helper.h"
#include "Cursor.h"

class Menu
{
protected:
	Cursor cursor;
	Point start_pos;
	char* header;
	int number_of_rows;
	int border_color;
	int length;

	Menu(Cursor& cursor, const char* header, int number_of_rows, int border_color = YELLOW)
	{
		this->cursor = cursor;
		this->start_pos = {0,0};
		this->header = _strdup(header);
		this->number_of_rows = number_of_rows;
		this->border_color = border_color;
	}

	void display()
	{
		text_info* ti = new text_info;
		gettextinfo(ti);
		start_pos.x = (ti->screenwidth - length) / 2;
		start_pos.y = (ti->screenheight - number_of_rows) / 2;
		Point end_pos(start_pos.x + length, start_pos.y + number_of_rows + 2);
		Helper::display_border(start_pos, end_pos, border_color);

		gotoxy(start_pos.x + (length - strlen(header)) / 2, start_pos.y + 2);
		textcolor(CYAN);
		cputs(header);
		textcolor(WHITE);
	}
};



class Input_Menu : Menu
{
private:
	char* buffer;
	int index;
public:
	Input_Menu(Cursor& cursor, const char* header, int border_color)
		: Menu(cursor, header, 5, border_color)
	{
		this->buffer = new char[11];
		this->index = 0;
		length = 25;

		int header_len = strlen(header);
		if (header_len > length)
			length = header_len + 4;
	}

	~Input_Menu()
	{
		clrscr();
	}

	void display()
	{
		clrscr();
		Menu::display();
	}

	char* handle_input(int input)
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
};



enum element_type { SELECTION, INPUT };

struct Selection_Menu_Element
{
	char* content;
	int length;
	char* return_value;
	element_type type;

	Selection_Menu_Element(element_type type, const char* content, const char* return_value = NULL)
	{
		this->content = _strdup(content);
		this->length = strlen(content);
		this->return_value = _strdup(return_value);
		this->type = type;
	}
};



class Selection_Menu : Menu
{
private:
	Selection_Menu_Element* elements;
	int number_of_elements;
	int spacing;
	int position;
	int elements_length;

public:
	Selection_Menu(Selection_Menu_Element* elements, int number_of_elements, int spacing, Cursor& cursor, const char* header, int border_color)
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

	~Selection_Menu()
	{
		clrscr();
	}

	void update_cursor()
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

	void display()
	{
		clrscr();
		Menu::display();
		cursor.limit_1.x = start_pos.x + (length - elements_length) / 2 + 1;
		cursor.limit_1.y = start_pos.y + 5;
		cursor.limit_2.x = start_pos.x + elements_length + 1;
		update_cursor();
	}

	char* handle_input(int input)
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
};