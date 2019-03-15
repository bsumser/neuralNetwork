#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <stdlib.h>
#include "Connection.h"

class Neuron;

typedef std::vector<Neuron> Layer;


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
		static double alpha; //learning rate, controls how much weights 
							//are adjusted after each update 0-n
		double m_outputVal;
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		static double randomWeight(void) { return rand() / double(RAND_MAX); }
		double sumDOW(const Layer &nextLayer) const;	
		//element in this vector for each neuron of the layer
		//to the right that it feeds
		std::vector<Connection> m_outputWeights;
		unsigned m_myIndex;
		double m_gradient;

};
#endif
