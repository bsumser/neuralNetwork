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

	//open csv file
	//TODO FIX THIS READING INPUT FROM FILE
	ifstream data ("wine.data");

	char dummy;
	double x;
	for (int i = 0; i < 100; ++i) {
		for (int i = 0; i < 14; ++i) {
			data >> x;
			if (i == 0) {
				if (x == 1)
					targetVals = {1, 0, 0};
				if (x == 2)
					targetVals = {0, 1, 0};
				if (x == 3)
					targetVals = {0, 0, 1};
			}
			else {
				//scale the training data first
				if(i == 1) {x = (x - 2) / (14.83 - 11.03);}
				if(i == 2) {x = (x - 2) / (5.8 - 0.74);}
				if(i == 3) {x = (x - 2) / (3.23 - 1.36);}
				if(i == 4) {x = (x - 2) / (30 - 10.6);}
				if(i == 5) {x = (x - 2) / (162 - 170);}
				if(i == 6) {x = (x - 2) / (3.88 - 0.98);}
				if(i == 7) {x = (x - 2) / (5.08 - 0.34);}
				if(i == 8) {x = (x - 2) / (0.66 - 0.13);}
				if(i == 9) {x = (x - 2) / (3.58 - 0.41);}
				if(i == 10) {x = (x - 2) / (13 - 1.28);}
				if(i == 11) {x = (x - 2) / (1.71 - 0.48);}
				if(i == 12) {x = (x - 2) / (4 - 1.27);}
				if(i == 13) {x = (x - 2) / (1680 - 278);}
				inputVals.push_back(x);
			}

			if (i < (14 - 1))
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
