#include <iostream>
#include <fstream>
#include <iomanip>

int main (int argc, char** argv)
{
	std::ifstream inputFile("input.txt");
	int linesCount = 0, columnCount = 0;

	// read first line of .csv file
	if (!(inputFile >> linesCount))
		return 1;
	if (!(inputFile >> columnCount))
		return 1;
	
	// read data into console table
	for (int i = 0; i < linesCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			int value = 0; inputFile >> value;
			inputFile.ignore(1);
			std::cout << std::setw(10) << value;
			if (j != columnCount - 1)
				std::cout << ' ';
			else std::cout << std::endl;
		}
	}
	return 0;
}