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

	enum values
	{
		BORDER = '0',
		INTERIOR = '1',
		PLAYER_1 = '2',
		PLAYER_2 = '3'
	};

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

		char* load_data = FileService::read_file("gameState.txt");
		int lenght = 0;

		while (load_data[lenght] != '\n')
		{
			lenght++;
		}

		if (lenght == (size + 2))
		{
			int k = 0;
			for (int i = 0; i < lenght; i++)
			{
				area[i] = new char[size + 2];
				for (int j = 0; j <= lenght; j++)
				{
					area[i][j] = load_data[k];
					k++;
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
				char temp = area[i][j];

				switch (temp)
				{
					case BORDER:
					{
						putch(border);
						break;
					}
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

	void save()
	{
		int board_size = size;
		FileService::save_file("gameState.txt", NULL, 0);

		for (int i = 0; i < board_size + 2; i++)
		{
			FileService::append_file("gameState.txt", this->get_area_line(i), board_size + 2);
			FileService::append_file("gameState.txt", "\n", 1);
		}
		FileService::append_file("gameState.txt", "\0", 1);
	}
};
#endif