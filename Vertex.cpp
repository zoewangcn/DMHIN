#include "StdAfx.h"
#include "Vertex.h"


Vertex::Vertex(void)
{
}


Vertex::~Vertex(void)
{
}

void Vertex::setId(string id)
{
	this->id = id;
}
string Vertex::getId()
{
	return this->id;
}
void Vertex::setName(string name)
{
	this->name = name;
}
string Vertex::getName()
{
	return this->name;
}
void Vertex::setType(string type)
{
	this->type = type;
}
string Vertex::getType()
{
	return this->type;
}
void Vertex::setLabel(string label)
{
	this->label = label;
}
string Vertex::getLabel()
{
	return this->label;
}