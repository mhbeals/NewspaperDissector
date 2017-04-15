#include "stdafx.h"

extern std::string cont;
extern int f;
extern int g;
extern int h;
extern int i;
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

void saveDatabase()
{
	// Set issue name for save file
	std::string saveaddress = "outputs\\autosave.txt";
	std::string savedata = "";

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
							+ std::to_string(issues[f].day)
							+ "\n"
							+ std::to_string(issues[f].month)
							+ "\n"
							+ std::to_string(issues[f].year)
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
	std::ofstream savefile(saveaddress);
	savefile << savedata; // save file
}

void loadSave()
{
	std::cout << "Paste save data" << std::endl;
	do {
		issue empty{};
		issues.push_back(empty);
		issues[f].position = f + 1;
		std::cin.ignore();
		getline(std::cin, issues[f].title);
		std::cin >> issues[f].day;
		std::cin >> issues[f].month;
		std::cin >> issues[f].year;
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
					std::cin.ignore();
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].type);
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].topic);
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].geo);
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].flag);
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].source);
					getline(std::cin, issues[f].pages[g].columns[h].articles[i].text);
					issues[f].pages[g].columns[h].articles[i].wc =
						wordcount(issues[f].pages[g].columns[h].articles[i].text);
					std::cin >> cont;
					++i; // advance article counter
				} while (cont == "y");
				std::cin >> cont;
				++h; // advance column counter
			} while (cont == "y");
			std::cin >> cont;
			++g; // Advance page counter
		} while (cont == "y");
		std::cin >> cont;
	} while (cont == "y");
	std::cout << "Record " << f + 1 << " loaded." << std::endl;
	system("pause");
};
