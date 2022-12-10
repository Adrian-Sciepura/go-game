#pragma once
#include "Board.h"
#include "Cursor.h"
#include "Legend.h"
#include "Player.h"
#include "Menu.h"
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
			board->set_value_by_pos(p, player->id);
			player->score += can_beat(player, p);

			if (is_suicide(player, p))
			{
				board->set_value_by_pos(p, field_type::INTERIOR);
				return false;
			}
			
			return true;
		}
		return false;
	}

	bool is_suicide(Player*& player, Point p)
	{
		if (has_even_one_breathe(p, player->id))
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
			clear_checked_list();
			char opponent_id = 99 - player->id;
			if (has_even_one_breathe(possibilities[i], opponent_id) == false)
			{
				remove_points();
				beated = this->how_many_checked;
			}
		}
		clear_checked_list();
		return beated;;
	}

	bool has_even_one_breathe(Point p, char search)
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
					if (has_even_one_breathe(possibilities[i], search))
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
		cursor->board_size = board_size;
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
				this->legend->set_display_pos({1, 1});
				cursor->limit_1 = { legend->get_longest_line_length() + 5 + DISTANCE, 3 };
				break;
			}
			case 'l':
			{
				this->legend->set_display_pos({ board->display_size*2 + 2 + DISTANCE, 1 });
				cursor->limit_1 = { 3, 3 };
				break;
			}
		}

		cursor->absolute_pos = cursor->limit_1;
		cursor->relative_pos = { 0, 0 };
		cursor->limit_2 = { cursor->limit_1.x + ((board->page_end.x - 1) % board->display_size) * 2, cursor->limit_1.y + ((board->page_end.y - 1) % board->display_size) };
	}

	void display()
	{
		int display_size = board->get_board_size() > PAGE_LENGTH ? PAGE_LENGTH : board->get_board_size();
		legend->display();
		Helper::display_border(cursor->limit_1 - 1, { cursor->limit_1.x + display_size * 2, cursor->limit_1.y + display_size + 1 }, YELLOW);
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
		fwrite(&this->player1->score, sizeof(double), 1, file);
		fwrite(&this->player2->score, sizeof(double), 1, file);

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
		fread(&this->player1->score, sizeof(double), 1, file);
		fread(&this->player2->score, sizeof(double), 1, file);

		delete this->board;
		this->board = new Board(size, tour);
		this->board_size = size;
		cursor->board_size = size;

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
		this->player1->score = 0;
		this->player2->score = 0;
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
					cursor->move(board, input);
				}

				if (cursor->refresh)
				{
					clrscr();
					display();
					cursor->refresh = false;
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