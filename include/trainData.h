#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>

class TrainData
{
public:
	TrainData(int r = 0, int c = 0):row(r), col(c) {}
	void fillData(); //fills input vals vector with the input data
	void printInputVals();
	void printNormalVals();
	void printTargetVals();
	void normalizeData();

private:
	int row;
	int col;
	std::vector<double> inputVals;
	std::vector<double> normalVals;
	std::vector<double> targetVals;

};


#endif
