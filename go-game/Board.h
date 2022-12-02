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
					area[i][j] = '0';
				}
				else if (i == 0 || i == size + 1)
				{
					area[i][j] = '0';
				}
				else
				{
					area[i][j] = '1';
				}
			}
		}
	}


	Board(const char* file, int size, char border = '#', char interior = '+')
	{
		this->size = size;
		this->border = border;
		this->interior = interior;
		this->area = new char* [size + 2];

		char* temp = FileService::read_file(file);
		int i = 0;
		int line = 0;

		while (temp[i] != '\0')
		{
			if (area[line] == NULL)
			{
				area[line] = new char[size + 2];
			}
			if (i % (size+2) == 0)
			{
				line++;
				continue;
			}
			area[line][i % (size+2)] = temp[i];
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
				char temp = area[i][j];

				switch (temp)
				{
					case '0':
					{
						putch(border);
						break;
					}
					case '1':
					{
						putch(interior);
						break;
					}
					case '2':
					{
						textcolor(LIGHTGREEN);
						putch('o');
						textcolor(LIGHTGRAY);
						break;
					}
					case '3':
					{
						textcolor(LIGHTMAGENTA);
						putch('o');
						textcolor(LIGHTGRAY);
						break;
					}
				}
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

	char* get_area_line(int line) const
	{
		return area[line];
	}
};

#endif