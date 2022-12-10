#include "Point.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point Point::operator - (int val)
{
	return { this->x - val, this->y - val };
}

Point Point::operator - (Point p)
{
	return { this->x - p.x, this->y - p.y };
}

Point Point::operator + (int val)
{
	return { this->x + val, this->y + val };
}

bool Point::operator == (Point p)
{
	return this->x == p.x && this->y == p.y;
}