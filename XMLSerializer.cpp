#include "XMLSerializer.h"
#include "pugixml.hpp"


XMLSerializer::XMLSerializer(pugi::xml_document* doc): document(doc)
{
}

bool XMLSerializer::Serialize(ISerializable* obj)
{
	CreateNode(obj, &document->append_child(obj->GetName().c_str()));
	//document->save(;
	return false;
}

void CreateNode(ISerializable* obj, pugi::xml_node* node)
{
	std::vector<SerializeElement*>* serializableElements = obj->GetSerializableElements;
	for (size_t i = 0; i < serializableElements->size; i++)
	{
		switch ((*serializableElements)[i]->GetType())
		{
		case Int: {

			node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(int*)(*serializableElements)[i]->GetValue());
			break;
		}
		case Float: {
			node->append_attribute((*serializableElements)[i]->GetName().c_str()).set_value(*(float*)(*serializableElements)[i]->GetValue());
			break;
		}
		case Serializable: {
			CreateNode((ISerializable*)(*serializableElements)[i]->GetValue(), &node->append_child(((ISerializable*)(*serializableElements)[i]->GetValue())->GetName().c_str()));
			break;
		}
		default:
			break;
		}
	}
}

bool XMLSerializer::Deserialize(ISerializable* obj)
{
	return false;
}
