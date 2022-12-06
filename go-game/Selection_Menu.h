#pragma once
#include "Point.h"
#include "conio2.h"
#include "Cursor.h"
#include "Helper.h"
#include <string.h>
#include <malloc.h>
struct Selection_Menu_Element
{
	char* content;
	int length;
	int return_value;

	Selection_Menu_Element(const char* content, int return_value)
	{
		this->content = _strdup(content);
		this->length = strlen(content);
		this->return_value = return_value;
	}
};

class Selection_Menu
{
private:
	Selection_Menu_Element* elements;
	Point start_pos;
	int number_of_elements;
	char* header;
	int spacing;
	int position;

public:
	Selection_Menu(Selection_Menu_Element* elements, int number_of_elements, const char* header, int position, int spacing)
	{
		this->elements = elements;
		this->number_of_elements = number_of_elements;
		this->header = _strdup(header);
		this->position = position;
		this->spacing = spacing;
		this->start_pos = { 0, 0 };
	}

	~Selection_Menu()
	{
		free(elements);
	}

	void update_cursor(Cursor& cursor)
	{
		textcolor(WHITE);
		int temp = cursor.limit_1.x - 1;

		for (int i = 0; i < number_of_elements; i++)
		{
			gotoxy(temp + i * spacing-1, start_pos.y + 5);
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

	void display(Cursor& cursor, int border_color, int header_color = WHITE)
	{
		int full_elements_length = (number_of_elements - 1)*spacing;
		for (int i = 0; i < number_of_elements; i++)
		{
			full_elements_length += elements[i].length;
		}

		int final_length;
		
		if (strlen(header) > full_elements_length)
		{
			final_length = strlen(header) + 2 * spacing;
		}
		else
		{
			final_length = full_elements_length + 2*spacing;
		}

		text_info* ti = new text_info;
		gettextinfo(ti);
		start_pos.x = (ti->screenwidth - final_length)/2;
		start_pos.y = (ti->screenheight - 8)/2;
		Point end_pos(start_pos.x + final_length, start_pos.y + 8);
		Helper::display_border(start_pos, end_pos, border_color);
		

		gotoxy(start_pos.x + (final_length - strlen(header)) / 2, start_pos.y + 2);
		textcolor(header_color);
		cputs(header);
		textcolor(WHITE);

		cursor.limit_1.x = start_pos.x + (final_length - full_elements_length) / 2 + 1;
		cursor.limit_1.y = start_pos.y + 5;
		cursor.limit_2.x = start_pos.x + full_elements_length + 1;

		update_cursor(cursor);
		delete ti;
	}



	int move(Cursor& cursor, int input)
	{ 
		switch (input)
		{
			case 0:
			{
				input = getch();
				switch (input)
				{
					case Helper::LEFT_ARROW:
					{
						if (position > 0)
							position--;
						break;
					}
					case Helper::RIGHT_ARROW:
					{
						if (position < number_of_elements-1)
							position++;
						break;
					}
				}
				update_cursor(cursor);
				break;
			}
			case Helper::ENTER:
			{
				return elements[position].return_value;
				break;
			}
		}
		return -1;
	}
};