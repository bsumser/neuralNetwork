#include <iostream>
#include <stdio>

class Net 
{
public:

private:
};

int main()
{
	//class constructor, topology is layers and neurons per layer
	Net myNet(topology);
	
	//function to feed values fowards from one layer to the next
	myNet.feedForward(inputVals);

	//function to back propagate learning
	myNet.backProp(targetVals);

	//
	myNet.getResults(resultsVals);

	//need to add loop for training samples
}

