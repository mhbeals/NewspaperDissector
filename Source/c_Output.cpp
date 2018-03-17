#include "c_output.h"

//    ____                       _               _             
//   |  _ \ ___ _ __   __ _  ___| | ____ _  __ _(_)_ __   __ _ 
//   | |_) / _ \ '_ \ / _` |/ __| |/ / _` |/ _` | | '_ \ / _` |
//   |  _ <  __/ |_) | (_| | (__|   < (_| | (_| | | | | | (_| |
//   |_| \_\___| .__/ \__,_|\___|_|\_\__,_|\__, |_|_| |_|\__, |
//             |_|                         |___/         |___/ 

int c_Output::wordcount(std::string text) {
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

void c_Output::transformVector()
{
	// Create basic structure
	currentCopy.day = edition[0].day;
	currentCopy.month = edition[0].month;
	currentCopy.year = edition[0].year;
	currentCopy.title = edition[0].title;
	for (int i = 0; i < edition[edition.size() - 1].page; i++)
	{
		currentCopy.pages.push_back(emptyPage);
		currentCopy.pages[i].position = i + 1;

		for (int j = 0; j < edition[edition.size() - 1].column; j++)
		{
			currentCopy.pages[i].columns.push_back(emptyColumn);
			currentCopy.pages[i].columns[j].position = j + 1;
		}
	}

	// Fill in details
	for (size_t i = 0; i < edition.size(); i++)
	{
		size_t currentPage = edition[i].page - 1;
		size_t currentColumn = edition[i].column - 1;
		size_t currentSnippet = edition[i].snippet;
		if (currentSnippet > currentCopy.pages[currentPage].columns[currentColumn].articles.size())
		{
			currentCopy.pages[currentPage].columns[currentColumn].articles.push_back(emptyArticle);
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].position = currentSnippet;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].type = edition[i].type;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].topic = edition[i].topic;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].mentioned_location = edition[i].mentioned_location;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].source_location = edition[i].source_location;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].source = edition[i].source;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].source_type = edition[i].source_type;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].text = edition[i].text;
			currentCopy.pages[currentPage].columns[currentColumn].articles[currentSnippet - 1].wc = wordcount(edition[i].text);
		}
	}
}

//    __  __       _        _        ____        _ _     _ _             
//   |  \/  | __ _| |_ _ __(_)_  __ | __ ) _   _(_) | __| (_)_ __   __ _ 
//   | |\/| |/ _` | __| '__| \ \/ / |  _ \| | | | | |/ _` | | '_ \ / _` |
//   | |  | | (_| | |_| |  | |>  <  | |_) | |_| | | | (_| | | | | | (_| |
//   |_|  |_|\__,_|\__|_|  |_/_/\_\ |____/ \__,_|_|_|\__,_|_|_| |_|\__, |
//                                                                 |___/ 

int c_Output::typeColourFlagSwitch(std::string flag, int colourFlag)
{
	if (colourFlag == 0)
	{
		if (flag == "l")
		{
			return 0;
		}
		else if (flag == "a")
		{
			return 3;
		}
		else if (flag == "t")
		{
			return 5;
		}
		else if (flag == "c")
		{
			return 2;
		}
		else if (flag == "u")
		{
			return 9;
		}
		else
		{
			return 0;
		}
	}
	else if (colourFlag == 1)
	{
		if (flag == "l")
		{
			return 0;
		}
		else if (flag == "a")
		{
			return 50;
		}
		else if (flag == "t")
		{
			return 100;
		}
		else if (flag == "c")
		{
			return 150;
		}
		else if (flag == "u")
		{
			return 200;
		}
		else
		{
			return 225;
		}
	}
}

int c_Output::locationColourFlagSwitch(std::string flag, int colourFlag)
{
	if (colourFlag == 0)
	{
		if (flag == "l")
		{
			return 0;
		}
		else if (flag == "r")
		{
			return 3;
		}
		else if (flag == "n")
		{
			return 5;
		}
		else if (flag == "i")
		{
			return 2;
		}
		else if (flag == "u")
		{
			return 9;
		}
		else
		{
			return  0;
		}
	}
	else if (colourFlag == 1)
	{
		if (flag == "l")
		{
			return  0;
		}
		else if (flag == "r")
		{
			return 50;
		}
		else if (flag == "n")
		{
			return 100;
		}
		else if (flag == "i")
		{
			return 150;
		}
		else if (flag == "u")
		{
			return 200;
		}
		else
		{
			return 225;
		}
	}
}

std::string c_Output::colouriser(int g, int columnlist, int articlelist, int flagType, int colourFlag)
{
	std::string pagedata = ""; // create page data variable
	int currart = articlelist; // first article to process (last one entered)
	int flagInt = 0;
	int currcol = 0;

	while (currart >= 0)
	{
		while (currcol <= columnlist) // for each column on the page
		{
			if (currcol == 0)
			{
				pagedata = pagedata + "[";
			}
			if (currart > currentCopy.pages[g].columns[currcol].articles.size() - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "0"; // use 0
			}
			else {
				// if it does have a word count
				if (flagType == 0)
				{
					// If you are colourising for type
					flagInt = typeColourFlagSwitch(currentCopy.pages[g].columns[currcol].articles[currart].source_type, colourFlag);
					pagedata = pagedata + std::to_string(flagInt);
					// add the source type to the list
				}
				if (flagType == 1)
				{
					// If you are colourising for location
					// If you are colourising for type
					flagInt = locationColourFlagSwitch(currentCopy.pages[g].columns[currcol].articles[currart].source_location, colourFlag);
					pagedata = pagedata + std::to_string(flagInt);
					// add the source type to the list
				}
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
	return pagedata;
}

std::string c_Output::wordCountiser(int g, int columnlist, int articlelist)
{
	std::string pagedata = "["; // create page data variable
	int currart = articlelist; // first article to process (last one entered)
	int flagInt = 0;
	int currcol = 0;

	while (currart >= 0)
	{
		pagedata = pagedata + "["; // create list of article word counts

		while (currcol <= columnlist) // for each column on the page
		{
			if (currart > currentCopy.pages[g].columns[currcol].articles.size() - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "0"; // use 0
			}
			else {
				// if it does have a word count
				pagedata = pagedata
					+ std::to_string(currentCopy.pages[g].columns[currcol].articles[currart].wc);
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
	return pagedata;
}

std::string c_Output::labeliser(int g, int columnlist, int articlelist)
{
	std::string pagedata = "["; // create page data variable
	int currart = articlelist; // first article to process (last one entered)
	int flagInt = 0;
	int currcol = 0;

	while (currart >= 0)
	{
		pagedata = pagedata + "["; // create list of article word counts

		while (currcol <= columnlist) // for each column on the page
		{
			if (currart > currentCopy.pages[g].columns[currcol].articles.size() - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "'Unknown'"; // use 0
			}
			else {
				// if it does have a word count
				pagedata = pagedata
					+ "'" + (currentCopy.pages[g].columns[currcol].articles[currart].type) + "'";
				// add the article type to the list
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
	return pagedata;
}

//   __     ___                 _ _           _   _             
//   \ \   / (_)___ _   _  __ _| (_)___  __ _| |_(_) ___  _ __  
//    \ \ / /| / __| | | |/ _` | | / __|/ _` | __| |/ _ \| '_ \ 
//     \ V / | \__ \ |_| | (_| | | \__ \ (_| | |_| | (_) | | | |
//      \_/  |_|___/\__,_|\__,_|_|_|___/\__,_|\__|_|\___/|_| |_|
//    

int c_Output::findmaxarticleno(int g)
{
	size_t maxno = 0; // start with assumption of 0 articles as test condition
	for (size_t j = 0; j < currentCopy.pages[g].columns.size(); j++) // for every column
	{
		if (maxno < currentCopy.pages[g].columns[j].articles.size())
			// check to see if its number of articles is the most you've seen so far
		{
			maxno = int(currentCopy.pages[g].columns[j].articles.size());
			// if it is, change the test condition
		}
	}
	return maxno; // send maximum number of articles / column for this page onward
}

void c_Output::graphicMaker(int flagInt, int colourFlag)
{
	std::string pageData = ""; // declare page data matrix variable
	std::string pythonScript = "import matplotlib.pyplot as plt\nimport numpy as np\n"; // declare python script variable
	currentCopy.title.erase(std::remove(currentCopy.title.begin(), currentCopy.title.end(), ' '), currentCopy.title.end()); // remove spaces from title
	std::string filenameStub = currentCopy.title + "_" + std::to_string(currentCopy.year) + std::to_string(currentCopy.month) + std::to_string(currentCopy.day);
	std::string filename;

	for (size_t g = 0; g < currentCopy.pages.size(); g++)
	{
		int columnlist = int(currentCopy.pages[g].columns.size() - 1); // last column
		int articlelist = findmaxarticleno(g) - 1; // last article	

		pageData = colouriser(g, columnlist, articlelist, flagInt, colourFlag);
		pythonScript = pythonScript + "values_colour = [" + pageData + "\nvalues = "; // begin python file
		pageData = wordCountiser(g, columnlist, articlelist);
		pythonScript = pythonScript + pageData + "\nvalues_text=";
		pageData = labeliser(g, columnlist, articlelist);
		pythonScript = pythonScript + pageData + "\nmax_cols = len(values)\nmax_rows = len(values[0])\nvalues_sums = [sum([r[i] for r in values]) for i in range(max_rows)]\nvalues_norm = [[v / values_sums[i] for i, v in enumerate(row)] for row in values]\nfig, ax = plt.subplots(1, figsize = (16, 20))\nfor row_num in range(max_cols) :\n\tax.bar(range(max_rows), values_norm[row_num], bottom = [sum([values_norm[i][j] for i in range(row_num)]) for j in range(max_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('";
		if (colourFlag == 0) { pythonScript = pythonScript + "Set1"; }
		else if (colourFlag == 1) { pythonScript = pythonScript + "Greys"; }
		pythonScript = pythonScript + "')(i) for i in values_colour[row_num]])\nax.set_xlim(-0.5, max_rows - 0.5)\nax.set_xticks([])\nax.set_yticks([])\nax.set_ylim(0, 1)\nfor x in range(max_rows) :\n\tfor y in range(max_cols) :\n\t\tif values[y][x] != 0.0:\n\t\t\t\tax.text(x, values_norm[y][x] / 2 + sum([values_norm[newy][x] for newy in range(y)])-.005, values_text[y][x], fontsize = 12, ha='center')\nplt.savefig(\"";
		if (colourFlag == 0) { pythonScript = pythonScript + "Colour_"; }
		else if (colourFlag == 1) { pythonScript = pythonScript + "BW_"; }
		if (flagInt == 0) { pythonScript = pythonScript + "Type_" + filenameStub + "_" + std::to_string(currentCopy.pages[g].position) + ".png\")\n"; }
		else if (flagInt == 1) { pythonScript = pythonScript + "Location_" + filenameStub + "_" + std::to_string(currentCopy.pages[g].position) + ".png\")\n"; }
	}

	// Complete python file with legends
	pythonScript = pythonScript + "\nlvalues = [[50],[50],[50],[50],[50]]\nlvalues_colour = [[0],[3],[2],[5],[9]]\nlabels = ['Location', 'Ambiguous Publication','Named Publication', 'Correspondence','Undetermined']\nlmax_cols = len(lvalues)\nlmax_rows = len(lvalues[0])\nlvalues_sums = [sum([r[i] for r in lvalues]) for i in range(lmax_rows)]\nlvalues_norm = [[v/lvalues_sums[i] for i, v in enumerate(row)] for row in lvalues]\nfig, ax = plt.subplots(1, figsize=(4, 20))\nfor row_num in range(lmax_cols):\n\tax.bar(range(lmax_rows), lvalues_norm[row_num], bottom=[sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width=1, edgecolor='#000000',  color=[plt.get_cmap('Set1')(i) for i in lvalues_colour[row_num]])\nax.set_xlim(-0.5, lmax_rows-0.5)\nax.set_xticks([])\nax.set_yticks([])\nax.set_ylim(0, 1)\nfor x in range(lmax_rows):\n\tfor y in range(lmax_cols):\n\t\tif lvalues[y][x] != 0.0:\n\t\t\tax.text(x, lvalues_norm[y][x]/2-.005 + sum([lvalues_norm[newy][x] for newy in range(y)]), labels[y], fontsize=12, ha='center')\nplt.savefig('Colour_Type_Legend.png')\nlvalues = [[50],[50],[50],[50],[50]]\nlvalues_colour = [[0],[50],[100],[150],[200]]\nlabels = ['Location', 'Ambiguous Publication','Named Publication', 'Correspondence','Undetermined']\nlmax_cols = len(lvalues)\nlmax_rows = len(lvalues[0])\nlvalues_sums = [sum([r[i] for r in lvalues]) for i in range(lmax_rows)]\nlvalues_norm = [[v/lvalues_sums[i] for i, v in enumerate(row)] for row in lvalues]\nfig, ax = plt.subplots(1, figsize=(4, 20))\nfor row_num in range(lmax_cols):\n\tax.bar(range(lmax_rows), lvalues_norm[row_num], bottom=[sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width=1, edgecolor='#000000',  color=[plt.get_cmap('Greys')(i) for i in lvalues_colour[row_num]])\nax.set_xlim(-0.5, lmax_rows-0.5)\nax.set_xticks([])\nax.set_yticks([])\nax.set_ylim(0, 1)\nfor x in range(lmax_rows):\n\tfor y in range(lmax_cols):\n\t\tif lvalues[y][x] != 0.0:\n\t\t\tax.text(x, lvalues_norm[y][x]/2-.005 + sum([lvalues_norm[newy][x] for newy in range(y)]), labels[y], fontsize=12, ha='center')\nplt.savefig('BW_Type_Legend.png')\nlvalues = [[50],[50],[50],[50],[50]]\nlvalues_colour = [[0],[3],[2],[5],[9]]\nlabels = ['Local', 'Regional','National', 'International','Undetermined']\nlmax_cols = len(lvalues)\nlmax_rows = len(lvalues[0])\nlvalues_sums = [sum([r[i] for r in lvalues]) for i in range(lmax_rows)]\nlvalues_norm = [[v/lvalues_sums[i] for i, v in enumerate(row)] for row in lvalues]\nfig, ax = plt.subplots(1, figsize=(4, 20))\nfor row_num in range(lmax_cols):\n\tax.bar(range(lmax_rows), lvalues_norm[row_num], bottom=[sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width=1, edgecolor='#000000',  color=[plt.get_cmap('Set1')(i) for i in lvalues_colour[row_num]])\nax.set_xlim(-0.5, lmax_rows-0.5)\nax.set_xticks([])\nax.set_yticks([])\nax.set_ylim(0, 1)\nfor x in range(lmax_rows):\n\tfor y in range(lmax_cols):\n\t\tif lvalues[y][x] != 0.0:\n\t\t\tax.text(x, lvalues_norm[y][x]/2-.005 + sum([lvalues_norm[newy][x] for newy in range(y)]), labels[y], fontsize=12, ha='center')\nplt.savefig('Colour_Location_Legend.png')\nlvalues = [[50],[50],[50],[50],[50]]\nlvalues_colour = [[0],[50],[100],[150],[200]]\nlabels = ['Local', 'Regional','National', 'International','Undetermined']\nlmax_cols = len(lvalues)\nlmax_rows = len(lvalues[0])\nlvalues_sums = [sum([r[i] for r in lvalues]) for i in range(lmax_rows)]\nlvalues_norm = [[v/lvalues_sums[i] for i, v in enumerate(row)] for row in lvalues]\nfig, ax = plt.subplots(1, figsize=(4, 20))\nfor row_num in range(lmax_cols):\n\tax.bar(range(lmax_rows), lvalues_norm[row_num], bottom=[sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width=1, edgecolor='#000000',  color=[plt.get_cmap('Greys')(i) for i in lvalues_colour[row_num]])\nax.set_xlim(-0.5, lmax_rows-0.5)\nax.set_xticks([])\nax.set_yticks([])\nax.set_ylim(0, 1)\nfor x in range(lmax_rows):\n\tfor y in range(lmax_cols):\n\t\tif lvalues[y][x] != 0.0:\n\t\t\tax.text(x, lvalues_norm[y][x]/2-.005 + sum([lvalues_norm[newy][x] for newy in range(y)]), labels[y], fontsize=12, ha='center')\nplt.savefig('BW_Location_Legend.png')";

	// open python file
	if (colourFlag == 0) { filename = "Colour_"; }
	else if (colourFlag == 1) { filename = "BW_"; }
	if (flagInt == 0) { filename = filename + "type_" + filenameStub + ".py"; }
	else if (flagInt == 1) { filename = filename + "location_" + filenameStub + ".py"; }

	std::ofstream matrixfile(filename);
	matrixfile << pythonScript; // save data to file
	matrixfile.close();

	std::fstream batchFilename;
	batchFilename.open("createGraphics.bat", std::fstream::app);
	filename = "python " + filename + "\ndel " + filename + "\n";
	batchFilename << filename;

}
