#pragma once
#include "Vertex.h"
class Link
{
private:
	Vertex from;
	Vertex to;
	int id;
	std::string type;
public:
	Link(void);
	~Link(void);
};
