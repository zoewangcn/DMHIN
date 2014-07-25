#include "StdAfx.h"
#include "RankClass.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::cerr;
using std::endl;
using std::sqrt;
using std::fabs;

RankClass::RankClass(void)
{
}

RankClass::~RankClass(void)
{
	this->RDs.clear();

}
RMatrix S[MAXN_DO][MAXN_DO];
void RankClass::init(float ll, float aa)
{
	HIN mHin = this->hin;
	vector<vector<Vertex> > mX = mHin.getX();
	int mM = mHin.getM();
	int mK = mHin.getK();
	cout << "RankClass init start!" << endl;
	this->t = 0;
	for(int i = 0; i < mM; i++)
	{
		for(int j = 0; j < mM; j++)
		{
			this->lamda[i][j] = ll;
		}
		this->a[i] = aa;
	}
	cout << "Finish init lamda and a..." << endl;
	int classIndex = 0;
	map<string, float> RD0;
	for(vector<vector<Vertex> >::size_type i = 0; i != mM; ++i)
	{
		vector<Vertex> curType = mX[i];
		for(vector<Vertex>::size_type p = 0; p != curType.size(); ++p)
		{
			Vertex v = curType[p];
			string label = v.getLabel();
			for(int k = 0; k < mK; k++)
			{
				if(label != "" && atoi(label.c_str()) == k)
				{
					RD0[v.getType()[0]+v.getId()+"-"+this->hin.getIndex_label()[k]] 
						= (float)(1.0 / this->hin.getClasses()[k][i].size());
				}
				else
				{
					RD0[v.getType()[0]+v.getId()+"-"+this->hin.getIndex_label()[k]] = 0;
				}
			}
		}
	}
	RDs.push_back(RD0);
	cout << "Finish init Ranking Distribution..." << endl;
	vector<float> sumMatrix[MAXN_DO][MAXN_DO];
	for(int i = 0; i < mM; i++)
	{
		for(int j = i + 1; j < mM; j++)
		{
			RMatrix rm = this->hin.getRMatrixs()[i][j];
			RMatrix rm_r = this->hin.getRMatrixs()[j][i];
			for(int p = 0; p < rm.getMatrix().size(); p++)
			{
				float tmpSum = 0;
				vector<float> curRow = rm.getMatrix()[p];
				for(int q = 0; q < curRow.size(); q++) if(curRow[q] != 0)
				{
					tmpSum += curRow[q];
				}
				sumMatrix[i][j].push_back(tmpSum);
			}
			for(int q = 0; q < rm_r.getMatrix().size(); q++)
			{
				float tmpSum = 0;
				vector<float> curRow = rm_r.getMatrix()[q];
				for(int p = 0; p < curRow.size(); p++) if(curRow[p] != 0)
				{
					tmpSum += curRow[p];
				}
				sumMatrix[j][i].push_back(tmpSum);
			}
		}
	}
	cout << "Finish sum statistics..." << endl;
	RMatrix *D[MAXN_DO][MAXN_DO];
	for(int i = 0; i < mM; i++)
	{
		for(int j = i + 1; j < mM; j++)
		{
			int ni = sumMatrix[i][j].size();
			int nj = sumMatrix[j][i].size();
			D[i][j] = new RMatrix(ni, ni);
			D[j][i] = new RMatrix(nj, nj);
			for(int p = 0; p < ni; p++)
			{
				if(sumMatrix[i][j][p] != 0) D[i][j]->setElement(p, p, (float)(1.0 / sqrt(sumMatrix[i][j][p])));
				else D[i][j]->setElement(p, p, 0);
			}
			for(int q = 0; q < nj; q++)
			{
				if(sumMatrix[j][i][q] != 0) D[j][i]->setElement(q, q, (float)(1.0 / sqrt(sumMatrix[j][i][q])));
				else D[j][i]->setElement(q, q, 0);
			}
		}
	}
	cout << "Finish generate D[i][j]..." << endl;
	for(int i = 0; i < mM; i++)
	{
		for(int j = 0; j < mM; j++) if(i != j)
		{
			if(D[i][j]->getMatrix().size() != 0)
			{
				RMatrix tmp = multipleMatrix(*D[i][j], this->hin.getRMatrixs()[i][j]);
				S[i][j] = multipleMatrix(tmp, *D[j][i]);
			}
		}
	}
	this->t++;
	delete D;
	cout << "RankClass init finish!" << endl;
}
RMatrix RankClass::multipleMatrix(const RMatrix& ra, const RMatrix& rb)
{
	int ar = ra.getMatrix().size();
	int ac = ra.getMatrix()[1].size();
	int br = rb.getMatrix().size();
	int bc = rb.getMatrix()[1].size();
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
			for(int k = 0; k < ac; k++)
			{
				sum += ra.getElement(i, k) * rb.getElement(k, j);
			}
			resMatrix->setElement(i, j, sum);
		}
	}
	return *resMatrix;
}
void RankClass::process(float iterEndTR)
{
	cout << "Starting rankClass process!" << endl;
	cout << "Maximum number of iteration: " << MAXT << endl;
	HIN mHin = this->hin;
	vector<vector<Vertex> > mX = mHin.getX();
	int mM = mHin.getM();
	int mK = mHin.getK();
	vector<vector<RMatrix> > mRM = mHin.getRMatrixs();
 	while(this->t < MAXT)
	{
		map<string, float> curRD;
		cout << "t = " << this->t << endl;
		for(vector<vector<Vertex> >::size_type i = 0; i != mM; ++i)
		{
			vector<Vertex> curType = mX[i];
			for(vector<Vertex>::size_type p = 0; p != curType.size(); ++p)
			{
				Vertex v = curType[p];
				for(int k = 0; k < mK; k++)
				{
					string rdKey = v.getType()[0]+v.getId()+"-"+this->hin.getIndex_label()[k];
					float sumLSP = 0;
					float sumL = 0;
 					for(int j = 0; j < mM; j++) if(i != j && mRM[i][j].getMatrix().size() > 0)
					{
						sumL += lamda[i][j];
						vector<Vertex> xj = mX[j];
						for(vector<Vertex>::size_type q = 0; q != xj.size(); ++q) 
						{
							float sijpq = S[i][j].getElement(p, q);
							if(sijpq != 0)
							{
								string key = xj[q].getType()[0] + xj[q].getId() + "-" + this->hin.getIndex_label()[k];
								float RDxjqk = RDs[this->t-1][key];
								if(RDxjqk != 0)
								{
									sumLSP += this->lamda[i][j] * sijpq * RDxjqk;
								}
							}
						}
					}
					curRD[rdKey] = (sumLSP + this->a[i] * this->RDs[0][rdKey]) / (sumL + this->a[i]);
				}
			}
		}
		RDs.push_back(curRD);
		cout << "t = " << this->t << " finished!" << endl;
		cout << "current size of RDs: " << RDs.size() << endl;
		if(this->checkConverage(iterEndTR))
		{
			cout << "curT: " << this->t << endl;
			break;
		}
		this->t += 1;
	}
	//Bayes Posterior probability
	cout << "Start Bayes!" << endl;
	for(vector<vector<Vertex> >::size_type i = 0; i != mM; ++i)
	{
		vector<Vertex> curType = mX[i];
		for(vector<Vertex>::size_type p = 0; p != curType.size(); ++p)
		{
			Vertex v = curType[p];
			float maxV = -1.0;
			int maxK = -1;
			for(int k = 0; k < mK; k++)
			{
				Vertex v = curType[p];
				string key = v.getType()[0] + v.getId() + "-" + this->hin.getIndex_label()[k];
				resProb[key] = RDs[this->t][key] * mHin.getClasses()[i].size();
				if(resProb[key] > maxV)
				{
					maxV = resProb[key];
					maxK = k;
				}
			}
			if(v.getLabel() == "" && maxK > 0)
			{
				char newLabel[2];
				sprintf(newLabel, "%d", maxK);
				this->hin.getX()[i][p].setLabel(newLabel);
			}
		}
	}
	cout << "Finish Bayes!" << endl;
	//Statistics
	int labeledCounter[MAXN_DO];
	memset(labeledCounter, 0, sizeof(labeledCounter));
	for(vector<vector<Vertex> >::size_type i = 0; i != mM; ++i)
	{
		vector<Vertex> curType = mX[i];
		for(vector<Vertex>::size_type p = 0; p != curType.size(); ++p)
		{
			Vertex v = curType[p];
			if(v.getLabel() != "")
			{
				labeledCounter[i]++;
			}
		}
	}
	for(int i = 0; i < MAXN_DO; i++)
	{
		cout << mX[i][0].getType() << "'s labeled objects number: " << labeledCounter[i] << endl;
	}
}
void RankClass::setHIN(const HIN& hin)
{
	this->hin = hin;
}
HIN RankClass::getHIN()
{
	return this->hin;
}
int RankClass::checkConverage(float iterEndTR)
{
	HIN mHin = this->hin;
	vector<vector<Vertex> > mX = mHin.getX();
	int mM = mHin.getM();
	int mK = mHin.getK();
	for(vector<vector<Vertex> >::size_type i = 0; i != mM; ++i)
	{
		vector<Vertex> curType = mX[i];
		for(vector<Vertex>::size_type p = 0; p != curType.size(); ++p)
		{
			Vertex v = curType[p];
			for(int k = 0; k < mK; k++)
			{
				string rdKey = v.getType()[0]+v.getId()+"-"+this->hin.getIndex_label()[k];
				if(fabs(this->RDs[this->t][rdKey] - this->RDs[this->t-1][rdKey]) > iterEndTR)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
void RankClass::adjustNetwork(HIN& hin)
{

}
