#pragma once
#include <map>
#include "ISerializable.h"
#include "pugixml.hpp"
using namespace std;
namespace polySerial
{
	typedef void (*TypeSerialise)(pugi::xml_node* node, SerializeElement* element);

	void CreateNode(ISerializable* obj, pugi::xml_node* node);

	extern std::map<const char*, TypeSerialise> SerializableTypes;

	void ReadNode(ISerializable* obj, pugi::xml_node* node);

	extern std::map<const char*, TypeSerialise> DeserializableTypes;
}