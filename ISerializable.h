#pragma once
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include "pugixml.hpp"

namespace polySerial
{
	//#define serializableType(type) SerializeElement(std::string name, type* element) : sName(name), sValue(element), sType(e##type) {}

	class ISerializable;

	class SerializeElement
	{
	private:
	public:
		const char* sName;
		const void* sValue;
		const char* sType;
		SerializeElement(const char* name, int* element) : sName(name), sValue(element), sType(typeid(element).name()) {}
		SerializeElement(const char* name, float* element) : sName(name), sValue(element), sType(typeid(element).name()) {}
		SerializeElement(const char* name, ISerializable* element) : sName(name), sValue(element), sType(typeid(element).name()) {}
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