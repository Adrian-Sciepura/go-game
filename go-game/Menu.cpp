#include "Menu.h"

Menu::Menu(Cursor& cursor, const char* header, int number_of_rows, int border_color)
{
	this->cursor = cursor;
	this->start_pos = { 0,0 };
	this->header = _strdup(header);
	this->number_of_rows = number_of_rows;
	this->border_color = border_color;
	this->length = 0;
}

void Menu::display()
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
	delete ti;
}