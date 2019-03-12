#include <iostream>
#include <vector>

class Neuron{};

typedef vector<Neuron> Layer;

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

Net::Net(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();

	//loops through layer number and adds new layer to m_layers container
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		m_layers.push_back(Layer());

	        //inner loop to add neurons to layer, and adds a bias neuron
			for (unsigned neuronNum = 0; neruonNum <= topology[layerNum];) {
				
				//adresses most recent layer added
				m_layers.back()back().push_back(Neuron());
				std::cout << "added a neuron " << std::endl;
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
	std::vector<double> inputVals;
	
	//function to feed values fowards from one layer to the next
	myNet.feedForward(inputVals);

	//vector to hold target values
	std::vector<double> targetVals;
	
	//function to back propagate learning
	myNet.backProp(targetVals);

	//vector to hold result values
	std::vector<double> resultVals;
	
	//function that reads outputs and feeds in back in
	myNet.getResults(resultsVals);

	//need to add loop for training samples
}

