#pragma once
#include "coreVariables.h"
#include "c_LegendCreation.h"
#include "c_Transformation.h"

extern c_Transformation transformationInstance;
extern c_LegendCreation legendInstance;

class c_Output
{

private:
	std::string colouriser(int g, int columnlist, int articlelist, std::string colourFlag);
	std::string patterniser(int g, int columnlist, int articlelist, std::string colourFlag);
	std::string wordCountiser(int g, int columnlist, int articlelist);
	std::string labeliser(int g, int columnlist, int articlelist);
	int findmaxarticleno(int g);

	// Typographic Variables
	std::string lineBreak = "\n";
	std::string tab = "\t";

public:
	// Configuration flags
	std::string pythonFlag = "python";
	
	// Functions
	void graphicMaker(std::string colourFlag);	
	
};



