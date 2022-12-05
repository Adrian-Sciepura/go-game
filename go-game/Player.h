#pragma once
#include "Point.h"
#include "Board.h"
class Player
{
private:
	char id;
public:
	int score;

	Player(char id)
	{
		this->id = id;
		this->score = 0;
	}

	bool set_stone(Board* board, Point p)
	{
		char value_of_position = board->get_value_by_pos(p);

		if (value_of_position == Board::INTERIOR)
		{
			board->set_value_by_pos(p, this->id);
			return true;
		}

		return false;
	}
};

