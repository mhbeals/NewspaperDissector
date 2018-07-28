// Newspaper Dissector
// M. H. Beals (2018) v.0.3.5 [Software]

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
std::string inputDirectory = "c:\\"; // Default working directory
std::string inputFile = "data.tsv"; // Default data file
std::string legendFile = "legend.tsv"; // Default legend file

// Congifuration Defaults
std::string responseValue = "S"; // Start, or no user responses given yet
std::string colourFlag = "S"; // Start, or not yet set

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
			<< "\t(c) Configure the Python Command" << std::endl
			<< "\t(d) Create a Visualisation" << std::endl
			<< "\t(e) Exit the Programme" << std::endl
			<< "\nWhich would you like to do? ";
		std::cin >> responseValue;

		// If they ask to configure the files
		if (responseValue == "a")
		{
			std::cout << "\nWould you like to configure your:" << std::endl
				<< "\t(f) Main Data File, currently set to " << inputFile;
			if (inputInstance.dataFlag == "T") { std::cout << ", a text-based data file" << std::endl; }
			else if (inputInstance.dataFlag == "N") { std::cout << ", a data file with numeric size data" << std::endl; }
			std::cout << "\t(g) Legend Data File, currently set to " << legendFile << std::endl
				<< "\t(h) Return to the main menu" << std::endl
				<< "\n\nWhich would you like to do? ";
			std::cin >> responseValue;

			// If they ask to configure the data file
			if (responseValue == "f")
			{
				// Collect input filename each time
				std::cout << "\nWhat is the name of your input file? ";
				std::cin >> inputFile;

				// Set the data file type
				do
				{
					std::cout << "\nDoes this file include (T)ext or a (N)umeric value, such as line count, to determine snippet size? ";
					std::cin >> inputInstance.dataFlag;
				} while (inputInstance.dataFlag != "T" && inputInstance.dataFlag != "N");

				// Encourage user to configure the legend
				std::cout << "\nwould you like to set the Legend file? (y/n)";
				std::cin >> responseValue;

			}

			// If they ask to configure the legend
			if (responseValue == "g" || responseValue == "y")
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

		// If they ask to configure the python command.
		else if (responseValue == "c")
		{
			std::cout << "\nThe programme is currently set to execute the python script using the command " << vectorInstance.pythonFlag << std::endl << "Would you like to change the command (y/n)? ";
			std::cin >> responseValue;

			if (responseValue == "y")
			{
				std::cout << "What should the command be? For example 'python3': " << std::endl;
				std::cin >> vectorInstance.pythonFlag;
			}
		}

		// If they ask to run the visualiser
		else if (responseValue == "d") {
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

		// If they ask to exit the programme
		else if (responseValue == "e") { return 0; }

		// If they ask to do something that isn't an option
		else { std::cout << std::endl << "I can't do that, Dave." << std::endl << std::endl; }

	} while (responseValue != "a"
		|| responseValue != "b"
		|| responseValue != "c"
		|| responseValue != "d"
		);
}