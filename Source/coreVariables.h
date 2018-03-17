#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// Shared variables for data
struct entry
{
	int year;
	int month;
	int day;
	std::string title;
	int page;
	int column;
	int snippet;
	std::string type;
	std::string topic;
	std::string mentioned_location;
	std::string source_type;
	std::string source;
	std::string source_location;
	std::string text;
	int wordcount;
};
extern std::vector <entry> edition;
void loadFile(std::string inputDirectory, std::string inputFile);