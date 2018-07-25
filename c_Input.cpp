#include "coreVariables.h"
#include "c_Input.h"


//    _____        _          _____                   _   
//   |  __ \      | |        |_   _|                 | |  
//   | |  | | __ _| |_ __ _    | |  _ __  _ __  _   _| |_ 
//   | |  | |/ _` | __/ _` |   | | | '_ \| '_ \| | | | __|
//   | |__| | (_| | || (_| |  _| |_| | | | |_) | |_| | |_ 
//   |_____/ \__,_|\__\__,_| |_____|_| |_| .__/ \__,_|\__|
//                                       | |              
//                                       |_|              

void c_Input::loadFile(std::string inputDirectory, std::string inputFile)
{
	// Clear Vector from previous run
	edition.clear();

	// Load file
	std::ifstream input(inputDirectory + inputFile);

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

			edition.push_back(emptyEntry);
			size_t current = edition.size() - 1;
			edition[current].documentID = buffer[0];
			edition[current].page = std::stoi(buffer[1]);
			edition[current].column = std::stoi(buffer[2]);
			edition[current].snippet = std::stoi(buffer[3]);
			edition[current].type = buffer[4];
			edition[current].key_value = buffer[5];
			if (dataFlag == "T")
			{
				edition[current].text = buffer[6];
			}
			
			else if (dataFlag == "N")
			{
				edition[current].wordcount = std::stof(buffer[6]);
			}
			buffer.clear();
		}
	}
}