#ifndef HELPER_H
#define HELPER_H
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <stdlib.h>
#include "Point.h"

//maximum size of visible board
#define PAGE_LENGTH 26
//distance between legend and board
#define DISTANCE 10
//location of the board on the screen relative to the legend
#define BOARD_LOCATION 'r'

//ascii codes of used buttons
enum buttons
{
	UP_ARROW = 0x48,
	LEFT_ARROW = 0x4B,
	DOWN_ARROW = 0x50,
	RIGHT_ARROW = 0x4D,
	ENTER = 0x0d,
	ESC = 0x1B,
	BACKSPACE = 0x8,
	q = 0x71,
	n = 0x6E,
	i = 0x69,
	s = 0x73,
	l = 0x6C,
	f = 0x66,
	h = 0x68
};

class Helper
{
public:
	static void display_border(Point start_pos, Point end_pos, int border_color);
	static int convert_string_to_int(const char* str);
	static char* read_text_file(const char* file_name);
};
#endif