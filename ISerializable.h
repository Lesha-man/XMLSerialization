#pragma once
#include <map>
#include <string>
#include <vector>
#include "pugixml.hpp"

enum serializableTypess
{
	Serializable,
	Int,
	Float
};
class ISerializable;

class SerializeElement
{
private:
	std::string name;
	void* value;
	serializableTypess type;
public:
	SerializeElement(std::string name, ISerializable* element);
	SerializeElement(std::string name, int* element);
	SerializeElement(std::string name, float* element);

	std::string GetName();
	void* GetValue();
	serializableTypess GetType();

};
class ISerializable
{
private:
	std::vector<SerializeElement*>* serializableElements = new std::vector<SerializeElement*>();
protected:
	std::string name;
public:
	bool AddSerializable(SerializeElement*);
	std::vector<SerializeElement*>* GetSerializableElements();
	std::string GetName();
};
