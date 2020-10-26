#include "Test.h"

Test::Test(int i, float f) : ISerializable()
{
	name = "TestingCl";
	SomeFloat = f;
	SomeInt = i;
	test2 = new Test2(i, f);
	AddSerializable(new SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new SerializeElement("SomeFloat", &SomeFloat));
	AddSerializable(new SerializeElement("ERTY", test2));
}
