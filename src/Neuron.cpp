#include "../include/Neuron.h"
#include <cmath>

double Neuron::eta = 0.1; //net learning rate 0-1
double Neuron::alpha = 0.01; //momentum, multiplier of previous delta weight, 0-n

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
	//sigmoid - output range [0...1.0]
	return x / (1 + abs(x));
}

double Neuron::transferFunctionDerivative(double x)
{
	//sigmoid derivative 
	return x * (1-x);
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

