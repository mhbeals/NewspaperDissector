#pragma once
#include "coreVariables.h"

class c_LegendCreation
{

private:
	// Response Variables
	std::string responseString = "n";
	
	// Input Container
	std::vector <std::string> buffer;
	
	// Typographic Variables
	std::string lineBreak = "\n";
	std::string tab = "\t";
	
	// Legend Entry variables
	struct entry
	{
		std::string keyWord;
		std::string keyCharacter;
	};
	entry blankEntry;
	int legendItemCount = 1000;

	// Functions
	void c_LegendCreation::colourSchemeLoader(int legendItemCount);

public:
	// Legend Entry variables
	std::string legendLoaded = "S";
	std::vector <entry> legendEntries;
	int selectedColourScheme[10];

	// Colour Scheme
	std::string legendColourScheme = "Q";
	int fullColour[9] = { 0,2,4,6,8,10,1,3,5 };
	int colourblind[5] = { 0,1,5,6,8 };
	std::string patternScheme[10] = {" ", "\\\\", "||", "//", "+", "-", "=", "*", "o", "O"};

	// Functions
	std::string legendQuery(std::string inputDirectory);
	void legendLoader(std::string inputDirectory, std::string legendFile);
	void legendCreator(std::vector<entry> legendEntries, std::string inputDirectory);
	std::string c_LegendCreation::colourSchemeChooser();
};
