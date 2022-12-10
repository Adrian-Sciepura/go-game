#ifndef Legend_H
#define Legend_H
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <string.h>
#include "conio2.h"
#include "Helper.h"
#include "Point.h"
#include "Cursor.h"

class Legend
{
private:
	Point display_pos;
	char* menu_text;
	int* lines_length;
	int number_of_lines;
	unsigned char* separator;
	int longest_line;
	int last_y;

public:
	Legend();
	~Legend();
	void set_display_pos(Point start_pos);
	void display_separator();
	void display();
	void update(Cursor& cursor, int tour, int p1_score, int p2_score);
	void display_element(const char* header, const char* text, int y);
	int get_longest_line_length();
};
#endif