#include "StdAfx.h"
#include "HIN.h"
#include <iostream>
using std::cout;
using std::endl;

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
void HIN::setIndex_type(map<int, string> index_type)
{
	this->index_type = index_type;
}
map<int, string> HIN::getIndex_type()
{
	return this->index_type;
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
void HIN::setLabel_index(map<string, int> label_index)
{
	this->label_index = label_index;
}
map<string, int> HIN::getLabel_index()
{
	return this->label_index;
}
void HIN::setIndex_label(map<int, string> index_label)
{
	this->index_label = index_label;
}
map<int, string> HIN::getIndex_label()
{
	return this->index_label;
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
void HIN::printInfo()
{
	cout << "HIN Detail Information as follow:" << endl;
	cout << "Data objects (total " << this->getM() << "): ";
	for(vector<vector<Vertex> >::size_type i = 0; i != this->getX().size(); i++)
	{
		vector<Vertex> curType = this->getX()[i];
		string type = this->getIndex_type()[i];
		cout << type << "[" << curType.size() << "]" << " ";
	}
	cout << endl;
	cout << "Classes (total " << this->getK() << "): ";
	for(vector<vector<Vertex> >::size_type i = 0; i != this->getClasses().size(); i++)
	{
		vector<Vertex> curClass = this->getClasses()[i];
		string label = this->getIndex_label()[i];
		cout << label << "[" << curClass.size() << "]" << " ";
	}
	cout << endl;
}
