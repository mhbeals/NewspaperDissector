#pragma once
#include "coreVariables.h"
#include "c_Input.h"
extern c_Input inputInstance;

class c_Transformation
{

private:
	float wordcount(std::string text);

	struct article {
		int position; // index column
		std::string type; // lgend label
		std::string key_value; // legend indicator
		std::string text; // text of article
		float wc; // wordcount or other quantifier of article
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
		std::string documentID; // title of newspaper
		std::vector <page> pages;
	};

	std::vector <page> pages;
	std::vector <column> columns;
	std::vector<article> articles;

	page emptyPage;
	column emptyColumn;
	article emptyArticle;

public:
	void transformVector();
	copy currentCopy;

};



