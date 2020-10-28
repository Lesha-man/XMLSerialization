#include "XMLSerializer.h"
#include "pugixml.hpp"
#include <iostream>
#include <map>
namespace polySerial
{
	typedef void (*TypeSerialise)(pugi::xml_node* node, SerializeElement* element);

	#pragma region Serialize
	void CreateNode(ISerializable* obj, pugi::xml_node* node);

	std::map<const char*, TypeSerialise> SerializableTypes =
	{
	{typeid(int*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			node->append_attribute(element->sName).set_value(*(int*)(element->sValue));
		}},
	{typeid(float*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			node->append_attribute(element->sName).set_value(*(float*)(element->sValue));
		}},
	{typeid(ISerializable*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			CreateNode((ISerializable*)(element->sValue), &node->append_child(((ISerializable*)(element->sValue))->sName));
		}},
	};

	void CreateNode(ISerializable* obj, pugi::xml_node* node)
	{
		auto serializableElements = obj->GetSerializableElements();
		for (size_t i = 0; i < serializableElements.size(); i++)
		{
			SerializableTypes[serializableElements[i]->sType](node, serializableElements[i]);
		}
	}

	bool XMLSerializer::Serialize(ISerializable* obj, char* fileName)
	{
		pugi::xml_document document;
		pugi::xml_node* node = new pugi::xml_node(document.append_child(obj->sName));
		CreateNode(obj, node);
		document.save_file(fileName);
		delete node;
		return true;
	}

	#pragma endregion

	#pragma region Deserialize
	void ReadNode(ISerializable* obj, pugi::xml_node* node);

	std::map<const char*, TypeSerialise> DeserializableTypes =
	{
	{typeid(int*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			*(int*)element->sValue = std::atoi(node->attribute(element->sName).value());
		}},
	{typeid(float*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			*(float*)element->sValue = std::atoi(node->attribute(element->sName).value());
		}},
	{typeid(ISerializable*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			ReadNode((ISerializable*)element->sValue, &node->child(((ISerializable*)element->sValue)->sName));
		}},
	};

	void ReadNode(ISerializable* obj, pugi::xml_node* node)
	{
		auto serializableElements = obj->GetSerializableElements();
		for (size_t i = 0; i < serializableElements.size(); i++)
		{
			DeserializableTypes[serializableElements[i]->sType](node, serializableElements[i]);
		}
	}

	bool XMLSerializer::Deserialize(ISerializable* obj, char* fileName)
	{
		pugi::xml_document document;
		document.load_file(fileName);
		ReadNode(obj, &document.child(obj->sName));
		return true;
	}
	#pragma endregion
}