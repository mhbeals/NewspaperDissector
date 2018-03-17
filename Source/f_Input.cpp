#include "coreVariables.h"

std::vector <std::string> buffer;
std::vector <entry> edition;
entry emptyEntry;

void loadFile(std::string inputDirectory, std::string inputFile)
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
			edition[current].year = std::stoi(buffer[0]);
			edition[current].month = std::stoi(buffer[1]);
			edition[current].day = std::stoi(buffer[2]);
			edition[current].title = buffer[3];
			edition[current].page = std::stoi(buffer[4]);
			edition[current].column = std::stoi(buffer[5]);
			edition[current].snippet = std::stoi(buffer[6]);
			edition[current].type = buffer[7];
			edition[current].topic = buffer[8];
			edition[current].mentioned_location = buffer[9];
			edition[current].source = buffer[10];
			edition[current].source_type = buffer[11];
			edition[current].source_location = buffer[12];
			edition[current].text = buffer[13];
			buffer.clear();
		}
	}
}