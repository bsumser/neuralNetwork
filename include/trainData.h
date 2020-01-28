#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>
#include <fstream>

class TrainData
{
public:
	TrainData(char *fileArg);
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
	ifstream infile;
	std::vector<double> inputVals;
	std::vector<double> normalVals;
	std::vector<double> targetVals;

};


#endif
