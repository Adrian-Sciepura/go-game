#include "Board.h"

Board::Board(int size, bool tour)
{
	this->size = size;
	this->tour = tour;
	this->area = new char* [size];
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

Board::~Board()
{
	for (int y = 0; y < size; y++)
	{
		delete area[y];
	}
	delete[] area;
}

void Board::display_area(Point display_pos)
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

int Board::get_board_size() const
{
	return this->size;
}

char Board::get_value_by_pos(Point p) const
{
	if (p.x >= size || p.y >= size)
		return OUT_OF_RANGE;
	if (p.x < 0 || p.y < 0)
		return OUT_OF_RANGE;

	return this->area[p.y][p.x];
}

void Board::set_value_by_pos(Point p, char val)
{
	this->area[p.y][p.x] = val;
}