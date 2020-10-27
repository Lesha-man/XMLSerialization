#include "XMLSerializer.h"
#include "pugixml.hpp"
#include <fstream>
#include <iostream>
#include <map>

typedef void (*TypeSerialise)(pugi::xml_node* node, SerializeElement* element);

std::map<const char*, TypeSerialise> SerializableTypes =
{	
{typeid(int).name(), 
	[](pugi::xml_node* node, SerializeElement* element)
	{
		node->append_attribute(element->GetName()).set_value(*(int*)(element->GetValue()));
		node->attribute(element->GetName());
	}},
{typeid(float).name(), 
	[](pugi::xml_node * node, SerializeElement * element)
	{
		node->append_attribute(element->GetName()).set_value(*(float*)(element->GetValue()));
	}},
{typeid(ISerializable).name(), 
	[](pugi::xml_node * node, SerializeElement * element)
	{
		CreateNode((ISerializable*)(element->GetValue()), &node->append_child(((ISerializable*)(element->GetValue()))->GetName()));
	}},
};

XMLSerializer::~XMLSerializer()
{
	delete document;
}

void CreateNode(ISerializable* obj, pugi::xml_node* node)
{
	int a = 0;
	std::vector<SerializeElement*>* serializableElements = obj->GetSerializableElements();
	for (size_t i = 0; i < serializableElements->size(); i++)
	{
		SerializableTypes[(*serializableElements)[i]->GetType()](node, (*serializableElements)[i]);
		//switch ((*serializableElements)[i]->GetType())
		//{
		//case typeid(int): {
		//	node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(int*)serializableElements->at(i)->GetValue());
		//	break;
		//}
		//case efloat: {
		//	node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(float*)((*serializableElements)[i]->GetValue()));
		//	break;
		//}
		//case eISerializable: {
		//	CreateNode((ISerializable*)(*serializableElements)[i]->GetValue(), &node->append_child(((ISerializable*)((*serializableElements)[i]->GetValue()))->GetName().c_str()));
		//	break;
		//}
		//default:
		//	break;
		//}
	}
}

//void IntSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	node->append_attribute(element->GetName()).set_value(*(int*)(element->GetValue()));
//	node->attribute(element->GetName());
//}
//void FloatSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	node->append_attribute(element->GetName()).set_value(*(float*)(element->GetValue()));
//}
//void ISerializableSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	CreateNode((ISerializable*)(element->GetValue()), &node->append_child(((ISerializable*)(element->GetValue()))->GetName()));
//}

bool XMLSerializer::Serialize(ISerializable* obj, char* fileName)
{
	pugi::xml_node* node = new pugi::xml_node(document->append_child(obj->GetName()));
	CreateNode(obj, node);
	document->save_file(fileName);
	delete node;
	return true;
}

void ReadNode(ISerializable* obj, pugi::xml_node* node)
{
	int a = 0;
	std::vector<SerializeElement*>* serializableElements = obj->GetSerializableElements();
	for (size_t i = 0; i < serializableElements->size(); i++)
	{
		switch ((*serializableElements)[i]->GetType())
		{
		case eint: {
			*(int*)(*serializableElements)[i]->GetValue() = std::atoi(node->attribute((*serializableElements)[i]->GetName().c_str()).value());
			break;
		}
		case efloat: {
			*(float*)(*serializableElements)[i]->GetValue() = std::atof(node->attribute((*serializableElements)[i]->GetName().c_str()).value());
			break;
		}
		case eISerializable: {
			ReadNode((ISerializable*)(*serializableElements)[i]->GetValue(), &node->child(((ISerializable*)((*serializableElements)[i]->GetValue()))->GetName().c_str()));
			break;
		}
		default:
			break;
		}
	}
}

bool XMLSerializer::Deserialize(ISerializable* obj, char* fileName)
{
	document->load_file(fileName);
	ReadNode(obj, &document->child(obj->GetName().c_str()));
	return true;
}
