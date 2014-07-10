#include "StdAfx.h"
#include "DataImpoter.h"
#include <iostream>
#include <fstream>
#define MAXSIZE_BUF 5000
#define LINENUM 3
#define LABEL_NUM 4
using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;

DataImpoter::DataImpoter(void)
{
}


DataImpoter::~DataImpoter(void)
{
}

HIN DataImpoter::readFiles(string filePath)
{
	HIN *hin = new HIN;
	const string labels[LABEL_NUM] = {"Database", "Data Mining", "AI", "Information Retrieval"};
	//read info file in order to get file types
	ifstream info;
	info.open("info.txt");
	char *buf;
	vector<char*> infoStr;
	vector<string> objectFileList;
	vector<string> labelFileList;
	vector<string> linkFileList;
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
	infoStr.clear();
	delete[] buf;
	cout << "####################################################" << endl;

	const char *split_TAB = "	";
	const char *split_DOT = ".";
	const char *split_LINE = "_";
	//read data objects
	vector<vector <Vertex> > X;
	map<string, int> type_index;
	for(vector<string>::size_type i = 0; i != objectFileList.size(); ++i)
	{
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
			while(!in.eof())
			{
				buf = new char[MAXSIZE_BUF];
				in.getline(buf, MAXSIZE_BUF);
				char *id = strtok(buf, split_TAB);
				char *name = strtok(NULL, split_TAB);
				Vertex *v = new Vertex;
				v->setId(id);
				v->setName(name);
				v->setType(type);
				curTypeX.push_back(*v);
			}
		}
		in.close();
		X.push_back(curTypeX);
		type_index[type] = i;
	}
	delete[] buf;
	cout << "Finish read objects!" << endl;

	//read labels
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
		for(vector<Vertex>::iterator iter = curTypeV.begin(); iter != curTypeV.end(); ++iter)
		{
			string curId = iter->getId();
			if(id_label.count(curId))
			{
				iter->setLabel(id_label[curId]);
			}
		}
		in.close();
	}
	delete[] buf;
	cout << "Finish read labels!" << endl;

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
		vector<Vertex> curTypeVi = X[i];
		vector<Vertex> curTypeVj = X[j];
		map<string, string> id_label;
		if(!in)
		{
			cerr << "Error: unable to open links file: " << in << endl;
		}
		else
		{
			int line = 0;
			while(!in.eof())
			{
				++line;
				buf = new char[MAXSIZE_BUF];
				in.getline(buf, MAXSIZE_BUF);
				char *i = strtok(buf, split_TAB);
				char *j = strtok(NULL, split_TAB);
				if(i == NULL)
				{
					cout << "null i" << endl;
					cout << line << endl;
				}
				if(j == NULL)
				{
					cout << "null j" << endl;
					cout << line << endl;
				}
			}
		}
		in.close();
	}
	delete[] buf;
	cout << "Finish read links!" << endl;

	//set HIN

	return *hin;
}
