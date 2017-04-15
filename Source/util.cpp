#include "stdafx.h"

int wordcount(std::string text) {
	int spaces = 0; // start with assumption of 0 spaces in the article
	for (int j = 0; j < size(text); ++j) // for each character in the text
	{
		if (text[j] == char(32)) // check to see if it is a space
		{
			++spaces; // if it is, advance space counter
		}
	}
	++spaces; // add one more to space counter (to account for first word)
	return spaces; // send wordcount onward
};

int colourFlagSwitch(std::string flag)
{
	int flagInt = 0;
	if (flag == "l")
	{
		flagInt = 1;
	}
	else if (flag == "a")
	{
		flagInt = 3;
	}
	else if (flag == "t")
	{
		flagInt = 5;
	}
	else if (flag == "c")
	{
		flagInt = 7;
	}
	else if (flag == "u")
	{
		flagInt = 9;
	}
	else
	{
		flagInt = 0;
	}
	return flagInt;

}