#pragma once
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include "pugixml.hpp"

class ISerializable;

//#define serializableType(type) SerializeElement(std::string name, type* element) : sName(name), sValue(element), sType(e##type) {}

class SerializeElement
{
private:
	char* sName;
	void* sValue;
	const char* sType;
public:
	SerializeElement(char* name, int* element) : sName(name), sValue(element), sType(typeid(element).name()) {}
	SerializeElement(char* name, float* element) : sName(name), sValue(element), sType(typeid(element).name()) {}
	SerializeElement(char* name, ISerializable* element) : sName(name), sValue(element), sType(typeid(element).name()) {}
	//serializableType(ISerializable)
	//serializableType(int)
	//serializableType(float)
	char* GetName() { return &*sName; }
	void* GetValue() { return sValue; }
	const char* GetType() { return sType; }
};

class ISerializable
{
private:
	std::vector<SerializeElement*>* serializableElements = new std::vector<SerializeElement*>();
protected:
	char* name;
public:
	void AddSerializable(SerializeElement*);
	std::vector<SerializeElement*>* GetSerializableElements();
	char* GetName() { return name; }
};
