#include "../include/Net.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;


void Net::printTopology() const
{
	for (unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum) {
		cout << "Layer " << layerNum << "contains " << m_layers[layerNum].size() << " neurons" << endl;
	}
}


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
	//cout << "inputVals.size() = " << inputVals.size() <<" m_layers[0].size() - 1 = " << m_layers[0].size() - 1 << endl;
	assert(inputVals.size() == m_layers[0].size() - 1);

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
	auto start = high_resolution_clock::now();
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
				//cout << "added a neuron " << endl;
			}
			//assign bias neuron's value to be constant 1.0
			m_layers.back().back().setOutputVal(1.0);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Constructed Neural Network in " << duration.count() << " ms" << endl;
}
