#pragma once
#include <string>
#include "ISerializable.h"
#include "Test2.h"
class Test : public ISerializable
{
public:
	int SomeInt;
	Test2* test2;
	float SomeFloat;
	Test(int i, float f);
private:
};

