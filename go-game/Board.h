#pragma once
#include "Point.h"
#include <cstdio>
#include "conio2.h"
class Board
{
private:
	__int8 size;
	char interior;
	char border;
	char** area;

public:
	bool tour;

	enum values
	{
		INTERIOR = '0',
		PLAYER_1 = '1',
		PLAYER_2 = '2'
	};

	Board(int size, bool tour = 0, char interior = '+', char border = '#')
	{
		this->size = size;
		this->tour = tour;
		this->interior = interior;
		this->border = border;
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

	bool load(const char* file_name)
	{
		FILE* file;
		file = fopen(file_name, "rb");

		if (file == NULL)
		{
			return false;
		}

		fread(&this->size, sizeof(size), 1, file);
		fread(&this->tour, sizeof(tour), 1, file);
		fread(&this->interior, sizeof(interior), 1, file);
		fread(&this->border, sizeof(border), 1, file);

		delete[] this->area;

		this->area = new char* [size];

		for (int x = 0; x < size; x++)
		{
			area[x] = new char[size];
			for (int y = 0; y < size; y++)
			{
				fread(&this->area[x][y], sizeof(char), 1, file);
			}
		}

		fclose(file);
		return true;
	}

	bool save(const char* file_name)
	{
		FILE* file;
		file = fopen(file_name, "wb");

		if (file == NULL)
		{
			return false;
		}

		fwrite(&this->size, sizeof(size), 1, file);
		fwrite(&this->tour, sizeof(tour), 1, file);
		fwrite(&this->interior, sizeof(interior), 1, file);
		fwrite(&this->border, sizeof(border), 1, file);

		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				fwrite(&this->area[x][y], sizeof(char), 1, file);
			}
		}
		fclose(file);
		return true;
	}

	~Board()
	{
		delete [] area;
	}

	void display_border(Point p) const
	{
		gotoxy(p.x, p.y);
		for (int i = 0; i < size + 2; i++)
		{
			for (int j = 0; j < size + 2; j++)
			{
				putch(border);
			}
			gotoxy(p.x, ++p.y);
		}
	}

	void display_area(Point p) const
	{
		gotoxy(p.x, p.y);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				char temp = area[i][j];

				switch (temp)
				{
					case INTERIOR:
					{
						putch(interior);
						break;
					}
					case PLAYER_1:
					{
						textcolor(LIGHTGREEN);
						putch('o');
						textcolor(LIGHTGRAY);
						break;
					}
					case PLAYER_2:
					{
						textcolor(LIGHTMAGENTA);
						putch('o');
						textcolor(LIGHTGRAY);
						break;
					}
				}
			}
			gotoxy(p.x, ++p.y);
		}
	}

	int get_board_size() const
	{
		return this->get_board_size();
	}

	char get_value_by_pos(Point p)
	{
		return this->area[p.y][p.x];
	}

	void set_value_by_pos(Point p, char val)
	{
		this->area[p.y][p.x] = val;
	}
};
