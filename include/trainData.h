#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>
#include <fstream>

class TrainData
{
public:
	TrainData(char *inputFileArg, int verbosityFlag);
	void printInputVals();
	void printNormalVals();
	void printTargetVals();
	void normalizeData(const char normalType);
	std::vector<std::vector<float>> input;
	std::vector<float> inputVals;
	std::vector<std::vector<float>> normalVals;
	std::vector<std::vector<float>> targetVals;

private:
	char *fileArg;
	std::ifstream infile;
	int verbosity;

};


#endif
