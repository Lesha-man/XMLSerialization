#include "ISerializable.h"
namespace polySerial
{
	ISerializable::~ISerializable()
	{
		for (size_t i = 0; i < serializableElements.size(); i++)
		{
			delete serializableElements[i];
		}
	}

	void ISerializable::AddSerializable(SerializeElement* element)
	{
		serializableElements.push_back(element);
	}

	std::vector<SerializeElement*> ISerializable::GetSerializableElements()
	{
		return serializableElements;
	}
}