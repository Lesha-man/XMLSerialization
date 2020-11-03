#include "Test3.h"

Test3::Test3(int i, float f):SomeInt(i),SomeFloat(f)
{
	sName = "TestingCl3";
	serializable(SomeInt);
	serializable(SomeFloat);
}
