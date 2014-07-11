#pragma once
#include "HIN.h"
#include <string>
using std::string;
class DataImpoter
{
public:
	DataImpoter(void);
	~DataImpoter(void);
	vector<int> generateRandomSeq(int n, float ratio);
	HIN readFiles(string filePath);
};

