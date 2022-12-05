#ifndef Point_H
#define Point_H
#include "conio2.h"
struct Point
{
	int x;
	int y;

	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}

	Point operator - (int val)
	{
		return { this->x - val, this->y - val };
	}

	Point operator - (Point p)
	{
		return { this->x - p.x, this->y - p.y };
	}

	Point operator + (int val)
	{
		return { this->x + val, this->y + val };
	}
};
#endif