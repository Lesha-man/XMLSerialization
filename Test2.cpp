#include "Test2.h"
Test2::Test2(int i, float f) : ISerializable()
{
	name = "TestingCl";
	SomeFloat = f;
	SomeInt = i;
	AddSerializable(new SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new SerializeElement("SomeFloat", &SomeFloat));
}