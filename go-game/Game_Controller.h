#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

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

	bool set_stone(Player*& player, Point p);
	bool is_suicide(Player*& player, Point p);
	int can_beat(Player*& player, Point p);
	bool has_even_one_breathe(Point p, char search);
	bool is_already_checked(Point point);
	void remove_points();
	void clear_checked_list();

public:
	Game_Controller(int board_size, char board_location);
	~Game_Controller();
	void setup_points();
	void display();
	void update();
	bool save(const char* file_name);
	bool load(const char* file_name);
	void new_game();
	void handle_input(int input);
};
#endif