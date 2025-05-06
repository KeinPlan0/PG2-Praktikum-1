#include "Stack.h"
#include <vector>
#include <iostream>
bool Stack::empty() {
	if (stack.empty()) {
		return true;
	}
	else
	{
		return false;
	}
}

std::string Stack::pop() {
	if (stack.empty()) {
		 std::cout << "Stack is empty, cannot pop." << std::endl;
	}
	std::string end = stack.back(); 
	stack.pop_back();               
	return end;
}

void  Stack::push(std::string str) {
	stack.push_back(str);
}