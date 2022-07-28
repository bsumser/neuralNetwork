#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <math.h>

TrainData::TrainData(char *inputFileArg, int verbosityFlag)
{
	//set the verbosity for training data
	verbosity = verbosityFlag;
	std::cout << "TrainData verbosity set to " << verbosity << std::endl;

	fileArg = inputFileArg;

	std::string line, word, temp; //var for the csv line
    std::vector<float> tempLoop;
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

		if (verbosity == 1) {std::cout << "line " << lineCount << " read was: " << line << std::endl;}

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
	//set amount of training data to be used
	trainMax = floor(lineCount * 8);
}

void TrainData::printInputVals()
{
	std::cout << "printing input values" << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_i = input.size();
	size_t vector_j = input[0].size();

	for (size_t i = 0; i < vector_i; i++) {
		for (size_t j = 0; j < vector_j; j++) {
			std::cout << input[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "finished printing input values" << std::endl;
}

void TrainData::printInputVals(int row)
{
	std::cout << "printing input values" << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_j = input[0].size();

	for (size_t j = 0; j < vector_j; j++) {
		std::cout << input[row][j] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "finished printing input values" << std::endl;
}

void TrainData::printNormalVals()
{
	std::cout << "printing normalized values" << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_i = input.size();
	size_t vector_j = input[0].size();

	for (size_t i = 0; i < vector_i; i++) {
		for (size_t j = 0; j < vector_j; j++) {
			std::cout << normalVals[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "finished printing normalized values" << std::endl;
}

void TrainData::printNormalVals(int row)
{
	std::cout << "printing normal values" << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_j = normalVals[0].size();

	for (size_t j = 0; j < vector_j; j++) {
		std::cout << normalVals[row][j] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "finished printing normal values" << std::endl;
}


void TrainData::printTargetVals()
{
	std::cout << "printing target values" << std::endl;
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_i = targetVals.size();

	for (size_t i = 0; i < vector_i; i++) {
		std::cout << "row " << i << " = " << targetVals[i][0] << " " << targetVals[i][1] << " " << targetVals[i][2] << std::endl;
	}
	std::cout << "finished printing target values" << std::endl;
}

void TrainData::printTargetVals(int row)
{
	std::cout << "printing target values" << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_j = targetVals[0].size();

	for (size_t j = 0; j < vector_j; j++) {
		std::cout << targetVals[row][j] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "finished printing target values" << std::endl;
}


// TODO: finish this normalization
void TrainData::normalizeData(const char normalType)
{
	std::cout << "starting data normalization" << std::endl;

	//switch case for different types of data normalization
	switch (normalType) {
		case 'm':
		{
			std::cout << "min-max data normalization selected" << std::endl;
			//Min-Max normalization https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network

			float upperBound = 1;
			float lowerBound = 0;
	
			//size variable for vector lenggths to avoid comparison of int to different datatype
			size_t vector_i = input.size();
			size_t vector_j = input[0].size();
	
			std::vector<float> tempLoop;	//temp vector for normalized values in loop
			std::vector<float> tempTargetVals;	//temp vector for normalized values in loop

			for (size_t i = 0; i < vector_i; i++) {
				float tempVal = 0;
 		    	tempLoop.push_back(input[i][0]);	//push_back first value into vector to avoid it being normalized

				if (input[i][0] == 1) {tempTargetVals = {1, 0, 0,};}	//setup targetValues for output layer
				else if (input[i][0] == 2) {tempTargetVals = {0, 1, 0,};}
				else if (input[i][0] == 3) {tempTargetVals = {0, 0, 1,};}

				targetVals.push_back(tempTargetVals);	//add temp vector of target values to full target values vector
				
				for (size_t j = 1; j < vector_j; j++) {
					float min = *std::min_element(input[i].begin(), input[i].end());
					float max = *std::max_element(input[i].begin(), input[i].end());
					tempVal = (((input[i][j] - min) / (max-min)) * ((upperBound - lowerBound) + lowerBound));
 		           tempLoop.push_back(tempVal);

					if (verbosity == 3) 
					{ 
						std::cout << tempVal << "=" << input[i][j] << "-" << min << "/" << max << "-" << min 
						<< "*" << upperBound << "-" << lowerBound << "+" << lowerBound << std::endl;
					}
				}
 		       normalVals.push_back(tempLoop);
 		       tempLoop.clear();
			}
		}
		case 's':
			//TODO: implement this https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network
			std::cout << "standardization data normalization selected (has not been implemented)" << std::endl;

		case 'b':
			//TODO: implement this https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network
			//backprop algorithm will need to be changed
			std::cout << "batch data normalization selected (has not been implemented)" << std::endl;
	}
	std::cout << "finished data normalization" << std::endl;
}