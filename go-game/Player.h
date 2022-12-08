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

	char get_id()
	{
		return this->id;
	}
};


