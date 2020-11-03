#include "Test.h"

Test::Test(int i, float f) : ISerializable()
{
	serializable(SomeInt);
	serializable(SomeFloat);
	serializable(doubl);
	serializable(boo);
	serializable(strin);
	serializable(c);
	serializable(cc);
	sName = "TestingCl1";
	SomeFloat = f;
	SomeInt = i;
	test2 = new Test2(i, f);
	serializablePtr(test2);
	test3 = new Test3(i + 11, f / 3);
	serializablePtr(test3);
	if (i != 0)
	{
		cc = "hi my const char";
	}
	c = new char[sizeof("hi my char") + 1];
	strcpy_s(c, sizeof("hi my char"), "hi my char");
}
