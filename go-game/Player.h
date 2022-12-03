#pragma once
#include "Point.h"
#include "Board.h"
class Player
{
private:
	int id;
	int score;
public:
	Player(int id)
	{
		this->id = id;
		this->score = 0;
	}

	bool set_stone(Board *b, Point p)
	{
		char value_of_position = b->get_value_by_pos(p);

		if (value_of_position == Board::values::INTERIOR)
		{

		}


		return false;
	}
};

