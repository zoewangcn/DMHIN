#pragma once
#include "HIN.h"
#define MAXT 50
#define MAXN_DO 3

class RankClass
{
private:
	HIN hin; //Heterogeneous Information Network
	int t; //number of iteration
	float lamda[MAXN_DO][MAXN_DO]; //performing feature selection
	float a[MAXN_DO]; //contribution weight
	//RMatrix S[MAXN_DO][MAXN_DO]; //relation matrix (normalized)
	vector<map<string, float> > RDs; //ranking distribution key:[id-class]
	map<string, float> resProb;
public:
	RankClass(void);
	~RankClass(void);
	void init(float ll, float aa); //ll-lamda, aa-a
	void process(float iterEndTR);
	void setHIN(const HIN& hin);
	HIN getHIN();
	int checkConverage(float iterEndTR);
	void adjustNetwork(HIN& hin);
	RMatrix multipleMatrix(const RMatrix& ra, const RMatrix& rb);
};

