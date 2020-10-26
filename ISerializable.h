#pragma once
#include <map>
#include <string>
#include <vector>
#include "pugixml.hpp"

class ISerializable;


enum serializableTypes
{
	eISerializable,
	eint,
	efloat
};

#define serializableType(type) SerializeElement(std::string name, type* element) : sName(name), sValue(element), sType(e##type) {}

class SerializeElement
{
private:
	std::string sName;
	void* sValue;
	serializableTypes sType;
public:
	serializableType(ISerializable)
	serializableType(int)
	serializableType(float)
	std::string GetName();
	void* GetValue();
	serializableTypes GetType();
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
