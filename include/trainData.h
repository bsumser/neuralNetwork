#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>
#include <fstream>

class TrainData
{
public:
	TrainData(char *fileArg, int verbosityFlag);
	void getRow();
	void setRow(int r);
	void getCol();
	void setCol(int c);
	void fillData(); //fills input vals vector with the input data
	void printInputVals();
	void printNormalVals();
	void printTargetVals();
	void normalizeData();

private:
	int row;
	int col;
	char *fileArg;
	std::ifstream infile;
	std::vector<std::vector<float>> input;
	std::vector<float> inputVals;
	std::vector<float> normalVals;
	std::vector<float> targetVals;
	int verbosity;

};


#endif
