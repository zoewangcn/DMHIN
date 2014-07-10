#pragma once
#include "HIN.h"
#include <string>
using std::string;
class DataImpoter
{
public:
	DataImpoter(void);
	~DataImpoter(void);
	HIN readFiles(string filePath);
};

