#pragma once
#include "coreVariables.h"

class c_Output
{

private:
	int wordcount(std::string text);
	int typeColourFlagSwitch(std::string flag, int colourFlag);
	int locationColourFlagSwitch(std::string flag, int colourFlag);
	std::string colouriser(int g, int columnlist, int articlelist, int flagType, int colourFlag);
	std::string wordCountiser(int g, int columnlist, int articlelist);
	std::string labeliser(int g, int columnlist, int articlelist);
	int findmaxarticleno(int g);

	struct article {
		int position; // index column
		std::string type; // type of entry
		std::string topic; // topic of entry
		std::string mentioned_location; // geographic location mentioned in article
		std::string source; // source location
		std::string source_type; // source type indicator
		std::string source_location; // source indicator 
		std::string text; // text of article
		int wc; // auto-generated wordcount of article
	};
	struct column {
		int position;  // index column
		std::vector <article> articles;
	};
	struct page {
		int position; // index column
		std::vector <column> columns;
	};
	struct copy {
		std::string title; // title of newspaper
		int day; // day of issue
		int month; // month of issue
		int year; // year of issue
		std::vector <page> pages;
	};

	std::vector <page> pages;
	std::vector <column> columns;
	std::vector<article>articles;

	copy currentCopy;
	page emptyPage;
	column emptyColumn;
	article emptyArticle;

public:
	void transformVector();
	void graphicMaker(int flagInt, int colourFlag);	
	
};
