// DMHIN.cpp : 定义控制台应用程序的入口点。
// Author Wang Ziyi

#include "stdafx.h"
#include "DataImpoter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DataImpoter *di = new DataImpoter;
	HIN *hin = new HIN;
	*hin = di->readFiles("data/");
	delete hin;
	delete di;
	return 0;
}
