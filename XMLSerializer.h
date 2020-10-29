#pragma once
#include "ISerializable.h"
namespace polySerial
{
	class XMLSerializer
	{
	public:
		XMLSerializer() {}
		~XMLSerializer() {}
		bool Serialize(ISerializable* obj, std::basic_ostream<char, std::char_traits<char> >& stream);
		bool Deserialize(ISerializable* obj, std::basic_istream<char, std::char_traits<char> >& stream);

	private:
	};

}