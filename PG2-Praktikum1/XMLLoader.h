#pragma once
#include <string>
#include "Stack.h"
class XMLLoader
{
private:



public:
	Stack stack;
	void load(const char* filename);
	enum TagType { NONE, START_TAG, END_TAG, SELF_CLOSING };
	TagType tagName(std::string& tagIn);

};

