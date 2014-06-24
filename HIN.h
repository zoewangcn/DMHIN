#pragma once
#include "Vertex.h"
#include "Link.h"
#include <vector>
using std::vector;
class HIN
{
private:
	vector<Vertex> vs;
	vector<Link> ls;
public:
	HIN(void);
	~HIN(void);
};

