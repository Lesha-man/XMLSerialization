#include "XMLSerializer.h"
#include "pugixml.hpp"
#include <fstream>
#include <iostream>


XMLSerializer::XMLSerializer(pugi::xml_document* doc): document(doc)
{
}

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
		switch ((*serializableElements)[i]->GetType())
		{
		case eint: {
			node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(int*)serializableElements->at(i)->GetValue());
			break;
		}
		case efloat: {
			node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(float*)((*serializableElements)[i]->GetValue()));
			break;
		}
		case eISerializable: {
			CreateNode((ISerializable*)(*serializableElements)[i]->GetValue(), &node->append_child(((ISerializable*)((*serializableElements)[i]->GetValue()))->GetName().c_str()));
			break;
		}
		default:
			break;
		}
	}
}

//void IntSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	node->append_attribute(element->GetName().c_str()).set_value(*(int*)(element->GetValue()));
//}
//void FloatSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	node->append_attribute(element->GetName().c_str()).set_value(*(float*)(element->GetValue()));
//}
//void ISerializableSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	CreateNode((ISerializable*)(element->GetValue()), &node->append_child(((ISerializable*)(element->GetValue()))->GetName().c_str()));
//}

bool XMLSerializer::Serialize(ISerializable* obj, char* fileName)
{
	pugi::xml_node* node = new pugi::xml_node(document->append_child(obj->GetName().c_str()));
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
