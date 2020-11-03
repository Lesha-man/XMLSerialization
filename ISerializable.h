#pragma once
#include <vector>
#include <typeinfo>
#include "pugixml.hpp"

#define serializable(x) AddSerializable(new polySerial::SerializeElement(#x, &x))
#define serializablePtr(x) AddSerializable(new polySerial::SerializeElement(#x, x))

namespace polySerial
{
	class ISerializable;

	class SerializeElement
	{
	private:
	public:
		const char* sName;
		const void* sValue;
		const char* sType;
		template<typename T>
		SerializeElement(const char* name, T* element) : sName(name), sValue(element), sType(typeid(element).name()) 
		{
			if (std::is_base_of<ISerializable, T>::value)
				sType = typeid(ISerializable*).name();
		}
	};

	class ISerializable
	{
	private:
		std::vector<SerializeElement*> serializableElements;
	protected:
	public:
		~ISerializable();
		void AddSerializable(SerializeElement*);
		std::vector<SerializeElement*> GetSerializableElements();
		const char* sName;
	};
}