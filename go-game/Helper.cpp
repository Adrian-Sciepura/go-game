#include "Helper.h"

void Helper::display_border(Point start_pos, Point end_pos, int border_color)
{
	Point corners[4] =
	{
		start_pos, {end_pos.x - 1, start_pos.y},
		{start_pos.x, end_pos.y - 1}, end_pos - 1
	};

	unsigned char symbols[4] =
	{
		218, 191, 192, 217
	};

	gotoxy(start_pos.x, start_pos.y);
	Point temp{ (end_pos.x - start_pos.x), (end_pos.y - start_pos.y) };
	for (int x = 1; x <= temp.y; x++)
	{
		for (int y = 1; y <= temp.x; y++)
		{
			if (x == 1 || x == temp.y)
			{
				textcolor(border_color);
				putch(196);
			}
			else if (y == 1 || y == temp.x)
			{
				textcolor(border_color);
				putch(179);
			}
			else
				putch(' ');
			textcolor(WHITE);
		}
		gotoxy(start_pos.x, ++start_pos.y);
	}

	for (int i = 0; i < 4; i++)
	{
		textcolor(border_color);
		gotoxy(corners[i].x, corners[i].y);
		putch(symbols[i]);
	}
}

int Helper::convert_string_to_int(const char* str)
{
	char* end;
	return strtol(str, &end, 10);
}

char* Helper::read_text_file(const char* file_name)
{
	FILE* file;
	long file_length;
	char* buffer;
	size_t result;

	file = fopen(file_name, "r");
	if (file == NULL)
	{
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	file_length = ftell(file);
	rewind(file);

	buffer = new char[file_length + 1];

	if (buffer == NULL)
	{
		return NULL;
	}

	result = fread(buffer, 1, file_length, file);
	buffer[result] = '\0';
	fclose(file);
	return buffer;
}