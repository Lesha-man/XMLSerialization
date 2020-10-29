#include "XMLTypesSerialization.h"
#define simpleType(type) 	{typeid(type*).name(),															\
								[](pugi::xml_node* node, SerializeElement* element)								\
								{																				\
									node->append_attribute(element->sName).set_value(*(type*)(element->sValue));\
								}}																				\

#define simpleDeType(type, astype) 	{typeid(type*).name(),															\
										[](pugi::xml_node* node, SerializeElement* element)								\
										{																				\
											*(type*)element->sValue = node->attribute(element->sName).as_##astype();		\
										}}																				\

using namespace std;
namespace polySerial
{
#pragma region Serialize

	std::map<const char*, TypeSerialise> SerializableTypes =
	{
	{typeid(ISerializable*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			CreateNode((ISerializable*)(element->sValue), &node->append_child(((ISerializable*)(element->sValue))->sName));
		}},
		simpleType(int),
		simpleType(unsigned int),		
		simpleType(long),
		simpleType(unsigned long),
		simpleType(long long),
		simpleType(unsigned long long),
		simpleType(float),
		simpleType(double),
		simpleType(char),
		simpleType(bool),
	//{typeid(int*).name(),
	//	[](pugi::xml_node* node, SerializeElement* element)
	//	{
	//		node->append_attribute(element->sName).set_value(*(int*)(element->sValue));
	//	}},
	};

	void CreateNode(ISerializable* obj, pugi::xml_node* node)
	{
		auto serializableElements = obj->GetSerializableElements();
		for (size_t i = 0; i < serializableElements.size(); i++)
		{
			SerializableTypes[serializableElements[i]->sType](node, serializableElements[i]);
		}
	}
#pragma endregion

#pragma region Deserialize

	std::map<const char*, TypeSerialise> DeserializableTypes =
	{
	{typeid(ISerializable*).name(),
		[](pugi::xml_node* node, SerializeElement* element)
		{
			ReadNode((ISerializable*)element->sValue, &node->child(((ISerializable*)element->sValue)->sName));
			node->remove_child(((ISerializable*)element->sValue)->sName);
		}},
		simpleDeType(int, int),
		simpleDeType(unsigned int, uint),
		simpleDeType(long, llong),
		simpleDeType(unsigned long, ullong),
		simpleDeType(long long, llong),
		simpleDeType(unsigned long long, ullong),
		simpleDeType(float, float),
		simpleDeType(double, double),
		simpleDeType(string, string),
		simpleDeType(bool, bool),
	};

	void ReadNode(ISerializable* obj, pugi::xml_node* node)
	{
		auto serializableElements = obj->GetSerializableElements();
		for (size_t i = 0; i < serializableElements.size(); i++)
		{
			DeserializableTypes[serializableElements[i]->sType](node, serializableElements[i]);
		}
	}
#pragma endregion
}