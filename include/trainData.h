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
	std::vector<std::vector<double>> input;
	std::vector<double> inputVals;
	std::vector<std::vector<double>> normalVals;
	std::vector<std::vector<double>> targetVals;
	int trainMax;

private:
	char *fileArg;
	std::ifstream infile;
	int verbosity;

};


#endif
