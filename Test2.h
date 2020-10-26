#pragma once
#include "ISerializable.h"
class Test2 :
    public ISerializable
{
public:
	int SomeInt;
	float SomeFloat;
	Test2(int i, float f);
private:
};

