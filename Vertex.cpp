#include "Stdafx.h"
#include "Vertex.h"
#include <iostream>
using std::cout;

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
string Vertex::getName() const
{
	return this->name;
}
void Vertex::setName(string name)
{
	this->name = name;
}
string Vertex::getType() const
{
	return this->type;
}
void Vertex::setType(string type)
{
	this->type = type;
}
string Vertex::getLabel() const
{
	return this->label;
}
void Vertex::setLabel(string label)
{
	this->label = label;
}
void Vertex::print()
{
	 cout << "" << endl;
}