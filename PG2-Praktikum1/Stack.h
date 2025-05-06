#pragma once
#include <string>
#include <vector>
class Stack
{
public:
	std::vector <std::string> stack;
	std::string pop();
	void push(std::string str);
	bool empty();
};

