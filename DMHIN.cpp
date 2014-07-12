// DMHIN.cpp : �������̨Ӧ�ó������ڵ㡣
// Author Wang Ziyi

#include "stdafx.h"
#include "DataImpoter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DataImpoter *di = new DataImpoter;
	HIN *hin = new HIN;
	*hin = di->readFiles("data/");
	hin->printInfo();
	RankClass *rankClass = new RankClass;
	rankClass->setHIN(hin);
	rankClass->init();
	delete rankClass;
	delete hin;
	delete di;
	return 0;
}
