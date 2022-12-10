#pragma once
#include "Point.h"
#include <cstdio>
#include <stdio.h>
#include "conio2.h"

//types of fields which are on the board
enum field_type
{
	INTERIOR = '0',
	PLAYER_1 = '1',
	PLAYER_2 = '2',
	OUT_OF_RANGE = '#'
};

class Board
{
private:
	__int8 size;
	char** area;
public:
	int display_size;
	bool tour;
	Point page_start;
	Point page_end;

	Board(int size, bool tour = 0)
	{
		this->size = size;
		this->tour = tour;
		this->area = new char*[size];
		this->display_size = size > PAGE_LENGTH ? PAGE_LENGTH : size;
		this->page_start = { 0 ,0 };
		this->page_end = { display_size, display_size };
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

	void display_area(Point display_pos)
	{
		gotoxy(display_pos.x, display_pos.y);

		for (int y = page_start.y; y < page_end.y; y++)
		{
			for (int x = page_start.x; x < page_end.x; x++)
			{
				char temp = area[y][x];
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
						textcolor(DARKGRAY);
						putch(254);
						textcolor(WHITE);
						break;
					}
					case PLAYER_2:
					{
						textcolor(WHITE);
						putch(254);
						textcolor(WHITE);
						break;
					}
				}

				if (x != page_end.x - 1)
					putch(196);
				}
			gotoxy(display_pos.x, ++display_pos.y);
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