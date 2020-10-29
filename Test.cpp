#include "Test.h"

Test::Test(int i, float f) : ISerializable()
{
	sName = "TestingCl";
	SomeFloat = f;
	SomeInt = i;
	test2 = new Test2(i, f);
	test3 = new Test3(i + 11, f / 3);
	AddSerializable(new polySerial::SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new polySerial::SerializeElement("SomeFloat", &SomeFloat));
	AddSerializable(new polySerial::SerializeElement("", test2));
	AddSerializable(new polySerial::SerializeElement("", test3));
}
