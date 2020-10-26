#include "ISerializable.h"

bool ISerializable::AddSerializable(SerializeElement* element)
{
	serializableElements->push_back(element);
	return true;
}

std::vector<SerializeElement*>* ISerializable::GetSerializableElements()
{
	return new std::vector<SerializeElement*>(*serializableElements);
}

std::string ISerializable::GetName()
{
	return std::string(name);
}

SerializeElement::SerializeElement(std::string name, ISerializable* element) : name(name), value(element)
{
	type = Serializable;
}

SerializeElement::SerializeElement(std::string name, int* element): name(name), value(element)
{
	type = Int;
}

SerializeElement::SerializeElement(std::string name, float* element): name(name), value(element)
{
	type = Float;
}

std::string SerializeElement::GetName()
{
	return std::string(name);
}

void* SerializeElement::GetValue()
{
	return value;
}

int* SerializeElement::GetValue()
{
	return value;
}

serializableTypess SerializeElement::GetType()
{
	return type;
}