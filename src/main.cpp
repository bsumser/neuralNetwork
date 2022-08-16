#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include "../include/Net.h"
#include "../include/Neuron.h"
#include "../include/trainData.h"

using namespace std;

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
	trainData.normalizeData('m');
	if (verbosity == 3) { trainData.printInputVals(); }
	if (verbosity == 3) { trainData.printNormalVals(); }
	if (verbosity == 3) { trainData.printTargetVals(); }

	trainData.convolute();    //perform first convolution
	trainData.batchNormalize();    //batch normalize the data
	trainData.activationFuntion();    //rectified linear unit activation
	trainData.pool();    //pooling layer

	int userEpoch;	
	cout << "Please enter amount of epochs, 1 to infinity" << endl;
	cin >> userEpoch;
	
	//vector to dictate node and layer setup for network
	vector<unsigned> topology;

	//network topology of 13 input nodes, 6 nodes hidden layer and 10 node output layer
	topology.push_back(trainData.input[0].size());
	topology.push_back(6);
	topology.push_back(10);
			
	//class constructor, topology is layers and neurons per layer
	Net myNet(topology);
	
	for (int epoch = 0; epoch < userEpoch; ++epoch) {
		for (int line = 0; line < trainData.trainMax; ++line) {
			trainData.printInputVals(line);    //print the input values

			trainData.printTargetVals(line);   //print the target values expected

			trainData.printNormalVals(line);   //print the normalized data values

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
	return 0;
}
