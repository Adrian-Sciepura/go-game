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

	void display(int start_x, int start_y)
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
};

#endif

