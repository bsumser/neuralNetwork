#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

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

void TrainData::fillData()
{

}

void TrainData::printInputVals()
{
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_i = input.size();
	size_t vector_j = input[0].size();


	for (size_t i = 0; i < vector_i; i++) {
		for (size_t j = 0; j < vector_j; j++) {
			std::cout << input[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void TrainData::printNormalVals()
{
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_i = input.size();
	size_t vector_j = input[0].size();


	for (size_t i = 0; i < vector_i; i++) {
		for (size_t j = 0; j < vector_j; j++) {
			std::cout << normalVals[i][j] << " ";
		}
		std::cout << std::endl;
	}


}

void TrainData::printTargetVals()
{

}


// TODO: finish this normalization
void TrainData::normalizeData()
{
	std::cout << "starting data normalization" << std::endl;
	//Min-Max normalization https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network

	float upperBound = 1;
	float lowerBound = 0;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_i = input.size();
	size_t vector_j = input[0].size();
    
	//temp vector for normalized values in loop
	std::vector<float> tempLoop;

	for (size_t i = 0; i < vector_i; i++) {
		float tempVal = 0;
        tempLoop.push_back(input[i][0]);
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
	std::cout << "finished data normalization" << std::endl;
}