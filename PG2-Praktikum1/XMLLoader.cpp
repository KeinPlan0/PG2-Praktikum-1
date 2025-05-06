#include "XMLLoader.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>



std::string trim(const std::string& s) {
	const std::string WHITESPACE = " \n\r\t\f\v";
	size_t start = s.find_first_not_of(WHITESPACE);
	std::string str = (start == std::string::npos) ? s : s.substr(start);
	size_t end = str.find_last_not_of(WHITESPACE);
	str = (end == std::string::npos) ? str : str.substr(0, end + 1);
	return str;
}

std::vector<std::string> split(const std::string& strToSplit, char delim) {
	std::stringstream sstream(strToSplit);
	std::vector<std::string> splittedStrings;
	std::string item;
	while (std::getline(sstream, item, delim))
		splittedStrings.push_back(trim(item));
	return splittedStrings;
}

XMLLoader::TagType XMLLoader::tagName(std::string &tagIn) {
	std::string trimTag = trim(tagIn);
	std::string tagName = trimTag;
	char dl = ' ';
	std::vector<std::string> v;
	std::vector<std::string> attributes;
	std::string values;

	const std::string NOCHAR = "?!/<>";
	size_t start = tagName.find_first_not_of(NOCHAR);
	std::string str = "";
	str	= (start == std::string::npos) ? tagName : tagName.substr(start);
	size_t end = str.find_last_not_of(NOCHAR);
	str = (end == std::string::npos) ? str : str.substr(0, end + 1);
	v = split(str, ' ');

	tagIn = v.at(0);

	for (int i = 1; i < v.size(); i++) {
		if (v[i].find_first_of('=') != std::string::npos) {
			attributes = split(v[i], '='); // [position]["0]
		
			std::cout << values << std::endl;
			std::cout << attributes[0] << std::endl;
				values = (attributes[1]) + " ";
			
		}
		else {
			values += v[i] + " ";
		}
	}

	std::cout << values << std::endl;

	std::cout << "Trim Tag" << trimTag << std::endl;
	if ((trimTag.at(0) == '<' && trimTag.back() == '>'))
	{
		if (trimTag.at(1) == '!' || trimTag.at(1) == '?')
		{
			return NONE;
		}
		if (trimTag.at(1) == '/')return END_TAG;
		else if (trimTag.at(trimTag.length() - 2) == '/') return SELF_CLOSING;
		return START_TAG;
	} return NONE;
}



void XMLLoader :: load(const char* filename) {
	std::ifstream ifs;
	ifs.open(filename);
	if (!ifs.good()) {
		std::cout << "Datei konnte nicht geöffnet werden" << std::endl;
		exit(0);
	}
	//--------------------------
	std::string line;
	while (std::getline(ifs, line)) {
		TagType type = tagName(line);
		std::cout << "Line: " << line << std::endl;
		if (type == START_TAG) {
			stack.push(line);
			std::cout << "Pushing: " << (line) << std::endl;
		}
		else if (type == END_TAG) {
			if (stack.empty()) {
				std::cout << "Not correctly formattet XML.Because cloed without opening." << std::endl;
				exit(0);
			}
			else {
				std::string poppedTag = stack.pop();
				if (poppedTag == (line)) {
					std::cout << "Popped: " << poppedTag << std::endl;
				}
				else {
					std::cout << "Not correctly formattet XML. Wrong Order" << std::endl;
					exit(0);
				}
			}
		}
		else if (type == SELF_CLOSING) {
			std::cout << "Self Closing Tag: " << (line) << std::endl;
		}
		else if (type == NONE) {
			std::cout << "None Tag: " << line << std::endl;
		}
		std::cout << std::endl;
	}
	if (stack.empty()) {
		std::cout << "XML is correctly formattet." << std::endl;
	}
	else {
		std::cout << "Not correctly formattet XML. Stack not empty." << std::endl;
		std::cout << "Remaining stack: " << std::endl;
		for (int i = 0; i < stack.stack.size(); i++) {
			std::cout << stack.stack[i] << std::endl;
		}
	}
}



/*
XMLLoader::TagType XMLLoader::tagType(std::string tagIn) {
	std::string trimTag = trim(tagIn);
	std::cout << extractTagName(trimTag) << std::endl;
	if ((trimTag.at(0) == '<' && trimTag.back() == '>'))
	{
		if (trimTag.at(1) == '!' || trimTag.at(1) == '?')
		{
			return NONE;
		}
		if (trimTag.at(1) == '/')return END_TAG;
		else if (trimTag.at(trimTag.length() - 2) == '/') return SELF_CLOSING;
		return START_TAG;
	} return NONE;
}
*/

