#include "stdafx.h"

struct article {
	int position; // index column
	std::string type; // type of entry
	std::string topic; // topic of entry
	std::string geo; // geographic location mentioned in article
	std::string flag; // source indicator
	std::string source; // source text 
	std::string text; // text of article
	int wc; // auto-generated wordcount of article
};
extern std::vector<article>articles;
struct column {
	int position;  // index column
	std::vector <article> articles;
};
extern std::vector <column> columns;
struct page {
	int position; // index column
	std::vector <column> columns;
};
extern std::vector <page> pages;
struct issue {
	int position; // index column
	std::string title; // title of newspaper
	int day; // day of issue
	int month; // month of issue
	int year; // year of issue
	std::vector <page> pages;
};
extern std::vector <issue> issues;

int findmaxarticleno(int f, int g)
{
	int maxno = 0; // start with assumption of 0 articles as test condition
	for (int j = 0; j < issues[f].pages[g].columns.size(); j++) // for every column
	{
		if (maxno < issues[f].pages[g].columns[j].articles.size())
			// check to see if its number of articles is the most you've seen so far
		{
			maxno = int(issues[f].pages[g].columns[j].articles.size());
			// if it is, change the test condition
		}
	}
	return maxno; // send maximum number of articles / column for this page onward
}

void colourListMaker(int maxarticleno, int f, int g) {
	std::string pagedata = "\nvalues_colour = ["; // start list of lists
	int currcol = 0; // first column
	int columnlist = int(issues[f].pages[g].columns.size() - 1); // last column
	int articlelist = maxarticleno - 1; // last article	
	int currart = articlelist; // first article to process (last one entered)
	int flagInt = 0;

	while (currart >= 0)
	{
		pagedata = pagedata + "["; // create list of article word counts

		while (currcol <= columnlist) // for each column on the page
		{
			if (currart > issues[f].pages[g].columns[currcol].articles.size() - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "0"; // use 0
			}
			else {
				// if it does have a word count
				flagInt = colourFlagSwitch(issues[f].pages[g].columns[currcol].articles[currart].flag);
				pagedata = pagedata + std::to_string(flagInt);
				// add the word count to the list
			}

			if (currcol == columnlist) // if it is the last column on the page
			{
				pagedata = pagedata + "]"; // end the article list
			}
			else // if its not
			{
				pagedata = pagedata + ","; // add comma
			}

			++currcol; // advance to next column
		}
		currcol = 0; // reset column counter

		if (currart == 0)
			// if it is the last article (of the most populated column)
		{
			pagedata = pagedata + "]"; // end the list of lists
		}
		else // if it isn't the last article
		{
			pagedata = pagedata + ","; // add a comma
		}

		--currart; // advanced to next article counter (down one number)
	}

	// open matrix file
	std::fstream matrixfile;
	std::string matrixaddress = "outputs\\matrix_"
		+ std::to_string(issues[f].year)
		+ std::to_string(issues[f].month)
		+ std::to_string(issues[f].day)
		+ "_"
		+ std::to_string(issues[f].pages[g].position)
		+ "_"
		+ issues[f].title
		+ ".txt";
	matrixfile.open(matrixaddress, std::fstream::app);
	matrixfile << pagedata; // save matrix file
	matrixfile.close();
	pagedata = ""; // reset log
}

void listMaker(int maxarticleno, int f, int g) {
	std::string pagedata = "values = ["; // start list of lists
	int currcol = 0; // first column
	int columnlist = int(issues[f].pages[g].columns.size() - 1); // last column
	int articlelist = maxarticleno - 1; // last article	
	int currart = articlelist; // first article to process (last one entered)

	while (currart >= 0)
	{
		pagedata = pagedata + "["; // create list of article word counts

		while (currcol <= columnlist) // for each column on the page
		{
			if (currart > issues[f].pages[g].columns[currcol].articles.size() - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "0"; // use 0
			}
			else {
				// if it does have a word count
				pagedata = pagedata
					+ std::to_string(issues[f].pages[g].columns[currcol].articles[currart].wc);
				// add the word count to the list
			}

			if (currcol == columnlist) // if it is the last column on the page
			{
				pagedata = pagedata + "]"; // end the article list
			}
			else // if its not
			{
				pagedata = pagedata + ","; // add comma
			}

			++currcol; // advance to next column
		}
		currcol = 0; // reset column counter

		if (currart == 0)
			// if it is the last article (of the most populated column)
		{
			pagedata = pagedata + "]"; // end the list of lists
		}
		else // if it isn't the last article
		{
			pagedata = pagedata + ","; // add a comma
		}

		--currart; // advanced to next article counter (down one number)
	}

	// open matrix file
	std::ofstream matrixfile("matrix_"
		+ std::to_string(issues[f].year)
		+ std::to_string(issues[f].month)
		+ std::to_string(issues[f].day)
		+ "_"
		+ std::to_string(issues[f].pages[g].position)
		+ "_"
		+ issues[f].title
		+ ".txt");
	matrixfile << pagedata; // save matrix file
	pagedata = ""; // reset log

}
