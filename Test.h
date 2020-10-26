#pragma once
#include <string>
#include "ISerializable.h"
#include "Test2.h"
class Test : public ISerializable
{
public:
	int SomeInt;
	float SomeFloat;
	Test2* test2;
	Test(int i, float f);
private:
};

