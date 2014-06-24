#pragma once
#include "Vertex.h"
#include "Link.h"
#include <vector>
class HIN
{
private:
	std::vector<Vertex> vs;
	std::vector<Link> ls;
public:
	HIN(void);
	~HIN(void);
};

