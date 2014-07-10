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
void HIN::setRMatrixs(vector<vector<RMatrix> > RMatrixs)
{
	this->RMatrixs = RMatrixs;
}
vector<vector<RMatrix> > HIN::getRMatrixs()
{
	return this->RMatrixs;
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
map<string, int> getType_index();
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
