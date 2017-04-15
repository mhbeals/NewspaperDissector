#include "stdafx.h"

extern std::string cont;
int f; // issue counter
int g; // page counter
int h; // column counter
int i; // article counter

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
std::vector<article>articles;
struct column {
	int position;  // index column
	std::vector <article> articles;
};
std::vector <column> columns;
struct page {
	int position; // index column
	std::vector <column> columns;
};
std::vector <page> pages;
struct issue {
	int position; // index column
	std::string title; // title of newspaper
	int day; // day of issue
	int month; // month of issue
	int year; // year of issue
	std::vector <page> pages;
};
std::vector <issue> issues;

void articleInput()
{
	do {
		// Create issue struct
		issue empty{};
		f = int(issues.size());
		issues.push_back(empty);
		issues[f].position = f + 1;

		system("cls");
		std::cout << "Welcome to the Newspaper Dissector" << std::endl;
		system("pause");
		system("cls");

		std::cout << "This programme will provide you with two files:"
			<< std::endl
			<< "     a) a log of your entries"
			<< std::endl
			<< "     b) a matrix of your wordcounts"
			<< std::endl;
		system("pause");
		system("cls");

		std::cout << "The log file will update after each article"
			<< std::endl
			<< "The matrix file will only update after each page."
			<< std::endl
			<< "For best results, complete whole issues before stopping the programme."
			<< std::endl;
		system("pause");
		system("cls");

		// Populate Title
		std::cout << "What is the newspaper title? " << std::endl;
		std::cin.ignore();
		getline(std::cin, issues[f].title);

		// Populate Day
		std::cout << "Which day was it published? " << std::endl;
		std::cin >> issues[f].day;

		// Populate Month
		std::cout << "Which month was it published? (1, 2, 3, 4 ...) " << std::endl;
		std::cin >> issues[f].month;

		// Populate Year
		std::cout << "Which year was it published? " << std::endl;
		std::cin >> issues[f].year;

		// Set issue name for log file
		std::string logaddress = "outputs\\log_"
			+ std::to_string(issues[f].year)
			+ std::to_string(issues[f].month)
			+ std::to_string(issues[f].day)
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
				std::cout << "You are working on column "
					<< issues[f].pages[g].columns[h].position
					<< " of page "
					<< issues[f].pages[g].position
					<< std::endl
					<< std::endl;

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
					std::cout << "Type:" << std::endl;
					std::cin.ignore();
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].type);

					// Populate Topic
					std::cout << "Topic:" << std::endl;
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].topic);

					// Populate Geo
					std::cout << "Location Mentioned:" << std::endl;
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].geo);

					// Populate Source
					std::cout << "Source Mentioned:" << std::endl;
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].source);
					std::cout << "Is this a (l)ocation, (a)mbiguous newspaper, newspaper (t)itle, private (c)orrespondence, or (u)nknown? " << std::endl;
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].flag);

					// Populate Text and Word Count
					std::cout << "Article Text:" << std::endl;
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].text);
					issues[f].pages[g].columns[h].articles[i].wc =
						wordcount(issues[f].pages[g].columns[h].articles[i].text);


					// Print snippet log
					std::string logdata = std::to_string(issues[f].year)
						+ "\t"
						+ std::to_string(issues[f].month)
						+ "\t"
						+ std::to_string(issues[f].day)
						+ "\t"
						+ issues[f].title
						+ "\t"
						+ std::to_string(issues[f].pages[g].position)
						+ "\t"
						+ std::to_string(issues[f].pages[g].columns[h].position)
						+ "\t"
						+ std::to_string(issues[f].pages[g].columns[h].articles[i].position)
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
						+ std::to_string(issues[f].pages[g].columns[h].articles[i].wc)
						+ "\n";

					// Print graph matrix
					std::fstream issuefile;
					issuefile.open(logaddress, std::fstream::app);
					issuefile << logdata; // add entry to log
					issuefile.close(); // Closing the file

									   // Ask if there is another snippet
					std::cout << "You have just finished snippet "
						<< issues[f].pages[g].columns[h].articles[i].position
						<< ". Would you like to continue entering articles? (y or n) "
						<< std::endl;
					std::cin >> cont;

					++i; // advance article counter

				} while (cont == "y");

				// Ask if there is another column
				std::cout << "You have just finished column "
					<< issues[f].pages[g].columns[h].position
					<< ". Would you like to continue entering columns? (y or n) "
					<< std::endl;
				std::cin >> cont;

				++h; // advance column counter

			} while (cont == "y");

			// find out the most articles in any column on this page
			int maxarticleno = findmaxarticleno(f, g);

			// run the listMaker
			listMaker(maxarticleno, f, g);

			// run the colourListMaker
			colourListMaker(maxarticleno, f, g);

			// Ask if there is another page
			std::cout << "You have just finished page "
				<< issues[f].pages[g].position
				<< ". Would you like to continue entering pages? (y or n) "
				<< std::endl;
			std::cin >> cont;

			++g; // Advance page counter

		} while (cont == "y");

		std::cout << "Would you like to continue entering issues?" << std::endl;
		std::cin >> cont;
		std::cin.ignore();
	} while (cont == "y");

};