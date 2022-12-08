#pragma once
#include "Point.h"
#include <cstdio>
#include "conio2.h"
class Board
{
private:
	__int8 size;
	char** area;
public:
	bool tour;
	enum values
	{
		INTERIOR = '0',
		PLAYER_1 = '1',
		PLAYER_2 = '2',
		OUT_OF_RANGE = '#'
	};

	Board(int size, bool tour = 0)
	{
		this->size = size;
		this->tour = tour;
		this->area = new char*[size];

		for (int x = 0; x < size; x++)
		{
			area[x] = new char[size];
			for (int y = 0; y < size; y++)
			{
				area[x][y] = INTERIOR;
			}
		}
	}

	~Board()
	{
		for (int y = 0; y < size; y++)
		{
			delete area[y];
		}
		delete [] area;
	}

	void display_area(Point p) const
	{
		gotoxy(p.x, p.y);
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				char temp = area[x][y];

				switch (temp)
				{
					case INTERIOR:
					{
						textcolor(WHITE);
						putch(197);
						break;
					}
					case PLAYER_1:
					{
						textcolor(WHITE);
						putch(254);
						textcolor(WHITE);
						break;
					}
					case PLAYER_2:
					{
						textcolor(DARKGRAY);
						putch(254);
						textcolor(WHITE);
						break;
					}
				}

				if (y != size - 1)
					putch(196);
			}
			
			gotoxy(p.x, ++p.y);
		}
	}

	int get_board_size() const
	{
		return this->size;
	}

	char get_value_by_pos(Point p)
	{
		if (p.x >= size || p.y >= size)
			return OUT_OF_RANGE;
		if (p.x < 0 || p.y < 0)
			return OUT_OF_RANGE;

		return this->area[p.y][p.x];
	}

	void set_value_by_pos(Point p, char val)
	{
		this->area[p.y][p.x] = val;
	}
};
