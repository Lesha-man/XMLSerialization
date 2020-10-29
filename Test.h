#pragma once
#include <string>
#include "ISerializable.h"
#include "Test2.h"
class Test : public polySerial::ISerializable
{
public:
	int SomeInt;
	Test2* test2;
	Test3* test3;
	float SomeFloat;
	Test(int i, float f);
	~Test() { delete test2; delete test3;}
private:
};

