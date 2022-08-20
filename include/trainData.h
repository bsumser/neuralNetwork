#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>
#include <fstream>

class TrainData
{
public:
	TrainData(char *inputFileArg, int verbosityFlag);
	void printInputVals();
	void printInputVals(int row);
	void printNormalVals();
	void printNormalVals(int row);
	void printTargetVals();
	void printTargetVals(int row);
	void normalizeData(const char normalType);
	void convolute(std::vector<std::vector<double>> kernel, int stride, int padding);    //perform first convolution
	void batchNormalize();    //batch normalize the data
	void activationFuntion(char type);    //rectified linear unit activation
	void pool(char type, int size, int stride);    //pooling layer
	std::vector<std::vector<double>> input;
	std::vector<std::vector<double>> normalVals;
	std::vector<std::vector<double>> targetVals;
	int trainMax;

private:
	char *fileArg;
	std::ifstream infile;
	int verbosity;
	std::vector<double> convoResult;
	std::vector<double> batchResult;
	std::vector<double> actResult;
	std::vector<double> poolResult;

};


#endif
