#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>
#include <fstream>

class TrainData
{
public:
	TrainData(char *inputFileArg, int verbosityFlag);
	void fillData(); //fills input vals vector with the input data
	void printInputVals();
	void printNormalVals();
	void printTargetVals();
	void normalizeData();

private:
	char *fileArg;
	std::ifstream infile;
	std::vector<std::vector<float>> input;
	std::vector<float> inputVals;
	std::vector<std::vector<float>> normalVals;
	std::vector<float> targetVals;
	int verbosity;

};


#endif
