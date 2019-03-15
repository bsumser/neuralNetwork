#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "Net.h"
#include "Neuron.h"

using namespace std;

//forward reference so that typedef will function

int main()
{
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

	//open data file
	ifstream data ("wine.data");

	char dummy;
	double x;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 14; ++j) {
			data >> x;
			if (j == 0) {
				if (x == 1)
					targetVals = {1, 0, 0};
				if (x == 2)
					targetVals = {0, 1, 0};
				if (x == 3)
					targetVals = {0, 0, 1};
			}
			else
				inputVals.push_back(x);

			if (j < (14 - 1))
				data >> dummy;
		}
		
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
		
		//function to feed values fowards from one layer to the next
		myNet.feedForward(inputVals);

		//function to back propagate learning
		myNet.backProp(targetVals);

		//vector to hold result values
		vector<double> resultsVals;
		
		//function that reads outputs and feeds in back in
		myNet.getResults(resultsVals);
		
		cout << "Reulting Values are: ";	
		for (size_t i = 0; i < resultsVals.size(); ++i){
			cout << resultsVals[i];
		}
		cout << endl;

		//need to add loop for training samples
		inputVals.clear();
	}
}
