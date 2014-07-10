#pragma once
#include <string>
using std::string;
class Vertex
{
private:
	string id;
	string name;
	string type;
	string label;
public:
	Vertex(void);
	~Vertex(void);
	void setId(string id);
	string getId();
	void setName(string name);
	string getName();
	void setType(string type);
	string getType();
	void setLabel(string label);
	string getLabel();
};
