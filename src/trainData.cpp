#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std::chrono;

TrainData::TrainData(char *inputFileArg, int verbosityFlag)
{
	//set the verbosity for training data
	verbosity = verbosityFlag;
	std::cout << "TrainData verbosity set to " << verbosity << std::endl;

	fileArg = inputFileArg;

	std::string line, word, temp; //var for the csv line
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

		if (verbosity == 1) {std::cout << "line " << lineCount << " read was: " << line << std::endl;}

		std::stringstream s(line); //stringstream to break into words

		while (std::getline(s,word,',')) {
			//add all the column data of row to vector
			if (verbosity == 3) {std::cout << word << std::endl;}
            tempLoop.push_back(std::stod(word));
		}
        input.push_back(tempLoop);        //add temp vector to input member
        tempLoop.clear();        //clear temp vector
        lineCount++;        //increment line count for looping through file
		int switchCase = (int)tempLoop[0];
		switch(switchCase) {
			case 0: {
				std::vector<double> tempTargetVals = {1,0,0,0,0,0,0,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 1: {
				std::vector<double> tempTargetVals = {0,1,0,0,0,0,0,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 2: {
				std::vector<double> tempTargetVals = {0,0,1,0,0,0,0,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 3: {
				std::vector<double> tempTargetVals = {0,0,0,1,0,0,0,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 4: {
				std::vector<double> tempTargetVals = {0,0,0,0,1,0,0,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 5: {
				std::vector<double> tempTargetVals = {0,0,0,0,0,1,0,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 6: {
				std::vector<double> tempTargetVals = {0,0,0,0,0,0,1,0,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 7: {
				std::vector<double> tempTargetVals = {0,0,0,0,0,0,0,1,0,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 8: {
				std::vector<double> tempTargetVals = {0,0,0,0,0,0,0,0,1,0};
				targetVals.push_back(tempTargetVals);
				break;
			}

			case 9: {
				std::vector<double> tempTargetVals = {0,0,0,0,0,0,0,0,0,9};
				targetVals.push_back(tempTargetVals);
				break;
			}

			default: {
				std::cout << "case is default, couldnt read num" << std::endl;
				break;
			}
		}
	trainMax = floor(lineCount * 8);    //set the percentage of the training data to use
	}
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
	std::cout << "printing input values for row " << row << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	int size = input[0].size();

	for (int j = 0; j < size; j++) {
		std::cout << input[row][j] << " ";
	}
	std::cout << std::endl;
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
	std::cout << "printing normal values for row " << row << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_j = normalVals[0].size();

	for (size_t j = 0; j < vector_j; j++) {
		std::cout << normalVals[row][j] << " ";
	}
	std::cout << std::endl;
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
	std::cout << "printing target values for row " << row << std::endl;
	
	//size variable for vector lenggths to avoid comparison of int to different datatype
	size_t vector_j = targetVals[0].size();

	for (size_t j = 0; j < vector_j; j++) {
		std::cout << targetVals[row][j] << " ";
	}
	std::cout << std::endl;
}

// TODO: finish this normalization
void TrainData::normalizeData(const char normalType)
{
	auto start = high_resolution_clock::now();    //start the clock to track function execution time
	std::cout << "starting data normalization" << std::endl;

	//switch case for different types of data normalization
	switch (normalType) {
		case 'm': {
			std::cout << "min-max data normalization selected" << std::endl;
			//Min-Max normalization https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network

			double upperBound = 1;
			double lowerBound = 0;
	
			//size variable for vector lenggths to avoid comparison of int to different datatype
			size_t vector_i = input.size();
			size_t vector_j = input[0].size();
	
			std::vector<double> tempLoop;	//temp vector for normalized values in loop
			std::vector<double> tempTargetVals;	//temp vector for normalized values in loop

			for (size_t i = 0; i < vector_i; i++) {
				double tempVal = 0;
 		    	tempLoop.push_back(input[i][0]);	//push_back first value into vector to avoid it being normalized

				for (size_t j = 1; j < vector_j; j++) {
					double min = *std::min_element(input[i].begin(), input[i].end());
					double max = *std::max_element(input[i].begin(), input[i].end());
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

		case 's': {
			//TODO: implement this https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network
			std::cout << "standardization data normalization selected (has not been implemented)" << std::endl;
		}

		case 'b': {
			//TODO: implement this https://www.baeldung.com/cs/normalizing-inputs-artificial-neural-network
			//backprop algorithm will need to be changed
			std::cout << "batch data normalization selected (has not been implemented)" << std::endl;
		}

		default: {
			std::cout << "no data normalization selected" << std::endl;
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "finished data normalization in " << duration.count() << " us" << std::endl;
}

void TrainData::convolute(std::vector<std::vector<double>> kernel, int stride, int padding)    //perform first convolution
{
	auto start = high_resolution_clock::now();
	size_t kernelSize = kernel[0].size();
	size_t j = 0;    //declaring loop variables early for use outside loop scope
	size_t g = 0;    //declaring loop variables early for use outside loop scope
	size_t size = 5;
	std::vector<double> actMap;

	std::vector<int> testVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	size_t vectorLength = testVector.size();

	//TODO: finished convulution (running out of memory)
	std::vector<double> kernelRes;
	for (int i = 0; i < 10000/*input.size()*/; i++) {
		for (j = 0; j < input[i].size() + 1 - kernelSize; j++) {
			for (g = 0; g < input[i].size() + 1 - kernelSize; g++) {
				double temp =
					input[0][j * size + g] * kernel[0][0] +
					input[0][j * size + g + 1] * kernel[0][1] +
					input[0][j * size + g + 2] * kernel[0][2] +
					input[0][(j + 1) * size + g] * kernel[1][0] +
					input[0][(j + 1) * size + g + 1] * kernel[1][1] +
					input[0][(j + 1) * size + g + 2] * kernel[1][2] +
					input[0][(j + 2) * size + g] * kernel[2][0] +
					input[0][(j + 2) * size + g + 1] * kernel[2][1] +
					input[0][(j + 2) * size + g + 2] * kernel[2][2] ;
				actMap.push_back(temp);
				//debug prints for checking correct convolution
				/*std::cout << input[0][j * size + g] << "*" << kernel[0][0] << "+"
						  << input[0][j * size + g + 1] << "*" << kernel[0][1] << "+"
						  << input[0][j * size + g + 2] << "*" << kernel[0][2] << "+" << std::endl;
				std::cout << input[0][(j + 1) * size + g] << "*" << kernel[1][0] << "+"
						  << input[0][(j + 1) * size + g + 1] << "*" << kernel[1][1] << "+"
						  << input[0][(j + 1) * size + g + 2] << "*" << kernel[1][2] << "+" << std::endl;
				std::cout << input[0][(j + 2) * size + g] << "*" << kernel[2][0] << "+"
						  << input[0][(j + 2) * size + g + 1] << "*" << kernel[2][1] << "+"
						  << input[0][(j + 2) * size + g + 2] << "*" << kernel[2][2] << "+" << std::endl;
			std::cout << std::endl; */
			}
			//std::cout << std::endl;
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Convolution finished in " << duration.count() << " us" << std::endl;
}
void TrainData::batchNormalize()    //batch normalize the data
{
	auto start = high_resolution_clock::now();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Batch Normalization finished in " << duration.count() << " us" << std::endl;

}

void TrainData::activationFuntion(char type)    //rectified linear unit activation
{
	auto start = high_resolution_clock::now();

	switch(type) {
		case 's': {
			std::cout << "Sigmoid activation function selected" << std::endl;
		}
		case 't': {
			std::cout << "TanH activation function selected" << std::endl;
		}
		case 'r': {
			std::cout << "ReLU activation function selected" << std::endl;
		}
		default: {
			std::cout << "No activation function selected, defaulting" << std::endl;
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Function activation finished in " << duration.count() << " us" << std::endl;

}

void TrainData::pool(char type, int size, int stride)    //pooling layer
{
	auto start = high_resolution_clock::now();

	switch(type) {
		case 'a': {
			std::cout << "Average pooling selected" << std::endl;
		}
		case 'l': {
			std::cout << "L2 norm pooling selected" << std::endl;
		}
		case 'w': {
			std::cout << "Weighted average distance from center pixel pooling selected" << std::endl;
		}
		case 'm': {
			std::cout << "Max pooling selected" << std::endl;
		}
		default: {
			std::cout << "Default pooling selected" << std::endl;
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Pooling finished in " << duration.count() << " us" << std::endl;

}
