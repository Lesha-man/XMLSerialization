#pragma once
#include "ISerializable.h"
class XMLSerializer
{
public:
	XMLSerializer(pugi::xml_document* doc);
	bool Serialize(ISerializable* obj);
	bool Deserialize(ISerializable* obj);
private:
	pugi::xml_document* document;
};

