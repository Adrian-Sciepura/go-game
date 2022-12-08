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

	bool has_even_one_empty_neighbour(Board& board, Point p, char search)
	{
		Point possibilities[4] =
		{
			{p.x - 1, p.y}, {p.x + 1, p.y},
			{p.x, p.y + 1}, {p.x, p.y - 1}
		};

		char current_element = board.get_value_by_pos(p);

		if (current_element == field_type::INTERIOR)
		{
			return true;
		}
		
		if (current_element == search)
		{
			board.set_value_by_pos(p, '4');

			for (int i = 0; i < 4; i++)
			{
				if (has_even_one_empty_neighbour(board, possibilities[i], search) == true)
					return true;
			}
		}
		return false;
	}

	bool is_suicide(Board& board, Point p)
	{
		if (has_even_one_empty_neighbour(board, p, this->id))
		{
			repair(board, this->id);
			return false;
		}	
		repair(board, this->id);
		return true;
	}

	int can_beat(Board& board, Point p)
	{
		int beated = 0;
		Point possibilities[4] =
		{
			{p.x - 1, p.y}, {p.x + 1, p.y},
			{p.x, p.y + 1}, {p.x, p.y - 1}
		};

		for (int i = 0; i < 4; i++)
		{
			char opponent_id = 99 - this->id;
			if (has_even_one_empty_neighbour(board, possibilities[i], opponent_id) == false)
				beated += repair(board, field_type::INTERIOR);
			else
				repair(board, opponent_id);
		}

		return beated;
	}

	int repair(Board& b, char player)
	{
		int counter = 0;
		for (int y = 0; y < b.get_board_size(); y++)
		{
			for (int x = 0; x < b.get_board_size(); x++)
			{
				if (b.get_value_by_pos({ x,y }) == '4')
				{
					counter++;
					b.set_value_by_pos({ x,y }, player);
				}
			}
		}
		return counter;
	}

	bool set_stone(Board& board, Point p)
	{
		char value_of_position = board.get_value_by_pos(p);

		if (value_of_position == field_type::INTERIOR)
		{
			board.set_value_by_pos(p, this->id);
			if (is_suicide(board, p))
			{
				board.set_value_by_pos(p, field_type::INTERIOR);
				return false;
			}

			int beat = can_beat(board, p);
			this->score += beat;

			return true;
		}
		return false;
	}
};

