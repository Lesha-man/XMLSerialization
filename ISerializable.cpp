#include "ISerializable.h"

void ISerializable::AddSerializable(SerializeElement* element)
{
	serializableElements->push_back(element);
}

std::vector<SerializeElement*>* ISerializable::GetSerializableElements()
{
	return new std::vector<SerializeElement*>(*serializableElements);
}