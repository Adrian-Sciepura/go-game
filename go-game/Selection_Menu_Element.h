#ifndef SELECTION_MENU_ELEMENT_H
#define SELECTION_MENU_ELEMENT_H

#include <string.h>

//type of item available in the menu
enum element_type { SELECTION, INPUT };

struct Selection_Menu_Element
{
	char* content;
	int length;
	char* return_value;
	element_type type;

	Selection_Menu_Element(element_type type, const char* content, const char* return_value = NULL);
	~Selection_Menu_Element();
};
#endif