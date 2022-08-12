#ifndef NET_H
#define NET_H

#include <vector>
#include "Neuron.h"
#include "Connection.h"


//typedef for Layer of neurons so I dont
//have to type vector<vector<Neuron>>
typedef std::vector<Neuron> Layer;

//**************** class Net ***************************
class Net 
{
public:
	//Constructor for neural network
	Net(const std::vector<unsigned> &topology);

	//function to feed values from one layer to the next
	void feedForward(const std::vector<int> &inputVals);

	//function that performs back propagation 
	void backProp(const std::vector<double> &targetVals);

	//function to get resultin values from the neural network
	void getResults(std::vector<double> &resultVals) const; 


private:
	//vector made up of each layer, vector of vectors
	std::vector<Layer> m_layers; //m_layers[layerNum][neuronNum]
	
	//used to compute error
	double m_error;
	
	//used to track recent errors in iteration
	double m_recentAverageError;
	
	//
	double m_recentAverageSmoothingFactor;
};
#endif
