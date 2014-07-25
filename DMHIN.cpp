// DMHIN.cpp : 定义控制台应用程序的入口点。
// Author Wang Ziyi

#include "stdafx.h"
#include "DataImpoter.h"
#include "RankClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DataImpoter *di = new DataImpoter;
	HIN *hin = new HIN;
	*hin = di->readFiles("data/");
	hin->printInfo();
	RankClass *rankClass = new RankClass;
	rankClass->setHIN(*hin);
	rankClass->init(0.2f, 0.1f);
	rankClass->process(0.01f);
	delete rankClass;
	delete hin;
	delete di;
	return 0;
}
