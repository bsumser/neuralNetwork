#include "../include/trainData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>    //tracking time of functions
#include <random> 	//random num gen for shuffle training data
#include <numeric>    //std::accumulate

using namespace std::chrono;

TrainData::TrainData(char *inputFileArg, int verbosityFlag)
{
	//takes a file path for the training data, and verbosity level

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

		if (verbosity == 3) {std::cout << "line " << lineCount << " read was: " << line << std::endl;}

		std::stringstream s(line); //stringstream to break into words

		while (std::getline(s,word,',')) {
			//add all the column data of row to vector
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

	std::cout << "First row of input values:" << std::endl;
	printInputVals(0);
	
	std::cout << "TargetVals for this row are:" << std::endl;
	printTargetVals(0);
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

void TrainData::dataShuffle()
{
	//shuffle data at each epoch
	// initialize random number generator engine
    std::random_device rd;
    std::mt19937 g(rd());

	// first argument is an iterator to the beginning of the vector (v[0])
  	// second argument is an iterator to the end of the vector (v[v.size()-1])
  	// third argument is the rng engine
	//https://stackoverflow.com/questions/60999419/how-do-i-shuffle-a-2d-array-in-c
	std::shuffle(normalVals.begin(), normalVals.end(), g);
	int trainDataSize = normalVals.size() * .8;
	int testDataSize = normalVals.size() - trainDataSize;

	auto it = std::next(normalVals.begin(), trainDataSize);

	std::move(normalVals.begin(), it, std::back_inserter(trainData));
}

void TrainData::convolute(std::vector<std::vector<double>> kernel, int stride, int padding)    //perform first convolution
{
	auto start = high_resolution_clock::now();
	std::cout << "Convolution input vector of " << input.size() << "x" << input[0].size() << " vector" << std::endl;
	size_t kernelSize = kernel[0].size();
	size_t j = 0;    //declaring loop variables early for use outside loop scope
	size_t g = 0;    //declaring loop variables early for use outside loop scope
	size_t size = 5;


	std::vector<int> testVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	size_t vectorLength = testVector.size();

	//TODO: finished convulution (running out of memory)
	std::vector<double> kernelRes;
	for (int i = 0; i < input.size(); i++) {
		std::vector<double> tempVector;
		for (j = 0; j < 28 + 1 - kernelSize; j++) {
			for (g = 0; g < 28 + 1 - kernelSize; g++) {
				double temp =
					input[i][j * size + g] * kernel[0][0] +
					input[i][j * size + g + 1] * kernel[0][1] +
					input[i][j * size + g + 2] * kernel[0][2] +
					input[i][(j + 1) * size + g] * kernel[1][0] +
					input[i][(j + 1) * size + g + 1] * kernel[1][1] +
					input[i][(j + 1) * size + g + 2] * kernel[1][2] +
					input[i][(j + 2) * size + g] * kernel[2][0] +
					input[i][(j + 2) * size + g + 1] * kernel[2][1] +
					input[i][(j + 2) * size + g + 2] * kernel[2][2] ;
				tempVector.push_back(temp);
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
		}
		convoResult.push_back(tempVector);
		tempVector.clear();
		tempVector.shrink_to_fit();
	}

	////deallocate input vector because we are done with it
	//input.clear();
	//input.shrink_to_fit();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Convolution finished in " << duration.count() << " us" << std::endl;
	std::cout << "Convolution result vector of " << convoResult.size() << "x" << convoResult[0].size() << " vector" << std::endl;
}

void TrainData::batchNormalize()    //batch normalize the data
{
	//function to normalize data output from convolution
	auto start = high_resolution_clock::now();
	std::cout << "Batch Normalization convolved of data start" << std::endl;

	for (size_t i = 0; i < convoResult.size(); i++) {
		std::vector<double> tempVector;    //temp vector for loop
		double max = *max_element(convoResult[i].begin(), convoResult[i].end());
		double min = *min_element(convoResult[i].begin(), convoResult[i].end());
		double denom = max - min;
		double average = accumulate(convoResult[i].begin(), convoResult[i].end(), 0.0)/convoResult[i].size();
		for (size_t j = 0; j < convoResult[i].size(); j++) {
			double temp = (convoResult[i][j] - average) / (denom);
			tempVector.push_back(temp);
		}
		std::cout << "size " << tempVector.size() << std::endl;
		batchResult.push_back(tempVector);
	}

	//deallocate convolutional result because we are done with it
	convoResult.clear();
	convoResult.shrink_to_fit();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Batch Normalization of Convolved Data finished in " << duration.count() << " us" << std::endl;
	std::cout << "Batch Normalization result vector of " << batchResult.size() << "x" << batchResult[0].size() << " vector" << std::endl;

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
			for (size_t i = 0; i < batchResult.size(); i++) {
				std::vector<double> tempVector;
				for (size_t j = 1; j < batchResult[i].size(); j++) {
					if (batchResult[i][j] > 0) tempVector.push_back(batchResult[i][j]);
					else tempVector.push_back(0);
				}
				actResult.push_back(tempVector);
			}
		}
		default: {
			std::cout << "No activation function selected, defaulting" << std::endl;
		}
	}

	//deallocate batch normalization result because we are done with it
	batchResult.clear();
	batchResult.shrink_to_fit();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Function activation finished in " << duration.count() << " us" << std::endl;
	std::cout << "Activation function result vector of " << actResult.size() << "x" << actResult[0].size() << " vector" << std::endl;
}

void TrainData::pool(char type, int size, int stride)    //pooling layer
{
	auto start = high_resolution_clock::now();

	size_t actSize = sqrt(actResult.size());

	//testing variables
	std::vector<double> testVector = {1,1,2,4,5,6,7,8,3,2,1,0,1,2,3,4};
	int vecDimen = 4;

	switch(type) {
		case 'd': {
			std::cout << "Default pooling selected (no pooling)" << std::endl;
		}
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
			for (size_t i = 0; i < actResult.size(); i++) {
				std::vector<double> tempVector;
				for (size_t j = 0; j < actSize; j+=stride) {
					for (size_t g = 0; g < actSize; g+=stride) {
						//debug print statements
						//std::cout << actResult[i][j * actSize + g] << "*" << testVector[j * actSize + g + 1] << std::endl;
						//std::cout << actResult[i][(j + 1) * actSize + g] << "*" << testVector[(j + 1) * actSize + g + 1] << std::endl;
						double maxPoolVal = std::max(std::max(actResult[i][j * actSize + g], testVector[j * actSize + g + 1]),
													 std::max(actResult[i][(j + 1) * actSize + g], testVector[(j + 1) * actSize + g + 1]));
						//std::cout << "max is " << maxPoolVal << std::endl;
						//std::cout << std::endl;
						tempVector.push_back(maxPoolVal);
					}
				poolResult.push_back(tempVector);
				}
			}
		}
		default: {
			std::cout << "couldnt read pooling type" << std::endl;
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Pooling finished in " << duration.count() << " us" << std::endl;
	std::cout << "Pool result vector of " << poolResult.size() << "x" << poolResult[0].size() << " vector" << std::endl;
}

void TrainData::printInputVals()
{
	std::cout << "printing input values" << std::endl;
	
	//size variable for vector lengths to avoid comparison of int to different datatype
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
	//size variable for vector lengths to avoid comparison of int to different datatype
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