#pragma once
#include "Board.h"
#include "Cursor.h"
#include "Legend.h"
#include "Player.h"
#include "Menu.h"
#include <corecrt_malloc.h>
#include <stdio.h>
class Game_Controller
{
private:
	Board* board;
	Cursor* cursor;
	Legend* legend;
	Player* player1;
	Player* player2;
	Point* checked;
	int how_many_checked;
	char board_location;
	int board_size;
	bool lock;
	bool handicap;

	//GAME LOGIC

	bool set_stone(Player*& player, Point p)
	{
		char value_of_position = board->get_value_by_pos(p);

		if (value_of_position == field_type::INTERIOR)
		{
			board->set_value_by_pos(p, player->get_id());
			if (is_suicide(player, p))
			{
				board->set_value_by_pos(p, field_type::INTERIOR);
				return false;
			}

			player->score += can_beat(player, p);
			return true;
		}
		return false;
	}

	bool is_suicide(Player*& player, Point p)
	{
		if (has_even_one_empty_neighbour(p, player->get_id()))
		{
			clear_checked_list();
			return false;
		}
		clear_checked_list();
		return true;
	}

	int can_beat(Player*& player, Point p)
	{
		int beated = 0;
		Point possibilities[4] =
		{
			{p.x - 1, p.y}, {p.x + 1, p.y},
			{p.x, p.y + 1}, {p.x, p.y - 1}
		};

		for (int i = 0; i < 4; i++)
		{
			char opponent_id = 99 - player->get_id();
			if (has_even_one_empty_neighbour(possibilities[i], opponent_id) == false)
			{
				remove_points();
				beated = this->how_many_checked;
				clear_checked_list();
			}
		}

		return beated;;
	}

	bool has_even_one_empty_neighbour(Point p, char search)
	{
		Point possibilities[4] =
		{
			{p.x - 1, p.y}, {p.x + 1, p.y},
			{p.x, p.y + 1}, {p.x, p.y - 1}
		};

		char current_element = board->get_value_by_pos(p);

		if (current_element == field_type::INTERIOR)
		{
			return true;
		}

		if (current_element == search)
		{
			checked[how_many_checked] = p;
			how_many_checked++;
			for (int i = 0; i < 4; i++)
			{
				if (is_already_checked(possibilities[i]) == false)
				{
					if (has_even_one_empty_neighbour(possibilities[i], search))
						return true;
				}
			}
		}
		return false;
	}

	bool is_already_checked(Point point)
	{
		for (int i = 0; i < how_many_checked; i++)
		{
			if (point == checked[i])
				return true;
		}
		return false;
	}

	void remove_points()
	{
		for (int i = 0; i < how_many_checked; i++)
			board->set_value_by_pos(checked[i], field_type::INTERIOR);
	}

	void clear_checked_list()
	{
		for (int i = 0; i < how_many_checked; i++)
			checked[i] = { -1, -1 };
		how_many_checked = 0;
	}

public:
	Game_Controller(int board_size, char board_location)
	{
		this->lock = false;
		this->handicap = false;
		this->board_size = board_size;
		this->board_location = board_location;

		this->board = new Board(board_size);
		this->cursor = new Cursor(); 
		this->legend = new Legend();
		this->player1 = new Player(field_type::PLAYER_1);
		this->player2 = new Player(field_type::PLAYER_2);
		this->checked = new Point[board_size*board_size];
		this->how_many_checked = 0;
		setup_points();
	}

	~Game_Controller()
	{
		delete board;
		delete cursor;
		delete legend;
		delete player1;
		delete player2;
		delete[] checked;
	}

	void setup_points()
	{
		switch (board_location)
		{
			case 'r':
			{
				this->legend->set_display_pos({2, 1});
				cursor->limit_1 = { legend->get_longest_line_length() + 10 + 1, 3 };
				break;
			}
			case 'l':
			{
				this->legend->set_display_pos({ board->get_board_size() + 10 + 2, 2 });
				cursor->limit_1 = { 2, 2 };
				break;
			}
		}
		cursor->absolute_pos = cursor->limit_1;
		cursor->limit_2 = { cursor->limit_1.x + board->get_board_size() * 2 - 2, cursor->limit_1.y + board->get_board_size() - 1 };
	}

	void display()
	{
		setup_points();
		legend->display();
		Helper::display_border(cursor->limit_1 - 1, { cursor->limit_2.x + 2, cursor->limit_2.y + 2 }, YELLOW);
	}

	void update()
	{
		board->display_area(cursor->limit_1);
		legend->update(*cursor, board->tour, player1->score, player2->score);
		cursor->display();
	}

	bool save(const char* file_name)
	{
		FILE* file;
		file = fopen(file_name, "wb");

		if (file == NULL)
		{
			return false;
		}

		__int8 size = this->board->get_board_size();
		bool tour = this->board->tour;

		fwrite(&size, sizeof(size), 1, file);
		fwrite(&tour, sizeof(tour), 1, file);

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				char area_val = this->board->get_value_by_pos({ x, y });
				fwrite(&area_val, sizeof(char), 1, file);
			}
		}
		fclose(file);
		return true;
	}

	bool load(const char* file_name)
	{
		FILE* file;
		file = fopen(file_name, "rb");

		if (file == NULL)
		{
			return false;
		}

		__int8 size;
		bool tour;

		fread(&size, sizeof(size), 1, file);
		fread(&tour, sizeof(tour), 1, file);

		delete this->board;
		this->board = new Board(size, tour);
		this->board_size = size;

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				char temp;
				fread(&temp, sizeof(char), 1, file);
				board->set_value_by_pos({ x, y }, temp);
			}
		}

		fclose(file);

		delete[] this->checked;
		this->checked = new Point[board_size * board_size];

		return true;
	}

	void new_game()
	{
		board_size = board->get_board_size();
		delete this->board;
		this->board = new Board(board_size);
		setup_points();
		display();
	}

	void handle_input(int input)
	{
		switch (input)
		{
			case 0:
			{
				if (lock == false)
				{
					input = getch();
					cursor->move(input);
				}
				break;
			}
			case buttons::i:
			{
				lock = true;
				break;
			}
			case buttons::ENTER:
			{
				if (lock)
				{
					bool success;
					if (handicap)
					{
						success = set_stone(player1, cursor->relative_pos);
						if (success)
							lock = false;
					}
					else
					{
						if (board->tour)
							success = set_stone(player2, cursor->relative_pos);
						else
							success = set_stone(player1, cursor->relative_pos);

						if (success)
						{
							board->tour = !board->tour;
							lock = false;
						}
					}
				}
				break;
			}
			case buttons::ESC:
			{
				lock = false;
				break;
			}
			case buttons::h:
			{
				handicap = !handicap;
				break;;
			}
		}
	}
};