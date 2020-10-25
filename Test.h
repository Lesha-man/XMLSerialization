#pragma once
#include <string>
#include "ISerializable.h"
class Test : public ISerializable
{
public:
	int SomeInt = 666;
	float SomeFloat = 42.2f;
	Test();
private:
	//serialize(SomeInt);
	//serialize(SomeFloat);
	//serialize(SomeString);
};

