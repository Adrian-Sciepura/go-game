#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include "Helper.h"
#include "conio2.h"

//types of fields which are on the board
enum field_type
{
	INTERIOR = '0',
	PLAYER_1 = '1',
	PLAYER_2 = '2',
	OUT_OF_RANGE = '#'
};

class Board
{
private:
	__int8 size;
	char** area;
public:
	int display_size;
	bool tour;
	Point page_start;
	Point page_end;

	Board(int size, bool tour = 0);
	~Board();
	void display_area(Point display_pos);
	int get_board_size() const;
	char get_value_by_pos(Point p) const;
	void set_value_by_pos(Point p, char val);
};
#endif