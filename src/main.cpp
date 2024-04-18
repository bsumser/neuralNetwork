#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <chrono>    //tracking time of functions
#include <random> 	//random num gen for shuffle training data
#include "../include/Net.h"
#include "../include/Neuron.h"
#include "../include/trainData.h"

using namespace std;
using namespace std::chrono;

//https://towardsdatascience.com/convolutional-neural-networks-explained-9cc5188c4939

bool cont();
void digitGuess(vector<double> resultVals);

int main(int argc, char *argv[])
{
	int verbosity = 0;

	for (int i = 0; i < argc; i++)
	{
		//print out arguments
		cout << "argument " << i << " is " << argv[i] << endl;

		//string compare to -v flag and set/check verbosity level
		if (strcmp(argv[i], "-v") == 0) {verbosity = 1; cout << "verbosity set to 1" << endl;}
		else if (strcmp(argv[i], "-vv") == 0) {verbosity = 2; cout << "verbosity set to 2" << endl;}
		else if (strcmp(argv[i], "-vvv") == 0) {verbosity = 3; cout << "verbosity set to 3" << endl;}
	}
	
	//TODO: work on the training data class
	TrainData trainData(argv[1], verbosity);
	if (!cont()) { return 0; }

	trainData.normalizeData('m');
	if (verbosity == 3) { 
		trainData.printInputVals(); 
		trainData.printNormalVals(); 
		trainData.printTargetVals(); 
	}
	else if (verbosity == 1) { 
		trainData.printInputVals(0); 
		trainData.printNormalVals(0); 
		trainData.printTargetVals(0); 
	}

	//TODO:THIS NEEDS TO BE FIXED
	//int kernel = 4, stride = 1, padding = 0;
	//trainData.convolute(kernel, stride, padding);    //perform first convolution
	//trainData.batchNormalize();    //batch normalize the data
	//trainData.activationFuntion('r');    //rectified linear unit activation
	
	//TODO: finish pooling function
	//char type = 'd'; 
	//int poolSize = 4, poolStride = 1;
	//trainData.pool(type, poolSize, poolStride);    //pooling layer

	int userEpoch = 0;
	cout << "Please enter amount of epochs, 1 to infinity" << endl;
	cin >> userEpoch;
	
	//vector to dictate node and layer setup for network
	vector<unsigned> topology;

	topology.push_back(trainData.normalVals[0].size());	//Input layer
	topology.push_back(32);	// Hidden layer
	topology.push_back(10);	// Output layer
			
	//class constructor, topology is layers and neurons per layer
	Net myNet(topology);

	auto start = high_resolution_clock::now();
	for (int epoch = 0; epoch < userEpoch; ++epoch) {

		//shuffle data at each epoch
		// initialize random number generator engine
    	std::random_device rd;
    	std::mt19937 g(rd());

		// first argument is an iterator to the beginning of the vector (v[0])
    	// second argument is an iterator to the end of the vector (v[v.size()-1])
    	// third argument is the rng engine
		//https://stackoverflow.com/questions/60999419/how-do-i-shuffle-a-2d-array-in-c
		std::shuffle(trainData.normalVals.begin(), trainData.normalVals.end(), g);

		//TODO: These are using normalized vals instead of pool result
		//because pooling is not implemented yet
		for (int line = 0; line < trainData.normalVals.size() * .8; ++line) {

			//function to feed values fowards from one layer to the next
			myNet.feedForward(trainData.normalVals[line]);

			//function to back propagate learning
			myNet.backProp(trainData.targetVals[line]);

			//vector to hold result values
			vector<double> resultsVals;

			//function that reads outputs and feeds in back in
			myNet.getResults(resultsVals);

			cout << "Reulting Values are: ";
			for (size_t i = 0; i < resultsVals.size(); ++i){
				cout << resultsVals[i] << " ";
			}
			cout << endl;
			cout << "Target Values are: ";
			for (size_t i = 0; i < trainData.targetVals[line].size(); ++i){
				cout << trainData.targetVals[line][i] << " ";
			}
			cout << endl;
			digitGuess(resultsVals);

		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Main training loop finished in " << duration.count() / 1000000 << " s" << std::endl;

	return 0;
}

bool cont()
{	
	char choice = 'n';
	cout << "Do you wish to continue? (y/n)" << endl;
	cin >> choice;
	
	//testing change to ternary
	bool result = (choice == 'y') ? true : false;
	return result;
}

void digitGuess(vector<double> resultVals)
{
	double maxElement = std::max_element(resultVals.begin(), resultVals.end()) - resultVals.begin();
	std::cout << "Max element is " << maxElement << std::endl;
}