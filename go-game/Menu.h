#ifndef MENU_H
#define MENU_H

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

	Menu(Cursor& cursor, const char* header, int number_of_rows, int border_color = YELLOW);
	void display();
};
#endif