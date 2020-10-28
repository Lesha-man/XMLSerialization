#include "XMLSerializer.h"
#include "pugixml.hpp"
#include <iostream>
#include <map>

typedef void (*TypeSerialise)(pugi::xml_node* node, SerializeElement* element);

#pragma region Serialize
void CreateNode(ISerializable* obj, pugi::xml_node* node);

std::map<const char*, TypeSerialise> SerializableTypes =
{	
{typeid(int*).name(), 
	[](pugi::xml_node* node, SerializeElement* element)
	{
		node->append_attribute(element->GetName()).set_value(*(int*)(element->GetValue()));
	}},
{typeid(float*).name(), 
	[](pugi::xml_node * node, SerializeElement * element)
	{
		node->append_attribute(element->GetName()).set_value(*(float*)(element->GetValue()));
	}},
{typeid(ISerializable*).name(), 
	[](pugi::xml_node * node, SerializeElement * element)
	{
		CreateNode((ISerializable*)(element->GetValue()), &node->append_child(((ISerializable*)(element->GetValue()))->GetName()));
	}},
};

void CreateNode(ISerializable* obj, pugi::xml_node* node)
{
	auto serializableElements = obj->GetSerializableElements();
	for (size_t i = 0; i < serializableElements.size(); i++)
	{
		SerializableTypes[serializableElements[i]->GetType()](node, serializableElements[i]);
	}
}

bool XMLSerializer::Serialize(ISerializable* obj, char* fileName)
{
	pugi::xml_document document;
	pugi::xml_node* node = new pugi::xml_node(document.append_child(obj->GetName()));
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
		*(int*)element->GetValue() = std::atoi(node->attribute(element->GetName()).value());
	}},
{typeid(float*).name(),
	[](pugi::xml_node* node, SerializeElement* element)
	{
		*(float*)element->GetValue() = std::atoi(node->attribute(element->GetName()).value());
	}},
{typeid(ISerializable*).name(),
	[](pugi::xml_node* node, SerializeElement* element)
	{
		ReadNode((ISerializable*)element->GetValue(), &node->child(((ISerializable*)element->GetValue())->GetName()));
	}},
};

void ReadNode(ISerializable* obj, pugi::xml_node* node)
{
	auto serializableElements = obj->GetSerializableElements();
	for (size_t i = 0; i < serializableElements.size(); i++)
	{
		DeserializableTypes[serializableElements[i]->GetType()](node, serializableElements[i]);
	}
}

bool XMLSerializer::Deserialize(ISerializable* obj, char* fileName)
{
	pugi::xml_document document;
	document.load_file(fileName);
	ReadNode(obj, &document.child(obj->GetName()));
	return true;
}
#pragma endregion