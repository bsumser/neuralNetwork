#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

using namespace std;

struct Connection
{
	//values for weights in neurons and the changes in weights
	double weight;
	double deltaWeight;

};

//forward reference so that typedef will function
class Neuron;

typedef vector<Neuron> Layer;


//**************** class Neuron ***************************

class Neuron
{
public:
		Neuron(unsigned numOutputs);

private:
		double m_outputVal;

		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		
		//element in this vector for each neuron of the layer
		//to the right that it feeds
		vector<Connection> m_outputWeights;

};

Neuron::Neuron(unsinged numOutputs)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(Connection());
		
		//set weight to random value
		m_outputWeights.back().weight = randomWeight();
	}

}



//**************** class Net ***************************
class Net 
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals) {};
	void backProp(const vector<double> &targetVals) {};
	void getResults(vector<double> &resultVals) const {};


private:
	vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
};

Net::feedForward(const vector<double> &inputVals)
{
	//check if input values and number of neurons in layer are the same
	//size() - 1 to account for the bias neuron
	assert(inputVals.size() == m_layers[0].size() - 1;)
	
	//assign the input values to the input neurons
	for (unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	//forward propagate the values
	for (unsigned layerNum = 1; layerNum)
}	

Net::Net(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();

	//loops through layer number and adds new layer to m_layers container
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		m_layers.push_back(Layer());

		//if layer number is output layer, then number of outputs is 0
		//otherwise number of outputs is whatever is in topology for the
		//next layer over
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

	        //inner loop to add neurons to layer, and adds a bias neuron
			for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
				
				//adresses most recent layer added
				m_layers.back().push_back(Neuron(numOutputs));
				cout << "added a neuron " << endl;
			}
	}
}

int main()
{
	//vector to dictate node and layer setup for network
	vector<unsigned> topology;

	//
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);

	//class constructor, topology is layers and neurons per layer
	Net myNet(topology);

	//vector to hold input values
	vector<double> inputVals;
	
	//function to feed values fowards from one layer to the next
	myNet.feedForward(inputVals);

	//vector to hold target values
	vector<double> targetVals;
	
	//function to back propagate learning
	myNet.backProp(targetVals);

	//vector to hold result values
	vector<double> resultsVals;
	
	//function that reads outputs and feeds in back in
	myNet.getResults(resultsVals);

	//need to add loop for training samples
}

