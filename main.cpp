// Newspaper Dissector
// M. H. Beals (2018) v.0.3.2 [Software]

// MIT License
// Copyright(c) 2018 M. H. Beals
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

#include "c_LegendCreation.h"
#include "c_Input.h"
#include "c_Transformation.h"
#include "c_Output.h"

// Shared User Variables
std::string inputDirectory = "c:\\";
std::string inputFile = "data.tsv";
std::string legendFile = "legend.tsv";
std::string responseValue = "S";
std::string colourFlag = "S";

// Create a Containers
c_LegendCreation legendInstance;
c_Input inputInstance;
c_Transformation transformationInstance;
c_Output vectorInstance;

int main()
{

	// Collect directory information once
	std::cout << "The default working directory is " + inputDirectory + "\n";
	std::cout << "Which directory contains your input files? ";
	std::cin >> inputDirectory;

	// Ask what the user would like to do
	do
	{
		if (responseValue == "S")
		{
			std::cout << "\nWelcome to The Newspaper Dissector." << std::endl;
		}

		std::cout << "\nYou can:" << std::endl
			<< "\t(a) Configure Data Files" << std::endl
			<< "\t(b) Configure Visualisation" << std::endl
			<< "\t(c) Create a Visualisation" << std::endl
			<< "\t(d) Exit the Programme" << std::endl
			<< "\nWhich would you like to do? ";
		std::cin >> responseValue;

		// If they ask to configure the files
		if (responseValue == "a")
		{
			std::cout << "\nWould you like to configure your:" << std::endl
				<< "\t(e) Main Data File, currently set to " << inputFile << std::endl
				<< "\t(f) Legend Data File, currently set to " << legendFile << std::endl
				<< "\t(g) Return to the main menu" << std::endl
				<< "\n\nWhich would you like to do? ";
			std::cin >> responseValue;

			// If they ask to configure the data file
			if (responseValue == "e")
			{
				// Collect input filename each time
				std::cout << "\nWhat is the name of your input file? ";
				std::cin >> inputFile;
				std::cout << "\nwould you like to set the Legend file? (y/n)";
				std::cin >> responseValue;

			}

			// If they ask to configure the legend
			if (responseValue == "f" || responseValue == "y")
			{
				std::cout << "\nWould you like to (l)oad or (m)anually create your legends? ";
				std::cin >> responseValue;

				// Create Legend Manually
				if (responseValue == "m")
				{
					colourFlag = legendInstance.legendQuery(inputDirectory);
				}

				// Load Legend File
				else if (responseValue == "l")
				{
					std::cout << "\nWhat is the name of your legend file? ";
					std::cin >> legendFile;
				}
			}

			std::cout << "\nYour files have been configured as follows:" << std::endl
				<< "\tThe Main Data File is currently set to " << inputFile << std::endl
				<< "\tThe Legend Data File is currently set to " << legendFile << std::endl;
		}

		// If the ask to configure the visualisation
		else if (responseValue == "b")
		{
			colourFlag = legendInstance.colourSchemeChooser();
		}

		// If they ask to run the visualiser
		else if (responseValue == "c") {
			{
					// Set legend colourscheme
					if (colourFlag == "S") 
					{ 
						colourFlag = legendInstance.colourSchemeChooser();
					}
					
					// Load data file into data container
					inputInstance.loadFile(inputDirectory, inputFile);

					// Load legend data
					if (legendInstance.legendLoaded == "S")
					{
						legendInstance.legendLoader(inputDirectory, legendFile);
					}


					// Clear old Data Containers
					transformationInstance.currentCopy = {};

					// Transform data into pivot table
					transformationInstance.transformVector();

					// Create graphic instructions
					vectorInstance.graphicMaker(colourFlag);

					// Run Python visualiser
					// NB This only works on Windows
					system("createGraphics.bat");

					// Clean up batch file 
					system("del createGraphics.bat");

			}
		}

		else if (responseValue == "d") { return 0; }

		else { std::cout << std::endl << "I can't do that, Dave." << std::endl << std::endl; }

	} while (responseValue != "a"
		|| responseValue != "b"
		|| responseValue != "c"
		|| responseValue != "d"
		);

	return 0;
}