#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TrainData::TrainData(char *fileArg)
{
	std::string line, word, temp; //var for the csv line
	std::vector<std::vector<double>> input;
    std::vector<double> tempLoop;
	int lineCount = 1; //counter for lines in csv file
	std::cout << "setting the input file" << std::endl;
	std::ifstream data(fileArg);

	std::cout << "reading from the input file as " << fileArg << std::endl;
	
	//read data from the file as a string vector
	std::vector<std::string> row;

	//TODO finished this file input
	//https://www.geeksforgeeks.org/csv-file-management-using-c/

	//check that file is open/readable
	if (std::getline(data,temp)) {std::cout << "file opened success " << std::endl << temp << std::endl;}
	else {std::cout << "failed to read file" << std::endl;}

	while(std::getline(data,line))  {
		//row.clear();

		//std::getline(data, line); //read row and store into string

		std::cout << "line " << lineCount << " read was: " << line << std::endl;

		std::stringstream s(line); //stringstream to break into words

		while (std::getline(s,word,',')) {
			//add all the column data of row to vector
			std::cout << word << std::endl;
            tempLoop.push_back(std::stod(word));
		}
        input.push_back(tempLoop);
        tempLoop.clear();
        lineCount++;
	}
	//data.close();
}
void TrainData::getRow()
{

}

void TrainData::setRow(int r)
{

}

void TrainData::getCol()
{

}

void TrainData::setCol(int c)
{

}

void TrainData::fillData()
{

}

void TrainData::printInputVals()
{

}

void TrainData::printNormalVals()
{

}

void TrainData::printTargetVals()
{

}

void TrainData::normalizeData()
{

}