#include "Test2.h"
Test2::Test2(int i, float f) : ISerializable()
{
	sName = "TestingCl";
	SomeFloat = f;
	SomeInt = i;
	AddSerializable(new polySerial::SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new polySerial::SerializeElement("SomeFloat", &SomeFloat));
}