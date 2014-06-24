#pragma once
#include <string>
using std::string;
class Vertex
{
private:
	int id;
	string name;
	string type;
	string label;
public:
	Vertex(void);
	Vertex(int id, string name, string type, string label):id(id), name(name), type(type), label(label){};
	~Vertex(void);
	int getId() const;
	void setId(int id);
	string getName() const;
	void setName(string name);
	string getType() const;
	void setType(string type);
	string getLabel() const;
	void setLabel(string label);
};

