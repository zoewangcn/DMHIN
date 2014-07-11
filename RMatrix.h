#pragma once
#include <vector>
#define MAXN 1000 + 10
using std::vector;
class RMatrix
{
private:
	vector<vector<float> > matrix;
public:
	RMatrix(void);
	RMatrix(int rowNum, int colNum);
	~RMatrix(void);
	void setMatrix(vector<vector<float> > matrix);
	vector<vector<float> > getMatrix();
	void setElement(int i, int j, float value);
	float getElement(int i, int j);
	void resetMatrix();
};

