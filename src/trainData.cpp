#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

TrainData::TrainData(char *fileArg, int verbosityFlag)
{
	//set the verbosity for training data
	verbosity = verbosityFlag;
	std::cout << "TrainData verbosity set to " << verbosity << std::endl;


	std::string line, word, temp; //var for the csv line
	input;
    std::vector<double> tempLoop;
	int lineCount = 1; //counter for lines in csv file
	std::cout << "setting the input file" << std::endl;
	std::ifstream data(fileArg);

	std::cout << "reading from the input file as " << fileArg << std::endl;
	
	//read data from the file as a string vector
	std::vector<std::string> row;

	//check that file is open/readable
	if (std::getline(data,temp)) {std::cout << "file opened success " << std::endl << temp << std::endl;}
	else {std::cout << "failed to read file" << std::endl;}

	while(std::getline(data,line))  {
		row.clear();

		std::getline(data, line); //read row and store into string

		if (verbosity == 3) {std::cout << "line " << lineCount << " read was: " << line << std::endl;}

		std::stringstream s(line); //stringstream to break into words

		while (std::getline(s,word,',')) {
			//add all the column data of row to vector
			if (verbosity == 3) {std::cout << word << std::endl;}
            tempLoop.push_back(std::stod(word));
		}
        input.push_back(tempLoop);
        tempLoop.clear();
        lineCount++;
	}
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
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[0].size(); j++) {
			std::cout << input[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void TrainData::printNormalVals()
{

}

void TrainData::printTargetVals()
{

}


// TODO: finish this normalization
void TrainData::normalizeData()
{
	std::cout << "starting data normalization" << std::endl;
	//Min-Max normalization https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network

	double upperBound = 1;
	double lowerBound = 0;

	for (int i = 0; i < input.size(); i++) {
		double tempVal = 0;
		for (int j = 1; j < input[0].size(); j++) {
			double min = *std::min_element(input[i].begin(), input[i].end());
			double max = *std::max_element(input[i].begin(), input[i].end());
			tempVal = (((input[i][j] - min) / (max-min)) * ((upperBound - lowerBound) + lowerBound));
			input[i][j] = tempVal;

			if (verbosity == 3) 
			{ 
				std::cout << tempVal << "=" << input[i][j] << "-" << min << "/" << max << "-" << min 
				<< "*" << upperBound << "-" << lowerBound << "+" << lowerBound << std::endl;
			}
		}
	}
	std::cout << "finished data normalization" << std::endl;
}