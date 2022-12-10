#ifndef INPUT_MENU_H
#define INPUT_MENU_H

#include "Menu.h"

class Input_Menu : Menu
{
private:
	char* buffer;
	int index;
public:
	Input_Menu(Cursor& cursor, const char* header, int border_color);
	~Input_Menu();
	void display();
	char* handle_input(int input);
};
#endif