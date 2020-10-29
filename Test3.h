#pragma once
#include "ISerializable.h"
class Test3 : public polySerial::ISerializable
{
public:
	int SomeInt;
	float SomeFloat;
	Test3(int i, float f);
};

