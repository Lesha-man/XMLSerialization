#pragma once
#include <string>
#include "ISerializable.h"
#include "Test2.h"
class Test : public polySerial::ISerializable
{
public:
	Test(int i, float f);
	~Test() { delete test2; delete test3;}
private:
	int SomeInt;
	Test2* test2;
	Test3* test3;
	float SomeFloat;
	std::string strin = "hi my friend";
	const char* cc;
	char* c;
	double doubl = 1234.56789;
	bool boo = true;
};

