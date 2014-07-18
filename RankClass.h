#pragma once
#include "HIN.h"
#define MAXT 1000
#define MAXN_DO 5
class RankClass
{
private:
	HIN hin; //Heterogeneous Information Network
	int t; //number of iteration
	float lamda[MAXN_DO][MAXN_DO]; //performing feature selection
	float a[MAXN_DO]; //contribution weight
	RMatrix S[MAXN_DO][MAXN_DO]; //relation matrix (normalized)
	map<string, float> RDs[MAXT]; //ranking distribution key:[id-class]
public:
	RankClass(void);
	~RankClass(void);
	void init(float ll, float aa); //ll-lamda, aa-a
	void process();
	void setHIN(const HIN& hin);
	HIN getHIN();
	void adjustNetwork(HIN& hin);
	RMatrix multipleMatrix(RMatrix ra, RMatrix rb);
};

