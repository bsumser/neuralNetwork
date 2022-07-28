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

	int userEpoch;	
	cout << "Please enter amount of epochs, 1 to infinity" << endl;
	cin >> userEpoch;
	
	//vector to dictate node and layer setup for network
	vector<unsigned> topology;

	//network topology of 13 input nodes, 6 nodes hidden layer and 3 node output layer
	topology.push_back(13);
	topology.push_back(6);
	topology.push_back(3);
			
	//class constructor, topology is layers and neurons per layer
	Net myNet(topology);
	
	for (int epoch = 0; epoch < userEpoch; ++epoch) {
		for (int line = 0; line < trainData.trainMax; ++line) {
			cout << "input values are: ";
			for (size_t i = 0; i < trainData.input.size(); ++i){
				cout  << setprecision(4) << trainData.input[i] << " ";
			}
			cout << endl;

			cout << "target values are: ";
			for (size_t i = 0; i < trainData.targetVals.size(); ++i){
				cout << trainData.targetVals[i] << " ";
			}
			cout << endl;

			cout << "Normalized data is: ";
			for (size_t i = 0; i < trainData.normalVals.size(); ++i) {
				cout << trainData.normalVals[i] << " ";
			}
			cout << endl;

			for (size_t i = 0; i < trainData.targetVals.size(); ++i){
				if (trainData.targetVals[i] == 1)
					cout << "Expected wine is wine number " << i + 1;
			}
			cout << endl;

		
			//function to feed values fowards from one layer to the next
			myNet.feedForward(trainData.normalVals);

			//function to back propagate learning
			myNet.backProp(trainData.targetVals);

			//vector to hold result values
			vector<double> resultsVals;

			//function that reads outputs and feeds in back in
			myNet.getResults(resultsVals);

			cout << "Reulting Values are: ";
			for (size_t i = 0; i < resultsVals.size(); ++i){
				cout << resultsVals[i] << " ";
			}
			cout << endl;

			//TODO 86 this global var
			float big = resultsVals[0];
			int bigIndex = 0;
			for (size_t i = 0; i < resultsVals.size(); ++i){
				if (resultsVals[i] > big) {
					big = resultsVals[i];
					bigIndex = i;
				}
			}
			cout << "Wine identified as wine " << bigIndex + 1 << endl;
		}
	}
	return 0;
}

	/*----------------------------------OLD CODE HERE-------------------------------------------------------/

	if (0 == 1) {
		//vector to dictate node and layer setup for network
		vector<unsigned> topology;

		//
		topology.push_back(13);
		topology.push_back(6);
		topology.push_back(3);

		//class constructor, topology is layers and neurons per layer
		Net myNet(topology);

		//vector to hold input values
		vector<double> inputVals;

		//vector for target values
		vector<double> targetVals;

		//array to calc mean and
		vector<double> normalVals;

		cout << "input values are: ";
		for (size_t i = 0; i < inputVals.size(); ++i){
			cout  << setprecision(4) << inputVals[i] << " ";
		}
		cout << endl;

		cout << "target values are: ";
		for (size_t i = 0; i < targetVals.size(); ++i){
			cout << targetVals[i] << " ";
		}
		cout << endl;

		cout << "Normalized data is: ";
		for (size_t i = 0; i < normalVals.size(); ++i) {
			cout << normalVals[i] << " ";
		}
		cout << endl;

		for (size_t i = 0; i < targetVals.size(); ++i){
			if (targetVals[i] == 1)
				cout << "Expected wine is wine number " << i + 1;
		}
		cout << endl;

		//function to feed values fowards from one layer to the next
		myNet.feedForward(normalVals);

		//function to back propagate learning
		myNet.backProp(targetVals);

		//vector to hold result values
		vector<double> resultsVals;

		//function that reads outputs and feeds in back in
		myNet.getResults(resultsVals);

		cout << "Reulting Values are: ";
		for (size_t i = 0; i < resultsVals.size(); ++i){
			cout << resultsVals[i] << " ";
		}
		cout << endl;

		//TODO 86 this global var
		float big = resultsVals[0];
		int bigIndex = 0;
		for (size_t i = 0; i < resultsVals.size(); ++i){
			if (resultsVals[i] > big) {
				big = resultsVals[i];
				bigIndex = i;
			}
		}
		cout << "Wine identified as wine " << bigIndex + 1 << endl;
	
	/*----------------------------------OLD CODE HERE-------------------------------------------------------*/
