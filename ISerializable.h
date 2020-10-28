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
	const char* sName;
	const void* sValue;
	const char* sType;
public:
	SerializeElement(const char* name, int* element) : sName(name), sValue(element), sType((char*)typeid(element).name()) {}
	SerializeElement(const char* name, float* element) : sName(name), sValue(element), sType((char*)typeid(element).name()) {}
	SerializeElement(const char* name, ISerializable* element) : sName(name), sValue(element), sType((char*)typeid(element).name()) {}
	//serializableType(ISerializable)
	//serializableType(int)
	//serializableType(float)
	const char* GetName() { return sName; }
	const void* GetValue() { return sValue; }
	const char* GetType() { return sType; }
};

class ISerializable
{
private:
	std::vector<SerializeElement*> serializableElements;
protected:
	const char* name;
public:
	~ISerializable();
	void AddSerializable(SerializeElement*);
	std::vector<SerializeElement*> GetSerializableElements();
	const char* GetName() { return name; }
};
