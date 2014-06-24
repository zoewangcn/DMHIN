#pragma once
#include <string>
class Vertex
{
private:
	int id;
	std::string name;
	std::string type;
	std::string label;
public:
	Vertex(void);
	Vertex(int id, std::string name, std::string type, std::string label):id(id), name(name), type(type), label(label){};
	~Vertex(void);
	int getId() const;
	void setId(int id);
	std::string getName() const;
	void setName(std::string name);
	std::string getType() const;
	void setType(std::string type);
	std::string getLabel() const;
	void setLabel(std::string label);
};

