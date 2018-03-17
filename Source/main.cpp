// Newspaper Dissector
// M. H. Beals (2018) v.0.2.0 [Software]

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

#include "stdafx.h"
#include "c_Output.h"

int main()
{
	// Prevent Excess Clean-up Operations
	std::string responseValue = "s";
	
	// Collect directory information once
	std::string inputDirectory = "c:\\";
	std::cout << "The default directory is " + inputDirectory + "\n";
	std::cout << "Which directory contains your input files? ";
	std::cin >> inputDirectory;

	// Main Loop
	while (responseValue != "n")
	{
		if (responseValue != "s")
		{
			// Clean up files from previous runs
			system("del createGraphics.bat");
		}

		// Collect input filename each time
		std::string inputFile = "";
		std::cout << "What is your input file name? ";
		std::cin >> inputFile;

		// Load file
		loadFile(inputDirectory, inputFile);
		
		// Transform data into pivot table
		c_Output vectorInstance;
		vectorInstance.transformVector();
		
		// Create graphic instructions for both types and colour schemes
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
				vectorInstance.graphicMaker(i, j);
		}
		
		// Run Python visualiser and clean up temporary files
		system("createGraphics.bat");
		
		// Query to continue
		std::cout << "\n\nWould you like to do another file (y/n)? ";
		std::cin >> responseValue;
	}

	// Clean up files before closing
	system("del createGraphics.bat");
	return 0;
}

