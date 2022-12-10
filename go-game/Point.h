#ifndef Point_H
#define Point_H

#include "conio2.h"

struct Point
{
	int x;
	int y;

	Point(int x = 0, int y = 0);
	Point operator - (int val);
	Point operator - (Point p);
	Point operator + (int val);
	bool operator == (Point p);
};
#endif