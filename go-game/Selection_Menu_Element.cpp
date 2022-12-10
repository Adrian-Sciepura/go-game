#include "Selection_Menu_Element.h"

Selection_Menu_Element::Selection_Menu_Element(element_type type, const char* content, const char* return_value)
{
	this->content = _strdup(content);
	this->length = strlen(content);
	this->return_value = _strdup(return_value);
	this->type = type;
}

Selection_Menu_Element::~Selection_Menu_Element()
{
	delete[] content;
	delete[] return_value;
}