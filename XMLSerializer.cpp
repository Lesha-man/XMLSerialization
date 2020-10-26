#include "XMLSerializer.h"
#include "pugixml.hpp"
#include <fstream>
#include <iostream>


XMLSerializer::XMLSerializer(pugi::xml_document* doc): document(doc)
{
}

void CreateNode(ISerializable* obj, pugi::xml_node* node)
{
	int a = 0;
	std::vector<SerializeElement*>* serializableElements = obj->GetSerializableElements();
	for (size_t i = 0; i < serializableElements->size(); i++)
	{
		switch ((*serializableElements)[i]->GetType())
		{
		case Int: {
			node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(int*)serializableElements->at(i)->GetValue());
			break;
		}
		case Float: {
			node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(float*)((*serializableElements)[i]->GetValue()));
			break;
		}
		case Serializable: {
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
//void SSerialize(pugi::xml_node* node, SerializeElement* element)
//{
//	CreateNode((ISerializable*)(element->GetValue()), &node->append_child(((ISerializable*)(element->GetValue()))->GetName().c_str()));
//}

bool XMLSerializer::Serialize(ISerializable* obj)
{
	pugi::xml_node* node = new pugi::xml_node(document->append_child(obj->GetName().c_str()));
	CreateNode(obj, node);
	document->save_file("Test.xml");
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
		case Int: {
			*(int*)(*serializableElements)[i]->GetValue() = std::atoi(node->attribute((*serializableElements)[i]->GetName().c_str()).value());
			break;
		}
		case Float: {
			*(float*)(*serializableElements)[i]->GetValue() = std::atof(node->attribute((*serializableElements)[i]->GetName().c_str()).value());
			break;
		}
		case Serializable: {
			ReadNode((ISerializable*)(*serializableElements)[i]->GetValue(), &node->child(((ISerializable*)((*serializableElements)[i]->GetValue()))->GetName().c_str()));
			break;
		}
		default:
			break;
		}
	}
}

bool XMLSerializer::Deserialize(ISerializable* obj)
{
	document->load_file("Test.xml");
	ReadNode(obj, &document->child(obj->GetName().c_str()));
	return true;
}
