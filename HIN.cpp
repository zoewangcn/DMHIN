#include "StdAfx.h"
#include "HIN.h"


HIN::HIN(void)
{
}


HIN::~HIN(void)
{
}

void HIN::setX(vector<vector <Vertex> > X)
{
	this->X = X;
}
vector<vector <Vertex> > HIN::getX()
{
	return this->X;
}
void HIN::setRMatrixs(vector<vector<RMatrix> > rMatrixs)
{
	this->rMatrixs = rMatrixs;
}
vector<vector<RMatrix> > HIN::getRMatrixs()
{
	return this->rMatrixs;
}
void HIN::setClasses(vector<vector <Vertex> > classes)
{
	this->classes = classes;
}
vector<vector <Vertex> > HIN::getClasses()
{
	return this->classes;
}
void HIN::setType_index(map<string, int> type_index)
{
	this->type_index = type_index;
}
map<string, int> HIN::getType_index()
{
	return this->type_index;
}
void HIN::setId_index(vector<map<string, int> > id_index)
{
	this->id_index = id_index;
}
vector<map<string, int> > HIN::getId_index()
{
	return this->id_index;
}
void HIN::setIndex_id(vector<map<int, string> > index_id)
{
	this->index_id = index_id;
}
vector<map<int, string> > HIN::getIndex_id()
{
	return this->index_id;
}
void HIN::setM(int m)
{
	this->m = m;
}
int HIN::getM()
{
	return this->m;
}
void HIN::setK(int k)
{
	this->k = k;
}
int HIN::getK()
{
	return this->k;
}
