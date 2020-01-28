#include "../include/trainData.h"
#include <iostream>
#include <fstream>

TrainData::TrainData(char *fileArg)
{
	std::cout << "setting the input file" << std::endl;
	std::ifstream inputFile;
	inputFile.open(fileArg);

	std::cout << "reading from the input file" << std::endl;
	char data[1000];
	inputFile >> data;

	std::cout << "writing some data to the screen" << std::endl;
	std::cout << data << std::endl;

	inputFile.close();
	//TODO get the number of data items in a line
	//TODO determine lines in the file
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

