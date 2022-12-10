#ifndef SELECTION_MENU_H
#define SELECTION_MENU_H

#include "Menu.h"
#include "Input_Menu.h"
#include "Selection_Menu_Element.h"

class Selection_Menu : Menu
{
private:
	Selection_Menu_Element* elements;
	int number_of_elements;
	int spacing;
	int position;
	int elements_length;

public:
	Selection_Menu(Selection_Menu_Element* elements, int number_of_elements, int spacing, Cursor& cursor, const char* header, int border_color);
	~Selection_Menu();
	void update_cursor();
	void display();
	char* handle_input(int input);
};
#endif