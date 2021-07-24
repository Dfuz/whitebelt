#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

struct Student
{
	std::string fName, sName;
	uint day, mounth, year;
};

int main (int argc, char** argv)
{
	int linesCount;	
	std::cin >> linesCount;

	std::vector<Student> students(linesCount);
	for (auto& student : students)
	{
		std::cin >> student.fName >> student.sName 
				>> student.day >> student.mounth >> student.year;		
	}

	std::cin >> linesCount;
	for (size_t i = 0; i < linesCount; i++)
	{
		std::string command;
		std::cin >> command;
		int parameter;
		std::cin >> parameter;
		if (command != "name" and command != "date")
			std::cout << "bad request" << std::endl;
		else
		{
			try
			{
				if (command == "name")
				{
					const auto &student = students.at(--parameter);
					std::cout << student.fName << ' ' << student.sName << std::endl;
				}
				else 
				{
					const auto &student = students.at(--parameter);
					std::cout << student.day << '.' << student.mounth << '.' << student.year << std::endl;
				}
				
			}
			catch (const std::out_of_range& oor)
			{
				std::cout << "bad request" << std::endl;
			}
		}
	}
	return 0;
}