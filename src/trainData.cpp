#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

TrainData::TrainData(char *fileArg)
{
	std::string line, word, temp; //var for the csv line
	std::vector<double> input;
	std::cout << "setting the input file" << std::endl;
	std::ifstream inputFile;
	inputFile.open(fileArg);

	std::cout << "reading from the input file" << std::endl;
	char data[1000];
	inputFile >> data;

	std::cout << "writing some data to the screen" << std::endl;
	std::cout << data << std::endl;

	//TODO finished this file input
	//https://www.geeksforgeeks.org/csv-file-management-using-c/

	while(inputFile >> temp)  {
		getline(inputFile, line); //read row and store into string
		std::cout << line << std::endl;

		std::stringstream s(line); //stringstream to break into words

		while (getline(s,word,',')) {
			//add all the column data of row to vector
			std::cout << "entering second while loop" << std::endl;
			std::cout << stod(word) << std::endl;
		}
	}

	inputFile.close();
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