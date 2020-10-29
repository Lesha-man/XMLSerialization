#include "XMLSerializer.h"
#include "pugixml.hpp"
#include <iostream>
#include <map>
#include "XMLTypesSerialization.h"

namespace polySerial
{
	bool XMLSerializer::Serialize(ISerializable* obj, std::basic_ostream<char, std::char_traits<char> >& stream)
	{
		pugi::xml_document document;
		pugi::xml_node* node = new pugi::xml_node(document.append_child(obj->sName));
		CreateNode(obj, node);
		document.save(stream);
		delete node;
		return true;
	}

	bool XMLSerializer::Deserialize(ISerializable* obj, std::basic_istream<char, std::char_traits<char> >& stream)
	{
		pugi::xml_document document;
		document.load(stream);
		ReadNode(obj, &document.child(obj->sName));
		return true;
	}
}