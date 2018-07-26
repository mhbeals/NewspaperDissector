#include "c_LegendCreation.h"


//    _                               _    _____                _   _             
//   | |                             | |  / ____|              | | (_)            
//   | |     ___  __ _  ___ _ __   __| | | |     _ __ ___  __ _| |_ _  ___  _ __  
//   | |    / _ \/ _` |/ _ \ '_ \ / _` | | |    | '__/ _ \/ _` | __| |/ _ \| '_ \ 
//   | |___|  __/ (_| |  __/ | | | (_| | | |____| | |  __/ (_| | |_| | (_) | | | |
//   |______\___|\__, |\___|_| |_|\__,_|  \_____|_|  \___|\__,_|\__|_|\___/|_| |_|
//                __/ |                                                           
//               |___/                                                            

void c_LegendCreation::legendCreator(std::vector<entry> legendEntries, std::string inputDirectory)
{
	// Size legend boxes for horizontal legend
	int block = 250 / legendItemCount;

	// Begin python script
	std::string pythonScript = "import matplotlib.pyplot as plt" + lineBreak
		+ "import numpy as np" + lineBreak
		+ "lvalues = [[";

	// Create legend boxes
	for (int i = 0; i < legendItemCount; i++)
	{
		pythonScript = pythonScript + std::to_string(block);
		if (i+1 != legendItemCount) { pythonScript = pythonScript + ","; }
	}

	pythonScript = pythonScript + "]]" + lineBreak;
	
	// Create legend colours
	pythonScript = pythonScript + "lvalues_colour =[[";

	for (int i = 0; i < legendItemCount; i++)
	{
		pythonScript = pythonScript + std::to_string(selectedColourScheme[i]);
		if (i+1 != legendItemCount){pythonScript = pythonScript + ","; }
	}

	pythonScript = pythonScript + "]]" + lineBreak;
		
	// Create legend labels
	pythonScript = pythonScript + "lvalues_text = [[";

	for (size_t i = 0; i < legendEntries.size(); i++)
	{
		pythonScript = pythonScript + "'" + legendEntries[i].keyWord;
		if (i+1 < size_t(legendItemCount)) { pythonScript = pythonScript + "', "; }
	}

	pythonScript = pythonScript + "']]" + lineBreak;
	
	// Add Patterns Data, if required
	if (legendColourScheme == "P")
	{
		pythonScript = pythonScript + "lvalues_pattern = [[";

		for (size_t i = 0; i < legendEntries.size(); i++)
		{
			pythonScript = pythonScript + "'" + patternScheme[i];
			if (i + 1 < size_t(legendItemCount)) { pythonScript = pythonScript + "', "; }
		}
		pythonScript = pythonScript + "']]" + lineBreak;
	}

	// Add in standard python scripting
	pythonScript = pythonScript + "lmax_cols = len(lvalues)" + lineBreak
		+ "lmax_rows = len(lvalues[0])" + lineBreak
		+ "lvalues_sums = [sum([r[i] for r in lvalues]) for i in range(lmax_rows)]" + lineBreak
		+ "lvalues_norm = [[v/lvalues_sums[i] for i, v in enumerate(row)] for row in lvalues]" + lineBreak
		+ "fig, ax = plt.subplots(1, figsize=(50, 2))" + lineBreak
		+ "for row_num in range(lmax_cols):" + lineBreak;
	
	// Colourise without patterns
	if (legendColourScheme != "P")
	{
		pythonScript = pythonScript + tab + "ax.bar(range(lmax_rows), lvalues_norm[row_num], bottom = [sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('";

		// add colour spectrum type
		if (legendColourScheme == "F") { pythonScript = pythonScript + "Paired"; }
		else if (legendColourScheme == "C") { pythonScript = pythonScript + "Set1"; }
		else if (legendColourScheme == "G") { pythonScript = pythonScript + "Greys"; }
		else if (legendColourScheme == "P") { pythonScript = pythonScript + "Greys"; }

		// add general python scripting
		pythonScript = pythonScript + "')(i) for i in lvalues_colour[row_num]])" + lineBreak;

	}

	// OR Colourise and add pattern overlay, if required
	else if (legendColourScheme == "P")
	{
		pythonScript = pythonScript + tab + "bars = ax.bar(range(lmax_rows), lvalues_norm[row_num], bottom = [sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('";

		// add colour spectrum type
		if (legendColourScheme == "F") { pythonScript = pythonScript + "Paired"; }
		else if (legendColourScheme == "C") { pythonScript = pythonScript + "Set1"; }
		else if (legendColourScheme == "G") { pythonScript = pythonScript + "Greys"; }
		else if (legendColourScheme == "P") { pythonScript = pythonScript + "Greys"; }

		// add general python scripting
		pythonScript = pythonScript + "')(i) for i in lvalues_colour[row_num]])" + lineBreak
			+ tab + "for bar, pattern in zip(bars, lvalues_pattern[row_num]):" + lineBreak
			+ tab + tab + "bar.set_hatch(pattern)" + lineBreak;
	}

	// Complete python script
	pythonScript = pythonScript + "ax.set_xlim(-0.5, lmax_rows-.5)" + lineBreak
		+ "ax.set_xticks([])" + lineBreak
		+ "ax.set_yticks([])" + lineBreak
		+ "ax.set_ylim(0, 1)" + lineBreak
		+ "for x in range(lmax_rows):" + lineBreak
		+ tab + "for y in range(lmax_cols):" + lineBreak
		+ tab + tab + "if lvalues[y][x] != 0.0:" + lineBreak
		+ tab + tab + tab + "ax.text(x, y + .5, lvalues_text[y][x], fontsize = 16, ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=.1'))" + lineBreak
		+ "plt.savefig('Legend_Horizontal.png', bbox_inches='tight')" + lineBreak;

	// Begin vertical legend with box sizes
	pythonScript = pythonScript + "lvalues = [";

	for (int i = 0; i < legendItemCount; i++)
	{
		pythonScript = pythonScript + "[" + std::to_string(block);
		if (i + 1 != legendItemCount) { pythonScript = pythonScript + "],"; }
	}

	pythonScript = pythonScript + "]]" + lineBreak;

	// Add colour values
	pythonScript = pythonScript + "lvalues_colour =[";

	for (int i = 0; i < legendItemCount; i++)
	{
		pythonScript = pythonScript + "[" + std::to_string(selectedColourScheme[i]);
		if (i+1 != legendItemCount) { pythonScript = pythonScript + "],"; }
	}

	
	pythonScript = pythonScript + "]]" + lineBreak;

	// Add labels
	pythonScript = pythonScript + "lvalues_text = [";

	for (size_t i = 0; i < legendEntries.size(); i++)
	{
		pythonScript = pythonScript + "['" + legendEntries[i].keyWord;
		if (i+1 != legendItemCount) { pythonScript = pythonScript + "'],"; }
	}

	pythonScript = pythonScript + "']]" + lineBreak;

	// Add Patterns Data, if required
	if (legendColourScheme == "P")
	{
		pythonScript = pythonScript + "lvalues_pattern = [";

		for (size_t i = 0; i < legendEntries.size(); i++)
		{
			pythonScript = pythonScript + "['" + patternScheme[i];
			if (i + 1 < size_t(legendItemCount)) { pythonScript = pythonScript + "'],"; }
		}

		pythonScript = pythonScript + "']]" + lineBreak;
	}
	
	// Add standard python scripting
	pythonScript = pythonScript + "lmax_cols = len(lvalues)" + lineBreak
		+ "lmax_rows = len(lvalues[0])" + lineBreak
		+ "lvalues_sums = [sum([r[i] for r in lvalues]) for i in range(lmax_rows)]" + lineBreak
		+ "lvalues_norm = [[v/lvalues_sums[i] for i, v in enumerate(row)] for row in lvalues]" + lineBreak
		+ "fig, ax = plt.subplots(1, figsize=(4, 20))" + lineBreak
		+ "for row_num in range(lmax_cols):" + lineBreak;

	// Colourise legend
	if (legendColourScheme != "P")
	{
		pythonScript = pythonScript + tab + "ax.bar(range(lmax_rows), lvalues_norm[row_num], bottom = [sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('";

		// add colour spectrum type
		if (legendColourScheme == "F") { pythonScript = pythonScript + "Paired"; }
		else if (legendColourScheme == "C") { pythonScript = pythonScript + "Set1"; }
		else if (legendColourScheme == "G") { pythonScript = pythonScript + "Greys"; }
		else if (legendColourScheme == "P") { pythonScript = pythonScript + "Greys"; }

		// add general python scripting
		pythonScript = pythonScript + "')(i) for i in lvalues_colour[row_num]])" + lineBreak;

	}

	// Colourise legend with pattern, if required
	else if (legendColourScheme == "P")
	{
		pythonScript = pythonScript + tab + "bars = ax.bar(range(lmax_rows), lvalues_norm[row_num], bottom = [sum([lvalues_norm[i][j] for i in range(row_num)]) for j in range(lmax_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('";

		// add colour spectrum type
		if (legendColourScheme == "F") { pythonScript = pythonScript + "Paired"; }
		else if (legendColourScheme == "C") { pythonScript = pythonScript + "Set1"; }
		else if (legendColourScheme == "G") { pythonScript = pythonScript + "Greys"; }
		else if (legendColourScheme == "P") { pythonScript = pythonScript + "Greys"; }

		// add general python scripting
		pythonScript = pythonScript + "')(i) for i in lvalues_colour[row_num]])" + lineBreak
			+ tab + "for bar, pattern in zip(bars, lvalues_pattern[row_num]):" + lineBreak
			+ tab + tab + "bar.set_hatch(pattern)" + lineBreak;
	}

	// Complete legend code
		pythonScript = pythonScript + "ax.set_xlim(-0.5, lmax_rows-.5)" + lineBreak
		+ "ax.set_xticks([])" + lineBreak
		+ "ax.set_yticks([])" + lineBreak
		+ "ax.set_ylim(0, 1)" + lineBreak
		+ "for x in range(lmax_rows):" + lineBreak
		+ tab + "for y in range(lmax_cols):" + lineBreak
		+ tab + tab + "if lvalues[y][x] != 0.0:" + lineBreak
		+ tab + tab + tab + "ax.text(x, lvalues_norm[y][x] / 2 + sum([lvalues_norm[newy][x] for newy in range(y)]), lvalues_text[y][x], fontsize = 16, ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=.1'))" + lineBreak
		+ "plt.savefig('Legend_Vertical.png', bbox_inches='tight')";

	// open python file
	std::string filename = "legends.py";
	std::ofstream legendsFile(filename);
	legendsFile << pythonScript; // save data to file
	legendsFile.close();

}

std::string c_LegendCreation::colourSchemeChooser()
{
	// Ask for colour or pattern scheme
	do
	{
		std::cout << "\nWhich colour scheme would you like: \n"
			<< "\t (F)ull Colour \n"
			<< "\t (C)olourblind Friendly \n"
			<< "\t (G)rey Scale \n"
		    << "\t (P)atterns \n";
		std::cin >> legendColourScheme;
	} while (legendColourScheme != "F"
		&& legendColourScheme != "C"
		&& legendColourScheme != "G"
		&& legendColourScheme != "P");

	return legendColourScheme;

}

void c_LegendCreation::colourSchemeLoader(int legendItemCount)
{
	// If not set, ask for colour scheme
	if (legendColourScheme == "Q")
	{
		legendColourScheme = colourSchemeChooser();
	}

	// Set Colour Scheme
	if (legendColourScheme == "F")
	{
		for (size_t i = 0; i < 9; i++) { selectedColourScheme[i] = fullColour[i]; }
	}

	else if (legendColourScheme == "C")
	{
		for (size_t i = 0; i < 5; i++) { selectedColourScheme[i] = colourblind[i]; }
	}

	else if (legendColourScheme == "G")
	{
		selectedColourScheme[0] = 225/legendItemCount;
		for (int i = 2; i < legendItemCount + 1; i++) { selectedColourScheme[i-1] = 225/legendItemCount * i; }
	}

	else if (legendColourScheme == "P")
	{
		selectedColourScheme[0] = 150/legendItemCount;
		for (int i = 2; i < legendItemCount + 1; i++) { selectedColourScheme[i-1] = 150 / legendItemCount * i; }
	}
}

std::string c_LegendCreation::legendQuery(std::string inputDirectory)
{
	do
	{
		// Ask for number of legend items (maximum 9, except colour blind, maximum 6)
		if (legendColourScheme == "C")
		{
			do
			{
				std::cout << "How many legend items do you have (maximum 5)?" << std::endl;
				std::cin >> legendItemCount;
			} while (legendItemCount > 5 || legendItemCount < 0);
		}
		else
		{
			do
			{
				std::cout << "How many legend items do you have (maximum 9)?" << std::endl;
				std::cin >> legendItemCount;
			} while (legendItemCount > 9 || legendItemCount < 0);
		}
		legendEntries.clear();

		// Ask for item 1 (repeat through number) 
		for (int i = 0; i <= legendItemCount - 1; i++)
		{
			std::string tempVariable;
			legendEntries.push_back(blankEntry);
			if (i == 0) { std::cin.ignore(); }
			std::cout << "What is item #" << i + 1 << "? ";
			std::getline(std::cin,legendEntries[i].keyWord = tempVariable);
			std::cout << "What is the key character(s) used for this type in your data file (no spaces)? ";
			std::getline(std::cin, legendEntries[i].keyCharacter = tempVariable);
		}

		std::cout << std::endl;

		for (size_t i = 0; i < legendEntries.size(); i++)
		{
			// Display Legend 
			std::cout << i + 1 << ". " << legendEntries[i].keyWord << "\t\t(" << legendEntries[i].keyCharacter << ")" << std::endl;
		}

		// Confirm Legend
		std::cout << std::endl << "Is this correct (y/n) ? " << std::endl;
		std::cin >> responseString;

		// If yes, return
		if (responseString == "y")
		{
			colourSchemeLoader(legendItemCount);
			legendCreator(legendEntries, inputDirectory);
			legendLoaded = "Y";
		}

		// Otherwise, start over
	} while (responseString != "y");

	return legendColourScheme;
}

void c_LegendCreation::legendLoader(std::string inputDirectory, std::string legendFile)
{
	// Clear Vector from previous run
	legendEntries.clear();

	// Load file
	std::ifstream input(inputDirectory + legendFile);

	while (input)
	{

		// Separate by line
		std::string line;
		for (std::string line; std::getline(input, line, '\n');)
		{

			// Separate by field
			std::istringstream iline(line);
			while (iline)
			{
				std::string field;
				std::getline(iline, field, '\t');
				buffer.push_back(field);
			}

			legendEntries.push_back(blankEntry);
			size_t current = legendEntries.size() - 1;
			legendEntries[current].keyWord = buffer[0];
			legendEntries[current].keyCharacter = buffer[1];
			buffer.clear();
		}
		
		// Create Legend
		legendItemCount = legendEntries.size();
		colourSchemeLoader(legendItemCount);
		legendCreator(legendEntries, inputDirectory);
	}

	}