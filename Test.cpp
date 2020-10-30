#include "Test.h"

Test::Test(int i, float f) : ISerializable()
{
	sName = "TestingCl1";
	SomeFloat = f;
	SomeInt = i;
	test2 = new Test2(i, f);
	test3 = new Test3(i + 11, f / 3);
	if (i != 0)
	{
		cc = "hi my const char";
	}
	c = new char[sizeof("hi my char") + 1];
	strcpy_s(c, sizeof("hi my char"), "hi my char");
	AddSerializable(new polySerial::SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new polySerial::SerializeElement("SomeFloat", &SomeFloat));
	AddSerializable(new polySerial::SerializeElement("", test2));
	AddSerializable(new polySerial::SerializeElement("", test3));
	AddSerializable(new polySerial::SerializeElement("doubl", &doubl));
	AddSerializable(new polySerial::SerializeElement("boo", &boo));
	AddSerializable(new polySerial::SerializeElement("strin", &strin));
	AddSerializable(new polySerial::SerializeElement("c", &c));
	AddSerializable(new polySerial::SerializeElement("cc", &cc));
}
