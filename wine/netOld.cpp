#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

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
		Neuron(unsigned numOutputs, unsigned myIndex);
		void setOutputVal(double val) { m_outputVal = val; }
		double getOutputVal(void) const { return m_outputVal; }
		void feedForward(const Layer &prevLayer);
		void calcOutputGradients(double targetVal);
		void calcHiddenGradients(const Layer &nextLayer);
		void updateInputWeights(Layer &prevLayer);

private:
		static double eta; //momentum term for updating weights in training 0-1
		static double alpha; //learning rate, controls how much weights are adjusted after each update 0-n
		double m_outputVal;
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		double sumDOW(const Layer &nextLayer) const;	
		//element in this vector for each neuron of the layer
		//to the right that it feeds
		vector<Connection> m_outputWeights;
		unsigned m_myIndex;
		double m_gradient;

};

double Neuron::eta = 0.05; //net learning rate 0-1
double Neuron::alpha = 0.1; //momentum, multiplier of previous delta weight, 0-n

void Neuron::updateInputWeights(Layer &prevLayer)
{
	//update weights in the Connection Struct
	//of the neurons in previous layer
	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient 
				+ alpha * oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	//sum up all the errors of the nodes it feeds
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}
	return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVal)
{
	//take difference between target value, and actaul value
	//and multiply difference by derivative of its output value
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{
	//tanh - output range [-1.0...1.0]
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	//tanh derivative 
	return 1.0 - x * x;
}

void Neuron::feedForward(const Layer &prevLayer)
{
	//variable to hold inputs
	double sum = 0.0;

	//sum all the previous layers inputs
	//include bias node from previous layer
	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(Connection());
		
		//set weight to random value
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;

}



//**************** class Net ***************************
class Net 
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const; 


private:
	vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

void Net::getResults(vector<double> &resultVals) const
{
	//clear previos reults
	resultVals.clear();

	//loop through every output neuron, and move
	//output value to results vals
	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}
void Net::feedForward(const vector<double> &inputVals)
{
	//check if input values and number of neurons in layer are the same
	//size() - 1 to account for the bias neuron
	//assert(inputVals.size() == m_layers[0].size() - 1);
	
	//assign the input values to the input neurons
	for (unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	//forward propagate the values
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {
		Layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}	

void Net::backProp(const vector<double> &targetVals)
{
	//needs to calculate net error (root mean square error of 
	//output neuron errors
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	//loop through neurons in output layer(not including bias), 
	//figure out error(delta) between actual value and the expected value
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1 ; //get the average error squared
	m_error = sqrt(m_error); //this is the root mean square error(RMS)

	//recent average measurement for how well error is
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor +
					m_error) / (m_recentAverageSmoothingFactor + 1.0);
	
	//calculate output layer gradients
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}
	
	//calculate gradients on hidden layers, starting at the rightmost layer
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}

	}
	
	//for all layers from outputs to the first hidden layer,
	//you need to update the connection weights
	
	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];
		
		//for each neuron,index and update index weights based on previous layer
		for (unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}

	}
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
				m_layers.back().push_back(Neuron(numOutputs, neuronNum));
				cout << "added a neuron " << endl;
			}
			//assign bias neuron's value to be constant 1.0
			m_layers.back().back().setOutputVal(1.0);
	}
}

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
