#include "StdAfx.h"
#include "Vertex.h"


Vertex::Vertex(void)
{
}


Vertex::~Vertex(void)
{
}

int Vertex::getId() const
{
	return this->id;
}
void Vertex::setId(int id)
{
	this->id = id;
}
std::string Vertex::getName() const
{
	return this->name;
}
void Vertex::setName(std::string name)
{
	this->name = name;
}
std::string Vertex::getType() const
{
	return this->type;
}
void Vertex::setType(std::string type)
{
	this->type = type;
}
std::string Vertex::getLabel() const
{
	return this->label;
}
void Vertex::setLabel(std::string label)
{
	this->label = label;
}