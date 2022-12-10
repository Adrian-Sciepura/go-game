#ifndef CURSOR_H
#define CURSOR_H

#include "Point.h"
#include "Helper.h"
#include "Board.h"
struct Cursor
{
	Point limit_1;
	Point limit_2;
	Point absolute_pos;
	Point relative_pos;
	char symbol;
	int pageX;
	int pageY;
	int board_size;
	bool refresh;

	Cursor();
	void display();
	void move(Board*& board, int input);
};
#endif