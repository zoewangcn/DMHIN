#pragma once
#include "Vertex.h"
#include "RMatrix.h"
#include <map>
using std::map;

class HIN
{
private:
	int m; //number of types
	vector<vector <Vertex> > X; //m types, data object
	vector<vector<RMatrix> > RMatrixs; //ith type -- jth type
	int k; //number of classes
	vector<vector <Vertex> > classes; //k classes
	map<string, int> type_index;
public:
	HIN(void);
	~HIN(void);
	void setX(vector<vector <Vertex> > X);
	vector<vector <Vertex> > getX();
	void setRMatrixs(vector<vector<RMatrix> > RMatrixs);
	vector<vector<RMatrix> > getRMatrixs();
	void setClasses(vector<vector <Vertex> > classes);
	vector<vector <Vertex> > getClasses();
	void setType_index(map<string, int> type_index);
	map<string, int> getType_index();
	void setM(int m);
	int getM();
	void setK(int k);
	int getK();
};

