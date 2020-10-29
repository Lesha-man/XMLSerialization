#pragma once
#include "ISerializable.h"
#include "Test3.h"

class Test2 : public Test3
{
public:
	float Flo;
	Test2(int i, float f);
private:
};

