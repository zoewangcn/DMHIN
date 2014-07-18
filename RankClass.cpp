#include "StdAfx.h"
#include "RankClass.h"
#include <iostream>
#include <cmath>
#define MAXN_DO 5
using std::cout;
using std::cerr;
using std::endl;
using std::sqrt;

RankClass::RankClass(void)
{
}

RankClass::~RankClass(void)
{
}
void RankClass::init(float ll, float aa)
{
	cout << "RankClass init start!" << endl;
	this->t = 0;
	for(int i = 0; i < this->hin.getM(); i++)
	{
		for(int j = 0; j < this->hin.getM(); j++)
		{
			this->lamda[i][j] = ll;
		}
		this->a[i] = aa;
	}
	cout << "Finish init lamda and a..." << endl;
	int classIndex = 0;
	for(vector<map<int, vector<Vertex> > >::size_type k = 0; k != this->hin.getClasses().size(); ++k)
	{
		map<int, vector<Vertex> > curClass = this->hin.getClasses()[k];
		for(map<int, vector<Vertex> >::size_type i = 0; i != curClass.size(); ++i)
		{
			vector<Vertex> vs = curClass[i];
			for(vector<Vertex>::size_type j = 0; j != vs.size(); ++j)
			{
				this->RDs[this->t][vs[j].getId()+"-"+this->hin.getIndex_label()[classIndex]] = (float)(1.0 / vs.size());
			}
		}
		classIndex++;
	}
	cout << "Finish init Ranking Distribution..." << endl;
	vector<float> sumMatrix[MAXN_DO][MAXN_DO];
	for(int i = 0; i < this->hin.getM(); i++)
	{
		for(int j = i + 1; j < this->hin.getM(); j++)
		{
			RMatrix rm = this->hin.getRMatrixs()[i][j];
			RMatrix rm_r = this->hin.getRMatrixs()[j][i];
			for(int p = 0; p < rm.getMatrix().size(); p++)
			{
				float tmpSum = 0;
				vector<float> curRow = rm.getMatrix()[p];
				for(int q = 0; q < curRow.size(); q++)
				{
					tmpSum += curRow[q];
				}
				sumMatrix[i][j].push_back(tmpSum);
			}
			for(int q = 0; q < rm_r.getMatrix().size(); q++)
			{
				float tmpSum = 0;
				vector<float> curRow = rm_r.getMatrix()[q];
				for(int p = 0; p < curRow.size(); p++)
				{
					tmpSum += curRow[p];
				}
				sumMatrix[j][i].push_back(tmpSum);
			}
		}
	}
	cout << "Finish sum statistics..." << endl;
	RMatrix *D[MAXN_DO][MAXN_DO];
	for(int i = 0; i < this->hin.getM(); i++)
	{
		for(int j = i + 1; j < this->hin.getM(); j++)
		{
			int ni = sumMatrix[i][j].size();
			int nj = sumMatrix[j][i].size();
			D[i][j] = new RMatrix(ni, ni);
			D[j][i] = new RMatrix(nj, nj);
			for(int p = 0; p < ni; p++)
			{
				D[i][j]->setElement(p, p, (float)(1.0 / sqrt(sumMatrix[i][j][p])));
			}
			for(int q = 0; q < nj; q++)
			{
				D[j][i]->setElement(q, q, (float)(1.0 / sqrt(sumMatrix[j][i][q])));
			}
		}
	}
	cout << "Finish generate D[i][j]..." << endl;
	RMatrix S[MAXN_DO][MAXN_DO];
	for(int i = 0; i < this->hin.getM(); i++)
	{
		for(int j = i + 1; j < this->hin.getM(); j++)
		{
			RMatrix tmp = multipleMatrix(*D[i][j], this->hin.getRMatrixs()[i][j]);
			S[i][j] = multipleMatrix(tmp, *D[j][i]);
		}
	}
	this->t++;
	cout << "RankClass init finish!" << endl;
}
RMatrix RankClass::multipleMatrix(RMatrix ra, RMatrix rb)
{
	int ar = ra.getMatrix().size();
	int ac = ra.getMatrix()[0].size();
	int br = rb.getMatrix().size();
	int bc = rb.getMatrix()[0].size();
	if(ac != br)
	{
		cerr << "Cannot multiple!" << endl;
		RMatrix *resMatrix = new RMatrix;
		return *resMatrix;
	}
	RMatrix *resMatrix = new RMatrix(ar, bc);
	for(int i = 0; i < ar; i++)
	{
		for(int j = 0; j < bc; j++)
		{
			float sum = 0;
			for(int k = 0; k < ar; k++)
			{
				sum += ra.getElement(i, k) * rb.getElement(k, j);
			}
			resMatrix->setElement(i, j, sum);
		}
	}
	return *resMatrix;
}
void RankClass::process()
{

}
void RankClass::setHIN(const HIN& hin)
{
	this->hin = hin;
}
HIN RankClass::getHIN()
{
	return this->hin;
}
void RankClass::adjustNetwork(HIN& hin)
{

}
