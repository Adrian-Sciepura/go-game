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

	bool is_suicide(Board* board, Point p)
	{
		int counter = 0;
		Point possibilities[4] =
		{
			{p.x - 1, p.y}, {p.x + 1, p.y},
			{p.x, p.y + 1}, {p.x, p.y - 1}
		};

		char current_element = board->get_value_by_pos(p);

		if (current_element == Board::INTERIOR)
		{
			return false;
		}
		
		if (current_element == this->id)
		{
			board->set_value_by_pos(p, '4');

			for (int i = 0; i < 4; i++)
			{
				if (is_suicide(board, possibilities[i]) == false)
					return false;
			}
		}
		return true;
	}

	void repair(Board* b)
	{
		for (int y = 0; y < b->get_board_size(); y++)
		{
			for (int x = 0; x < b->get_board_size(); x++)
			{
				if (b->get_value_by_pos({ x,y }) == '4')
					b->set_value_by_pos({ x,y }, this->id);
			}
		}
	}

	bool set_stone(Board* board, Point p)
	{
		char value_of_position = board->get_value_by_pos(p);

		if (value_of_position == Board::INTERIOR)
		{
			board->set_value_by_pos(p, this->id);
			if (is_suicide(board, p))
			{
				board->set_value_by_pos(p, Board::INTERIOR);
				repair(board);
				return false;
			}
			repair(board);
			return true;
		}
		return false;
	}
};

