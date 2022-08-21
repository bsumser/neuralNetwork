#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <chrono>    //tracking time of functions
#include "../include/Net.h"
#include "../include/Neuron.h"
#include "../include/trainData.h"

using namespace std;
using namespace std::chrono;

//https://towardsdatascience.com/convolutional-neural-networks-explained-9cc5188c4939

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
	//trainData.normalizeData('m');
	if (verbosity == 3) { trainData.printInputVals(); }
	if (verbosity == 3) { trainData.printNormalVals(); }
	if (verbosity == 3) { trainData.printTargetVals(); }
	trainData.printInputVals(0);    //print the input values

	std::vector<std::vector<double>> kernel{{1,1,1},{1,1,1},{1,1,1}};
	int stride = 1;
	int padding = 0;
	char act = 'r';
	char type = 'm';
	int poolSize = 2;
	int poolStride = 2;

	trainData.convolute(kernel, stride, padding);    //perform first convolution
	trainData.batchNormalize();    //batch normalize the data
	trainData.activationFuntion(act);    //rectified linear unit activation
	trainData.pool(type, poolSize, poolStride);    //pooling layer

	int userEpoch;
	cout << "Please enter amount of epochs, 1 to infinity" << endl;
	cin >> userEpoch;
	
	//vector to dictate node and layer setup for network
	vector<unsigned> topology;

	//network topology of input nodes for all layers
	topology.push_back(trainData.poolResult[0].size());
	topology.push_back(20);
	topology.push_back(10);
			
	//class constructor, topology is layers and neurons per layer
	Net myNet(topology);

	auto start = high_resolution_clock::now();
	for (int epoch = 0; epoch < userEpoch; ++epoch) {
		for (int line = 0; line < trainData.poolResult.size() * .8; ++line) {
			//TODO:fix these print functions to grab data from poolResult
			//trainData.printInputVals(line);    //print the input values

			//trainData.printTargetVals(line);   //print the target values expected

			//trainData.printNormalVals(line);   //print the normalized data values

			//function to feed values fowards from one layer to the next
			myNet.feedForward(trainData.poolResult[line]);

			//function to back propagate learning
			myNet.backProp(trainData.targetVals[line]);

			//vector to hold result values
			vector<double> resultsVals;

			//function that reads outputs and feeds in back in
			myNet.getResults(resultsVals);

			//cout << "Reulting Values are: ";
			//for (size_t i = 0; i < resultsVals.size(); ++i){
			//	cout << resultsVals[i] << " ";
			//}
			//cout << endl;

			//TODO change this from old wine project to new digit recognition
			//float big = resultsVals[0];
			//int bigIndex = 0;
			//for (size_t i = 0; i < resultsVals.size(); ++i){
			//	if (resultsVals[i] > big) {
			//		big = resultsVals[i];
			//		bigIndex = i;
			//	}
			//}
			//cout << "Wine identified as wine " << bigIndex + 1 << endl;
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Main training loop finished in " << duration.count() << " us" << std::endl;

	int userLine;

	do {
		cout << "Please enter a line number between 8500 and 10000" << endl;
		cin >> userLine;

		//function to feed values fowards from one layer to the next
		myNet.feedForward(trainData.poolResult[userLine]);

		//function to back propagate learning
		myNet.backProp(trainData.targetVals[userLine]);

		//vector to hold result values
		vector<double> resultsVals;

		//function that reads outputs and feeds in back in
		myNet.getResults(resultsVals);

		cout << "Reulting Values are: ";
		for (size_t i = 0; i < resultsVals.size(); ++i){
			cout << resultsVals[i] << " ";
		}
		cout << endl;

	} while (userLine != -1);
	return 0;
}
