#pragma once
#include <map>
#include <string>
#include <vector>

enum serializableTypess
{
	Serializable,
	Int,
	Float
};

class ISerializable
{
private:
	std::string name;
	std::vector<SerializeElement*> * serializableElements = new std::vector<SerializeElement*>();
public:
	bool AddSerializable(SerializeElement*);
	std::vector<SerializeElement*>* GetSerializableElements();
	std::string GetName();
};

class SerializeElement
{
private:
	std::string name;
	void* value;
	serializableTypess type;
public:
	SerializeElement(std::string name, ISerializable* element);
	SerializeElement(std::string name, int element);
	SerializeElement(std::string name, float element);

	std::string GetName();
	void* GetValue();
	serializableTypess GetType();

};