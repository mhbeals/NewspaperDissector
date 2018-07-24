#include "c_Transformation.h"


//    _____        _          _______                   __                           _   _             
//   |  __ \      | |        |__   __|                 / _|                         | | (_)            
//   | |  | | __ _| |_ __ _     | |_ __ __ _ _ __  ___| |_ ___  _ __ _ __ ___   __ _| |_ _  ___  _ __  
//   | |  | |/ _` | __/ _` |    | | '__/ _` | '_ \/ __|  _/ _ \| '__| '_ ` _ \ / _` | __| |/ _ \| '_ \ 
//   | |__| | (_| | || (_| |    | | | | (_| | | | \__ \ || (_) | |  | | | | | | (_| | |_| | (_) | | | |
//   |_____/ \__,_|\__\__,_|    |_|_|  \__,_|_| |_|___/_| \___/|_|  |_| |_| |_|\__,_|\__|_|\___/|_| |_|
//                                                                                                     
//                                                                                                     

int c_Transformation::wordcount(std::string text) {
	int spaces = 0; // start with assumption of 0 spaces in the article
	for (size_t j = 0; j < size(text); ++j) // for each character in the text
	{
		if (text[j] == char(32)) // check to see if it is a space
		{
			++spaces; // if it is, advance space counter
		}
	}
	++spaces; // add one more to space counter (to account for first word)
	return spaces; // send wordcount onward
};

void c_Transformation::transformVector()
{
	// Create basic structure
	currentCopy.day = inputInstance.edition[0].day;
	currentCopy.month = inputInstance.edition[0].month;
	currentCopy.year = inputInstance.edition[0].year;
	currentCopy.title = inputInstance.edition[0].title;
	for (int i = 0; i < inputInstance.edition[inputInstance.edition.size() - 1].page; i++)
	{
		currentCopy.pages.push_back(emptyPage);
		currentCopy.pages[i].position = i + 1;

		for (int j = 0; j < inputInstance.edition[inputInstance.edition.size() - 1].column; j++)
		{
			currentCopy.pages[i].columns.push_back(emptyColumn);
			currentCopy.pages[i].columns[j].position = j + 1;
		}
	}

	// Fill in details
	for (size_t i = 0; i < inputInstance.edition.size(); i++)
	{
		size_t currentPage = inputInstance.edition[i].page - 1;
		size_t currentColumn = inputInstance.edition[i].column - 1;
		size_t currentSnippet = inputInstance.edition[i].snippet;
		if (currentSnippet > currentCopy.pages[currentPage].columns[currentColumn].articles.size())
		{
			currentCopy.pages[currentPage].columns[currentColumn].articles.push_back(emptyArticle);
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].position = currentSnippet;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].type = inputInstance.edition[i].type;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].key_value = inputInstance.edition[i].key_value;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].text = inputInstance.edition[i].text;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].wc = wordcount(inputInstance.edition[i].text);
		}
	}
}

