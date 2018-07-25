#include "c_Output.h"


//   __      ___                 _ _           _   _             
//   \ \    / (_)               | (_)         | | (_)            
//    \ \  / / _ ___ _   _  __ _| |_ ___  __ _| |_ _  ___  _ __  
//     \ \/ / | / __| | | |/ _` | | / __|/ _` | __| |/ _ \| '_ \ 
//      \  /  | \__ \ |_| | (_| | | \__ \ (_| | |_| | (_) | | | |
//       \/   |_|___/\__,_|\__,_|_|_|___/\__,_|\__|_|\___/|_| |_|
//                                                               
//                                                               

std::string c_Output::colouriser(int g, int columnlist, int articlelist, std::string colourFlag)
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
			if (currart > int(transformationInstance.currentCopy.pages[g].columns[currcol].articles.size()) - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "0"; // use 0
			}
			else {
				// if it does have a word count
				std::string key_value = transformationInstance.currentCopy.pages[g].columns[currcol].articles[currart].key_value;

				for (size_t i = 0; i < legendInstance.legendEntries.size(); i++)
				{
					if (key_value == legendInstance.legendEntries[i].keyCharacter)
					{
						pagedata = pagedata + std::to_string(legendInstance.selectedColourScheme[i]); // use legend colour
					}
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
			if (currart > int(transformationInstance.currentCopy.pages[g].columns[currcol].articles.size()) - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "0"; // use 0
			}
			else {
				// if it does have a word count
				pagedata = pagedata
					+ std::to_string(transformationInstance.currentCopy.pages[g].columns[currcol].articles[currart].wc);
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
			if (currart > int(transformationInstance.currentCopy.pages[g].columns[currcol].articles.size()) - 1)
				// if it doesn't have a word count
			{
				pagedata = pagedata + "'No Content'"; // use 0
			}
			else {
				// if it does have a word count
				pagedata = pagedata
					+ "'" + (transformationInstance.currentCopy.pages[g].columns[currcol].articles[currart].type) + "'";
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

int c_Output::findmaxarticleno(int g)
{
	size_t maxno = 0; // start with assumption of 0 articles as test condition
	for (size_t j = 0; j < transformationInstance.currentCopy.pages[g].columns.size(); j++) // for every column
	{
		if (maxno < transformationInstance.currentCopy.pages[g].columns[j].articles.size())
			// check to see if its number of articles is the most you've seen so far
		{
			maxno = int(transformationInstance.currentCopy.pages[g].columns[j].articles.size());
			// if it is, change the test condition
		}
	}
	return maxno; // send maximum number of articles / column for this page onward
}

void c_Output::graphicMaker(std::string colourFlag)
{
	// declare filename variable
	std::string filename;

	// remove spaces from title
	transformationInstance.currentCopy.documentID.erase(std::remove(transformationInstance.currentCopy.documentID.begin(), transformationInstance.currentCopy.documentID.end(), ' '), transformationInstance.currentCopy.documentID.end()); 
	
	// create filename stub
	std::string filenameStub = transformationInstance.currentCopy.documentID;
	
	// declare and start python script variable
	std::string pythonScript = "import matplotlib.pyplot as plt" + lineBreak
		+ "import numpy as np" + lineBreak;

	// declare page data matrix variable
	std::string pageData = ""; 

	// for each page
	for (size_t g = 0; g < transformationInstance.currentCopy.pages.size(); g++)
	{
		// set max columns and articles
		int columnlist = int(transformationInstance.currentCopy.pages[g].columns.size() - 1); // last column
		int articlelist = findmaxarticleno(g) - 1; // last article	

		// create colour matrix
		pageData = colouriser(g, columnlist, articlelist, colourFlag);

		// add colour matrix to python file
		pythonScript = pythonScript + "values_colour = [" + pageData + lineBreak; 
		
		// create wordcount matrix
		pageData = wordCountiser(g, columnlist, articlelist);

		// add wordcount matrix data to python file
		pythonScript = pythonScript + "values = " + pageData + lineBreak;
		
		// create label matrix
		pageData = labeliser(g, columnlist, articlelist);
		
		// add label matrix to python file
		pythonScript = pythonScript + "values_text = " + pageData + lineBreak;

		// add general python scripting
		pythonScript = pythonScript 
			+ "max_cols = len(values)" + lineBreak
			+ "max_rows = len(values[0])" + lineBreak
			+ "values_sums = [sum([r[i] for r in values]) for i in range(max_rows)]" + lineBreak
			+ "values_norm = [[v / values_sums[i] for i, v in enumerate(row)] for row in values]" + lineBreak
			+ "fig, ax = plt.subplots(1, figsize = (12, 20))" + lineBreak
			+ "for row_num in range(max_cols) :" + lineBreak 
			+ tab + "ax.bar(range(max_rows), values_norm[row_num], bottom = [sum([values_norm[i][j] for i in range(row_num)]) for j in range(max_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('";

		// add colour spectrum type
		if (colourFlag == "F") { pythonScript = pythonScript + "Paired"; }
		else if (colourFlag == "C") { pythonScript = pythonScript + "Set1"; }
		else if (colourFlag == "G") { pythonScript = pythonScript + "gray"; }
		else if (colourFlag == "P") { pythonScript = pythonScript + "gray"; }

		// add general python scripting
		pythonScript = pythonScript + "')(i) for i in values_colour[row_num]])" + lineBreak
			+ "ax.set_xlim(-0.5, max_rows - 0.5)\nax.set_xticks([])\nax.set_yticks([])" + lineBreak
			+ "ax.set_ylim(0, 1)\nfor x in range(max_rows) :\n\tfor y in range(max_cols) :" + lineBreak 
			+ tab + tab + "if values[y][x] != 0.0:\n\t\t\t\tax.text(x, values_norm[y][x] / 2 + sum([values_norm[newy][x] for newy in range(y)]), values_text[y][x], fontsize = 10, ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=.1'))" + lineBreak
			+ "plt.savefig(\"";

		// Set colour spectrum prefix to filename of visualisation
		if (colourFlag == "F") { pythonScript = pythonScript + "Colour_"; }
		else if (colourFlag == "C") { pythonScript = pythonScript + "Colourblind_"; }
		else if (colourFlag == "G") { pythonScript = pythonScript + "Greyscale_"; }
		else if (colourFlag == "P") { pythonScript = pythonScript + "Patterned_"; }

		// complete python script
		pythonScript = pythonScript + filenameStub + "_" + std::to_string(transformationInstance.currentCopy.pages[g].position) + ".png\", bbox_inches='tight')" + lineBreak;
	}

	// set colour spectrum prefix to filename of visualisation script
	if (colourFlag == "F") { filename = "Colour_"; }
	else if (colourFlag == "C") { filename = "Colourblind_"; }
	else if (colourFlag == "G") { filename = "Greyscale_"; }
	else if (colourFlag == "P") { filename = "Patterned_"; }

	// complete filename
	filename = filename + filenameStub + ".py";

	// open python file
	std::ofstream matrixfile(filename);
	
	// save data to file
	matrixfile << pythonScript; 
	matrixfile.close();

	// create windows batch file to run python script, with "python" command
	std::fstream batchFilename;
	batchFilename.open("createGraphics.bat", std::fstream::app);
	filename = "python legends.py" + lineBreak 
		+ "python " + filename + lineBreak;
	batchFilename << filename;

}