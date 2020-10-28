#pragma once
#include "ISerializable.h"
class XMLSerializer
{
public:
	XMLSerializer() {}
	~XMLSerializer() {}
	bool Serialize(ISerializable* obj, char* fileName);
	bool Deserialize(ISerializable* obj, char* fileName);

private:
	pugi::xml_document document;
};

