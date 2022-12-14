#include "Legend.h"

Legend::Legend()
{
	this->last_y = 0;
	this->display_pos = { 0,0 };
	this->number_of_lines = 0;
	this->lines_length = new int[20];
	menu_text = Helper::read_text_file("menuContent.txt");
	int i = 0;
	int current = 0;
	while (menu_text[i] != '\0')
	{
		if (menu_text[i] == '\n')
		{
			if (longest_line < current)
			{
				longest_line = current;
			}
			lines_length[number_of_lines] = current;
			number_of_lines++;
			current = 0;
		}
		else
			current++;
		i++;
	}

	separator = new unsigned char[longest_line + 2];
	for (int i = 0; i < longest_line + 1; i++)
	{
		separator[i] = 196;
	}
	separator[0] = 195;
	separator[longest_line + 1] = 180;
}

Legend::~Legend()
{
	delete[] menu_text;
	delete[] separator;
	delete[] lines_length;
}

void Legend::set_display_pos(Point start_pos)
{
	this->display_pos = start_pos;
}

void Legend::display_separator()
{
	textcolor(WHITE);
	for (int i = 0; i < longest_line + 2; i++)
	{
		putch(separator[i]);
	}
}

void Legend::display()
{
	Point start_pos = display_pos;
	int i = 0;
	int line = 0;
	gotoxy(start_pos.x + 2 + (longest_line - lines_length[line]) / 2, start_pos.y);
	while (menu_text[i] != '\0')
	{
		char current_element = menu_text[i];

		if (current_element == '\n')
		{
			line++;
			gotoxy(start_pos.x + 2 + (longest_line - lines_length[line]) / 2, ++start_pos.y);
		}
		else if (current_element == '%')
		{
			gotoxy(start_pos.x + 1, ++start_pos.y);
			display_separator();
			start_pos.y++;
		}
		else
			putch(current_element);
		i++;
	}
	last_y = start_pos.y;
}

void Legend::update(Cursor& cursor, int tour, int p1_score, int p2_score)
{
	textcolor(LIGHTBLUE);
	char current_coords_text[30];
	sprintf(current_coords_text, " x: %d y: %d \0", cursor.relative_pos.x, cursor.relative_pos.y);
	display_element("Position", current_coords_text, 0);

	textcolor(LIGHTBLUE);
	char current_tour_text[30];
	sprintf(current_tour_text, "Player %d", tour + 1);
	display_element("Tour", current_tour_text, 3);

	textcolor(LIGHTBLUE);
	char current_score[30];
	sprintf(current_score, "Player 1: %d Player 2: %d", p1_score, p2_score);
	display_element("Score", current_score, 6);
}

void Legend::display_element(const char* header, const char* text, int y)
{
	gotoxy(display_pos.x + 2 + (longest_line - strlen(header)) / 2, last_y + y);
	cputs(header);
	gotoxy(display_pos.x + 2 + (longest_line - strlen(text)) / 2, last_y + y + 1);
	cputs(text);
	gotoxy(display_pos.x + 1, last_y + y + 2);
	display_separator();
}

int Legend::get_longest_line_length()
{
	return longest_line;
}