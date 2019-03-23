#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "../include/Net.h"
#include "../include/Neuron.h"

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

	//array to calc mean and 
	vector<double> normalVals;


	char dummy;
	double x;
	int userEpoch;
	int userLine;
	do {
		cout << "Please enter amount of epochs, 1 to infinity" << endl;
		cin >> userEpoch;
		cout << "Please enter amount of lines 1 - 178" << endl;
		cin >> userLine;
		for (int epoch = 0; epoch < userEpoch; ++epoch) {
			//open data file
			ifstream data ("/data/wine.data");
			for (int i = 0; i < userLine; ++i) {
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
					else {
						if(j == 1) { normalVals.push_back((x - 13.00062) / 0.807278);}
						if(j == 2) { normalVals.push_back((x - 2.336348) / 1.110888);}
						if(j == 3) { normalVals.push_back((x - 2.366517) / 0.272807);}
						if(j == 4) { normalVals.push_back((x - 19.49494) / 3.320855);}
						if(j == 5) { normalVals.push_back((x - 99.74157) / 14.20247);}
						if(j == 6) { normalVals.push_back((x - 2.295112) / 0.622345);}
						if(j == 7) { normalVals.push_back((x - 2.02927) / 0.993263);}
						if(j == 8) { normalVals.push_back((x - 0.361854) / 0.123756);}
						if(j == 9) { normalVals.push_back((x - 1.590899) / 0.569152);}
						if(j == 10) { normalVals.push_back((x - 5.05809) / 2.305298);}
						if(j == 11) { normalVals.push_back((x - 0.957449) / 0.227291);}
						if(j == 12) { normalVals.push_back((x - 2.611685) / 0.706013);}
						if(j == 13) { normalVals.push_back((x - 746.8933) / 313.1433);}
						inputVals.push_back(x);
					}

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
				
				cout << "Normalized data is: ";
				for (size_t i = 0; i < normalVals.size(); ++i) {
					cout << normalVals[i] << " ";
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
				

				//need to add loop for training samples
				inputVals.clear();
				normalVals.clear();
			}
			data.close();
		}
	}while(userEpoch != 0);
}
