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

std::string ISerializable::GetName() { return std::string(name); }

std::string SerializeElement::GetName() { return std::string(sName); }

void* SerializeElement::GetValue() { return sValue; }

serializableTypes SerializeElement::GetType() { return sType; }