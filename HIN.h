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
	vector<vector<RMatrix> > rMatrixs; //ith type -- jth type
	int k; //number of classes
	vector<map<int, vector<Vertex> > > classes; //k classes
	map<string, int> type_index;
	map<int, string> index_type;
	vector<map<int, string> > index_id;
	vector<map<string, int> > id_index;
	map<string, int> label_index;
	map<int, string> index_label;
public:
	HIN(void);
	~HIN(void);
	void setX(vector<vector <Vertex> > X);
	vector<vector <Vertex> > getX();
	void setRMatrixs(vector<vector<RMatrix> > rMatrixs);
	vector<vector<RMatrix> > getRMatrixs();
	void setClasses(vector<map<int, vector<Vertex> > > classes);
	vector<map<int, vector<Vertex> > > getClasses();
	void setType_index(map<string, int> type_index);
	map<string, int> getType_index();
	void setIndex_type(map<int, string> index_type);
	map<int, string> getIndex_type();
	void setId_index(vector<map<string, int> > id_index);
	vector<map<string, int> > getId_index();
	void setIndex_id(vector<map<int, string> > index_id);
	vector<map<int, string> > getIndex_id();
	void setLabel_index(map<string, int> label_index);
	map<string, int> getLabel_index();
	void setIndex_label(map<int, string> index_label);
	map<int, string> getIndex_label();
	void setM(int m);
	int getM();
	void setK(int k);
	int getK();
	void printInfo();
};

