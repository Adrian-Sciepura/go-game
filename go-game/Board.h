#include"conio2.h"

#ifndef Board_H
#define Board_H
class Board
{
private:
	int size;
	char border;
	char interior;
	char** area;
	
public: 

	Board(int size, char border = '#', char interior = '+')
	{
		this->size = size;
		this->border = border;
		this->interior = interior;
		this->area = new char*[size + 2];

		for (int i = 0; i < size + 2; i++)
		{
			area[i] = new char[size + 2];
			for (int j = 0; j < size + 2; j++)
			{
				if (j == 0 || j == size + 1)
				{
					area[i][j] = border;
				}
				else if (i == 0 || i == size + 1)
				{
					area[i][j] = border;
				}
				else
				{
					area[i][j] = interior;
				}
			}
		}
	}

	~Board()
	{
		delete [] area;
	}

	void display(int start_x, int start_y) const
	{
		gotoxy(start_x, start_y);
		for (int i = 0; i < size + 2; i++)
		{
			for (int j = 0; j < size + 2; j++)
			{
				putch(area[i][j]);
			}
			gotoxy(start_x, ++start_y);
		}
	}

	int get_board_size() const
	{
		return this->size;
	}

	char get_element_by_pos(int x, int y) const
	{
		return area[x+1][y+1];
	}

	void set_element_by_pos(int x, int y, char c)
	{
		area[y + 1][x + 1] = c;
	}
};

#endif