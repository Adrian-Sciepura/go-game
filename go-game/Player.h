#pragma once
#include "Point.h"
#include "Board.h"
struct Player
{
	char id;
	double score;

	Player(char id)
	{
		this->id = id;
		this->score = 0;
	}
};