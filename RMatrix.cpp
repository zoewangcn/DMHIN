#include "StdAfx.h"
#include "RMatrix.h"

RMatrix::RMatrix(void)
{
}


RMatrix::~RMatrix(void)
{
}

void RMatrix::setMatrix(vector<vector<float> > matrix)
{
	this->matrix = matrix;
}
vector<vector<float> > RMatrix::getMatrix()
{
	return this->matrix;
}
void RMatrix::setElement(int i, int j, float value)
{
	this->matrix[i][j] = value;
}
float RMatrix::getElement(int i, int j)
{
	return this->matrix[i][j];
}
void RMatrix::resetMatrix()
{
	for(vector<vector<float> >::iterator iter = this->matrix.begin();
		iter != this->matrix.end(); ++iter)
	{
		vector<float> curRow = *iter;
		curRow.clear();
	}
	this->matrix.clear();
}
