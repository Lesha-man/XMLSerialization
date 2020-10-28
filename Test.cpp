#include "Test.h"

Test::Test(int i, float f) : ISerializable()
{
	sName = "TestingCl";
	SomeFloat = f;
	SomeInt = i;
	test2 = new Test2(i, f);
	AddSerializable(new polySerial::SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new polySerial::SerializeElement("SomeFloat", &SomeFloat));
	AddSerializable(new polySerial::SerializeElement("ERTY", test2));
}
