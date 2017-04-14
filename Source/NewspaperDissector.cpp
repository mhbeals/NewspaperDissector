// Newspaper Dissector
// M. H. Beals (2017) v.0.1.7.0 [Software]

// MIT License
// Copyright(c) 2017 M. H. Beals
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <Lmcons.h>
using namespace std;

string cont; // boolean to continue section type
int f; // issue counter
int g; // page counter
int h; // column counter
int i; // article counter

struct article {
	int position; // index column
	string type; // type of entry
	string topic; // topic of entry
	string geo; // geographic location mentioned in article
	string flag; // source indicator
	string source; // source text 
	string text; // text of article
	int wc; // auto-generated wordcount of article
};
vector<article>articles;
struct column {
	int position;  // index column
	vector <article> articles;
};
vector <column> columns;
struct page {
	int position; // index column
	vector <column> columns;
};
vector <page> pages;
struct issue {
	int position; // index column
	string title; // title of newspaper
	int day; // day of issue
	int month; // month of issue
	int year; // year of issue
	vector <page> pages;
};
vector <issue> issues;

void saveDatabase()
{
	// Set issue name for save file
	string saveaddress = "autosave.txt";
	string savedata = "";

	for (int f = 0; f < issues.size(); f++)
	{
		if (f != 0)
		{
			savedata = savedata + "y\n";
		}
		for (int g = 0; g < issues[f].pages.size(); g++)
		{
			for (int h = 0; h < issues[f].pages[g].columns.size(); h++)
			{
				if (h != 0)
				{
					savedata = savedata + "y\n";
				}
				for (int i = 0; i < issues[f].pages[g].columns[h].articles.size(); i++)
				{
					if (i == 0 && h == 0 && g == 0)
					{
						savedata = savedata
							+ issues[f].title
							+ "\n"
							+ to_string(issues[f].day)
							+ "\n"
							+ to_string(issues[f].month)
							+ "\n"
							+ to_string(issues[f].year)
							+ "\n";
					}
					else if (i == 0 && h != 0)
					{

					}
					else
					{
						savedata = savedata + "y\n";
					}
					// Print data
					savedata = savedata
						+ issues[f].pages[g].columns[h].articles[i].type
						+ "\n"
						+ issues[f].pages[g].columns[h].articles[i].topic
						+ "\n"
						+ issues[f].pages[g].columns[h].articles[i].geo
						+ "\n"
						+ issues[f].pages[g].columns[h].articles[i].flag
						+ "\n"
						+ issues[f].pages[g].columns[h].articles[i].source
						+ "\n"
						+ issues[f].pages[g].columns[h].articles[i].text
						+ "\n";
					if (i == issues[f].pages[g].columns[h].articles.size() - 1)
					{
						savedata = savedata + "n\n";
					}
				}
				if (h == issues[f].pages[g].columns.size() - 1)
				{
					savedata = savedata + "n\n";
				}
			}
			if (g == issues[f].pages.size() - 1)
			{
				savedata = savedata + "n\n";
			}
		}
		if (f == issues.size() - 1)
		{
			savedata = savedata + "n\n";
		}
	}

	// Print save file
	ofstream savefile(saveaddress);
	savefile << savedata; // save file
}

int findmaxarticleno(int f, int g)
{
	int maxno = 0; // start with assumption of 0 articles as test condition
	for (int j = 0; j < issues[f].pages[g].columns.size(); j++) // for every column
	{
		if (maxno < issues[f].pages[g].columns[j].articles.size())
			// check to see if its number of articles is the most you've seen so far
		{
			maxno = issues[f].pages[g].columns[j].articles.size();
			// if it is, change the test condition
		}
	}
	return maxno; // send maximum number of articles / column for this page onward
}

int wordcount(string text) {
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

int colourFlagSwitch(string flag)
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

void colourListMaker(int maxarticleno, int f, int g) {
	string pagedata = "\nvalues_colour = ["; // start list of lists
	int currcol = 0; // first column
	int columnlist = issues[f].pages[g].columns.size() - 1; // last column
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
				pagedata = pagedata + to_string(flagInt);
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
	fstream matrixfile;
	string matrixaddress = "matrix_"
		+ to_string(issues[f].year)
		+ to_string(issues[f].month)
		+ to_string(issues[f].day)
		+ "_"
		+ to_string(issues[f].pages[g].position)
		+ "_"
		+ issues[f].title
		+ ".txt";
	matrixfile.open(matrixaddress, fstream::app);
	matrixfile << pagedata; // save matrix file
	matrixfile.close();
	pagedata = ""; // reset log
}

void listMaker(int maxarticleno, int f, int g) {
	string pagedata = "values = ["; // start list of lists
	int currcol = 0; // first column
	int columnlist = issues[f].pages[g].columns.size() - 1; // last column
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
					+ to_string(issues[f].pages[g].columns[currcol].articles[currart].wc);
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
	ofstream matrixfile("matrix_"
		+ to_string(issues[f].year)
		+ to_string(issues[f].month)
		+ to_string(issues[f].day)
		+ "_"
		+ to_string(issues[f].pages[g].position)
		+ "_"
		+ issues[f].title
		+ ".txt");
	matrixfile << pagedata; // save matrix file
	pagedata = ""; // reset log

}

void articleInput()
{
	do {
		// Create issue struct
		issue empty{};
		f = issues.size();
		issues.push_back(empty);
		issues[f].position = f + 1;

		system("cls");
		cout << "Welcome to the Newspaper Dissector" << endl;
		system("pause");
		system("cls");

		cout << "This programme will provide you with two files:"
			<< endl
			<< "     a) a log of your entries"
			<< endl
			<< "     b) a matrix of your wordcounts"
			<< endl;
		system("pause");
		system("cls");

		cout << "The log file will update after each article"
			<< endl
			<< "The matrix file will only update after each page."
			<< endl
			<< "For best results, complete whole issues before stopping the programme."
			<< endl;
		system("pause");
		system("cls");

		// Populate Title
		cout << "What is the newspaper title? " << endl;
		cin.ignore();
		getline(cin, issues[f].title);

		// Populate Day
		cout << "Which day was it published? " << endl;
		cin >> issues[f].day;

		// Populate Month
		cout << "Which month was it published? (1, 2, 3, 4 ...) " << endl;
		cin >> issues[f].month;

		// Populate Year
		cout << "Which year was it published? " << endl;
		cin >> issues[f].year;

		// Set issue name for log file
		string logaddress = "log_"
			+ to_string(issues[f].year)
			+ to_string(issues[f].month)
			+ to_string(issues[f].day)
			+ "_"
			+ issues[f].title
			+ ".txt";

		// Reset page counter
		g = 0;

		// For each page
		do {

			// Create page struct
			page empty;
			issues[f].pages.push_back(empty);

			// Fill in page number
			issues[f].pages[g].position = g + 1;

			// Reset column count
			h = 0;

			// For each column
			do {
				column empty;
				issues[f].pages[g].columns.push_back(empty);

				// Fill in column number
				issues[f].pages[g].columns[h].position = h + 1;
				cout << "You are working on column "
					<< issues[f].pages[g].columns[h].position
					<< " of page "
					<< issues[f].pages[g].position
					<< endl
					<< endl;

				// Reset snippet count
				i = 0;

				// For each snippet
				do {

					// Create snippet
					article empty;
					issues[f].pages[g].columns[h].articles.push_back(empty);

					// Populate Postion
					issues[f].pages[g].columns[h].articles[i].position = i + 1;

					// Populate Type
					cout << "Type:" << endl;
					cin.ignore();
					getline(cin, issues[f].pages[g].columns[h].articles[i].type);

					// Populate Topic
					cout << "Topic:" << endl;
					getline(cin, issues[f].pages[g].columns[h].articles[i].topic);

					// Populate Geo
					cout << "Location Mentioned:" << endl;
					getline(cin, issues[f].pages[g].columns[h].articles[i].geo);

					// Populate Source
					cout << "Source Mentioned:" << endl;
					getline(cin, issues[f].pages[g].columns[h].articles[i].source);
					cout << "Is this a (l)ocation, (a)mbiguous newspaper, newspaper (t)itle, private (c)orrespondence, or (u)nknown? " << endl;
					getline(cin, issues[f].pages[g].columns[h].articles[i].flag);

					// Populate Text and Word Count
					cout << "Article Text:" << endl;
					getline(cin, issues[f].pages[g].columns[h].articles[i].text);
					issues[f].pages[g].columns[h].articles[i].wc =
						wordcount(issues[f].pages[g].columns[h].articles[i].text);


					// Print snippet log
					string logdata = to_string(issues[f].year)
						+ "\t"
						+ to_string(issues[f].month)
						+ "\t"
						+ to_string(issues[f].day)
						+ "\t"
						+ issues[f].title
						+ "\t"
						+ to_string(issues[f].pages[g].position)
						+ "\t"
						+ to_string(issues[f].pages[g].columns[h].position)
						+ "\t"
						+ to_string(issues[f].pages[g].columns[h].articles[i].position)
						+ "\t"
						+ issues[f].pages[g].columns[h].articles[i].type
						+ "\t"
						+ issues[f].pages[g].columns[h].articles[i].topic
						+ "\t"
						+ issues[f].pages[g].columns[h].articles[i].geo
						+ "\t"
						+ issues[f].pages[g].columns[h].articles[i].flag
						+ "\t"
						+ issues[f].pages[g].columns[h].articles[i].source
						+ "\t"
						+ issues[f].pages[g].columns[h].articles[i].text
						+ "\t"
						+ to_string(issues[f].pages[g].columns[h].articles[i].wc)
						+ "\n";

					// Print graph matrix
					fstream issuefile;
					issuefile.open(logaddress, fstream::app);
					issuefile << logdata; // add entry to log
					issuefile.close(); // Closing the file

									   // Ask if there is another snippet
					cout << "You have just finished snippet "
						<< issues[f].pages[g].columns[h].articles[i].position
						<< ". Would you like to continue entering articles? (y or n) "
						<< endl;
					cin >> cont;

					++i; // advance article counter

				} while (cont == "y");

				// Ask if there is another column
				cout << "You have just finished column "
					<< issues[f].pages[g].columns[h].position
					<< ". Would you like to continue entering columns? (y or n) "
					<< endl;
				cin >> cont;

				++h; // advance column counter

			} while (cont == "y");

			// find out the most articles in any column on this page
			int maxarticleno = findmaxarticleno(f, g);

			// run the listMaker
			listMaker(maxarticleno, f, g);

			// run the colourListMaker
			colourListMaker(maxarticleno, f, g);

			// Ask if there is another page
			cout << "You have just finished page "
				<< issues[f].pages[g].position
				<< ". Would you like to continue entering pages? (y or n) "
				<< endl;
			cin >> cont;

			++g; // Advance page counter

		} while (cont == "y");

		cout << "Would you like to continue entering issues?" << endl;
		cin >> cont;
		cin.ignore();
	} while (cont == "y");

};

void loadSave()
{
	cout << "Paste save data" << endl;
	do {
		issue empty{};
		issues.push_back(empty);
		issues[f].position = f + 1;
		cin.ignore();
		getline(cin, issues[f].title);
		cin >> issues[f].day;
		cin >> issues[f].month;
		cin >> issues[f].year;
		g = 0;
		do {
			page empty;
			issues[f].pages.push_back(empty);
			issues[f].pages[g].position = g + 1;
			h = 0;
			do {
				column empty;
				issues[f].pages[g].columns.push_back(empty);
				issues[f].pages[g].columns[h].position = h + 1;
				i = 0;
				do {
					article empty;
					issues[f].pages[g].columns[h].articles.push_back(empty);
					issues[f].pages[g].columns[h].articles[i].position = i + 1;
					cin.ignore();
					getline(cin, issues[f].pages[g].columns[h].articles[i].type);
					getline(cin, issues[f].pages[g].columns[h].articles[i].topic);
					getline(cin, issues[f].pages[g].columns[h].articles[i].geo);
					getline(cin, issues[f].pages[g].columns[h].articles[i].flag);
					getline(cin, issues[f].pages[g].columns[h].articles[i].source);
					getline(cin, issues[f].pages[g].columns[h].articles[i].text);
					issues[f].pages[g].columns[h].articles[i].wc =
						wordcount(issues[f].pages[g].columns[h].articles[i].text);
					cin >> cont;
					++i; // advance article counter
				} while (cont == "y");
				cin >> cont;
				++h; // advance column counter
			} while (cont == "y");
			cin >> cont;
			++g; // Advance page counter
		} while (cont == "y");
		cin >> cont;
	} while (cont == "y");
	cout << "Record " << f + 1 << " loaded." << endl;
	system("pause");
};


int main()
{
	cout << "Do you have a saved database?" << endl;
	cin >> cont;
	if (cont == "y")
	{
		loadSave(); // load saved database
	};

	articleInput(); // start process

	saveDatabase();

	return 0;
}