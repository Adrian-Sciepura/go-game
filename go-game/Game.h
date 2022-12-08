#pragma once
#include "Board.h"
#include "Cursor.h"
#include "Legend.h"
#include "Player.h"
#include "Menu.h"
#include <corecrt_malloc.h>
class Game
{
private:
	Board* board;
	Cursor* cursor;
	Legend* legend;
	Player* player1;
	Player* player2;
	char board_location;
	int board_size;
	bool lock;

public:
	Game(int board_size, char board_location)
	{
		this->lock = false;
		this->board_size = board_size;
		this->board_location = board_location;

		this->board = new Board(board_size);
		this->cursor = new Cursor(); 
		this->legend = new Legend();
		this->player1 = new Player(Board::PLAYER_1);
		this->player2 = new Player(Board::PLAYER_2);
		setup_points();
	}

	~Game()
	{
		delete board;
		delete cursor;
		delete legend;
		delete player1;
		delete player2;
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
		legend->display();
		Helper::display_border(cursor->limit_1 - 1, { cursor->limit_2.x + 2, cursor->limit_2.y + 2 }, YELLOW);
	}

	void update()
	{
		board->display_area(cursor->limit_1);
		legend->update(*cursor, board->tour);
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

		_int8 size = this->board->get_board_size();
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

		_int8 size;
		bool tour;

		fread(&size, sizeof(size), 1, file);
		fread(&tour, sizeof(tour), 1, file);

		delete this->board;
		this->board = new Board(size, tour);

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
					if (board->tour)
						success = player2->set_stone(board, cursor->relative_pos);
					else
						success = player1->set_stone(board, cursor->relative_pos);

					if (success)
					{
						board->tour = !board->tour;
						lock = false;
					}
				}
				break;
			}
			case buttons::ESC:
			{
				lock = false;
				break;
			}
		}
	}



};