#pragma once
#include "coreVariables.h"

class c_Input
{

private:
	// Edition Entry Variables
	struct editionEntry
	{
		int year;
		int month;
		int day;
		std::string title;
		int page;
		int column;
		int snippet;
		std::string type;
		std::string key_value;
		std::string text;
		int wordcount;
	};
	std::vector <std::string> buffer;
	editionEntry emptyEntry;

public:

	// Functions
	void loadFile(std::string inputDirectory, std::string inputFile);

	// Containers
	std::vector <editionEntry> edition;
};


