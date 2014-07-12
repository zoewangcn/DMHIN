#include "StdAfx.h"
#include "DataImpoter.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#define MAXSIZE_BUF 5000
#define LINENUM 3
#define LABEL_NUM 4
#define MAX_TYPE_NUM 20000
#define LINE_LIMIT 3000
using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;
using std::set;
using std::sort;

DataImpoter::DataImpoter(void)
{
}


DataImpoter::~DataImpoter(void)
{
}

vector<int> DataImpoter::generateRandomSeq(int n, float ratio)
{
	vector<int> randomArr;
	for(int i = 0; i < n; i++)
	{
		randomArr.push_back(-1);
	}
	for(int i = 0; i < n; i++)
	{
		int index = rand() % n;
	}
	return randomArr;
}

HIN DataImpoter::readFiles(string filePath)
{
	HIN *hin;
	try
	{
		hin = new HIN;
	}
	catch (std::bad_alloc)
	{
		cerr << "HIN creating has alloc exception" << endl;
	}
	const string labels[LABEL_NUM] = {"Database", "Data Mining", "AI", "Information Retrieval"};
	//read info file in order to get file types
	ifstream info;
	info.open("info_DBLP.txt");
	char *buf;
	vector<char*> infoStr;
	vector<string> objectFileList;
	vector<string> labelFileList;
	vector<string> linkFileList;
	vector<string> ratioList;
	map<string, float> type_ratio;
	int lineCount = 0;
	if(!info)
	{
		cerr << "Error: unable to open info file: " << info << endl;
		return *hin;
	}
	else
	{
		cout << "Info file list:" << endl;
		while(!info.eof())
		{
			buf = new char[MAXSIZE_BUF];
			info.getline(buf, MAXSIZE_BUF);
			cout << buf << endl;
			infoStr.push_back(buf);
		}
	}
	info.close();
	const char *split = ",";
	char *tmp = strtok(infoStr[0], split);
	while(tmp != NULL)
	{
		objectFileList.push_back(tmp);
		tmp = strtok(NULL, split);
	}
	tmp = strtok(infoStr[1], split);
	while(tmp != NULL)
	{
		labelFileList.push_back(tmp);
		tmp = strtok(NULL, split);
	}
	tmp = strtok(infoStr[2], split);
	while(tmp != NULL)
	{
		linkFileList.push_back(tmp);
		tmp = strtok(NULL, split);
	}
	tmp = strtok(infoStr[3], split);
	const char *split_INSTR = ":";
	while(tmp != NULL)
	{
		ratioList.push_back(tmp);	
		tmp = strtok(NULL, split);
	}
	for(vector<string>::size_type i = 0; i != ratioList.size(); ++i)
	{
		char *type = strtok(const_cast<char*>(ratioList[i].c_str()), split_INSTR);
		char *ratio = strtok(NULL, split_INSTR);
		type_ratio[type] = atof(ratio);
	}
	ratioList.clear();
	infoStr.clear();
	delete[] buf;
	cout << "####################################################" << endl;

	const char *split_TAB = "	";
	const char *split_DOT = ".";
	const char *split_LINE = "_";
	//read data objects
	vector<vector <Vertex> > X;
	map<string, int> type_index;
	map<int, string> index_type;
	vector<map<int, string> > index_id;
	vector<map<string, int> > id_index;
	for(vector<string>::size_type i = 0; i != objectFileList.size(); ++i)
	{
		map<int, string> cur_index_id;
		map<string, int> cur_id_index;
		ifstream in;
		in.open(filePath.c_str() + objectFileList[i]);
		char *fileName = const_cast<char*>(objectFileList[i].c_str());
		string type = strtok(fileName, split_DOT);
		vector<Vertex> curTypeX;
		if(!in)
		{
			cerr << "Error: unable to open objects file: " << in << endl;
		}
		else
		{
			int line = 0;
			int tmpIndex = 0;
			while(!in.eof())
			{
				++line;
				if(line > LINE_LIMIT)
				{
					break;
				}
				buf = new char[MAXSIZE_BUF];
				in.getline(buf, MAXSIZE_BUF);
				char *id = strtok(buf, split_TAB);
				char *name = strtok(NULL, split_TAB);
				Vertex *v = new Vertex;
				v->setId(id);
				v->setName(name);
				v->setType(type);
				curTypeX.push_back(*v);
				cur_index_id[tmpIndex] = id;
				cur_id_index[id] = tmpIndex++;
			}
		}
		in.close();
		X.push_back(curTypeX);
		type_index[type] = i;
		index_type[i] = type;
		id_index.push_back(cur_id_index);
		index_id.push_back(cur_index_id);
	}
	delete[] buf;
	objectFileList.clear();
	cout << "Finish read objects!" << endl;
	hin->setM(type_index.size());
	hin->setType_index(type_index);
	hin->setIndex_type(index_type);
	hin->setId_index(id_index);
	hin->setIndex_id(index_id);

	//read labels
	map<string, int> label_index;
	map<int, string> index_label;
	for(vector<string>::size_type i = 0; i != labelFileList.size(); ++i)
	{
		ifstream in;
		in.open(filePath.c_str() + labelFileList[i]);
		char *fileName = const_cast<char*>(labelFileList[i].c_str());
		string type = strtok(fileName, split_LINE);
		vector<Vertex> curTypeV = X[type_index[type]];
		map<string, string> id_label;
		if(!in)
		{
			cerr << "Error: unable to open labels file: " << in << endl;
		}
		else
		{
			while(!in.eof())
			{
				buf = new char[MAXSIZE_BUF];
				in.getline(buf, MAXSIZE_BUF);
				char *id = strtok(buf, split_TAB);
				char *label = strtok(NULL, split_TAB);
				char *name = strtok(NULL, split_TAB);
				id_label[id] = label;
			}
		}
		int labeled_data_num = 0;
		for(vector<Vertex>::iterator iter = curTypeV.begin(); iter != curTypeV.end(); ++iter)
		{
			string curId = iter->getId();
			if(id_label.count(curId))
			{
				iter->setLabel(id_label[curId]);
				labeled_data_num++;
			}
		}
		cout << type << "'s labeled objects number: " << labeled_data_num << endl;
		in.close();
		X[type_index[type]] = curTypeV;
	}
	delete[] buf;
	labelFileList.clear();
	for(int i = 0; i < LABEL_NUM; i++)
	{
		label_index[labels[i]] = i;
		index_label[i] = labels[i];
	}
	cout << "Finish read labels!" << endl;
	hin->setK(LABEL_NUM);
	hin->setIndex_label(index_label);
	hin->setLabel_index(label_index);
	hin->setX(X);

	//read links
	vector<vector<RMatrix> > rMatrixs;
	RMatrix tmpRMatrixs[4][4];
	for(vector<string>::size_type k = 0; k != linkFileList.size(); ++k)
	{ 
		ifstream in;
		in.open(filePath.c_str() + linkFileList[k]);
		char *fileName = const_cast<char*>(linkFileList[k].c_str());
		string linkFileName = strtok(fileName, split_DOT);
		string typei = strtok(const_cast<char*>(linkFileName.c_str()), split_LINE);
		string typej = strtok(NULL, split_LINE);
		int i = type_index[typei];
		int j = type_index[typej];
		int rowNum = X[i].size();
		int colNum = X[j].size();
		RMatrix *rMatrix;
		try
		{
			rMatrix = new RMatrix(rowNum, colNum);
		}
		catch (std::bad_alloc)
		{
			cerr << "RMatrix creating has alloc exception" << endl;
		}
		if(!in)
		{
			cerr << "Error: unable to open links file: " << in << endl;
		}
		else
		{
			while(!in.eof())
			{
				buf = new char[MAXSIZE_BUF];
				in.getline(buf, MAXSIZE_BUF);
				char *id_i = strtok(buf, split_TAB);
				char *id_j = strtok(NULL, split_TAB);
				if(id_index[i].count(id_i) && id_index[j].count(id_j))
				{
					int index_i = id_index[i][id_i];
					int index_j = id_index[j][id_j];
					rMatrix->setElement(index_i, index_j, 1);
				}
			}
		}
		in.close();
		try
		{
			tmpRMatrixs[i][j] = *rMatrix;
		}
		catch (std::bad_alloc)
		{
			cerr << "temp RMatrix creating has alloc exception" << endl;
		}
	}
	RMatrix *nrx = new RMatrix;
	for(int i = 0; i < hin->getM(); i++)
	{
		vector<RMatrix> curRV;
		for(int j = 0; j < hin->getM(); j++)
		{
			curRV.push_back(*nrx);
		}
		rMatrixs.push_back(curRV);
	}
	for(int i = 0; i < hin->getM(); i++)
	{
		for(int j = 0; j < hin->getM(); j++)
		{
			if(i != j)
			{
				rMatrixs[i][j] = tmpRMatrixs[i][j];
			}
		}
	}
	delete nrx;
	delete[] buf;
	linkFileList.clear();
	cout << "Finish read links!" << endl;
	hin->setRMatrixs(rMatrixs);

	//read classes
	vector<vector<Vertex> > classes;
	for(int i = 0; i < hin->getK(); i++)
	{
		char theLabel[10];
		sprintf(theLabel, "%d", i);
		vector<Vertex> curClass;
		vector<vector<Vertex> > XX = hin->getX();
		for(vector<vector<Vertex> >::iterator typeIter = XX.begin(); 
			typeIter != XX.end(); ++typeIter)
		{
			vector<Vertex> curTypeObjs = *typeIter;
			for(vector<Vertex>::iterator objIter = curTypeObjs.begin();
				objIter != curTypeObjs.end(); ++objIter)
			{
				Vertex v = *objIter;
				if(v.getLabel() == theLabel)
				{
					curClass.push_back(v);
				}
			}
		}
		classes.push_back(curClass);
	}
	hin->setClasses(classes);
	cout << "Finish read classes!" << endl;

	return *hin;
}
