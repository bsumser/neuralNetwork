#ifndef TRAINDATA_H
#define TRAINDATA_H
#include <vector>

class TrainData
{
public:
	TrainData::TrainData(int row, int col);
	void fillData(); //fills input vals vector with the input data
	void printInputVals();
	void printNormalVals();
	void printTargetVals();
	void normalizeData();

private:
	vector<double> inputVals;
	vector<double> normalVals;
	vector<double> targetVals;

};


#endif
