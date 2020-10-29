#include "Test3.h"

Test3::Test3(int i, float f):SomeInt(i),SomeFloat(f)
{
	sName = "TestingCl";
	AddSerializable(new polySerial::SerializeElement("SomeInt", &SomeInt));
	AddSerializable(new polySerial::SerializeElement("SomeFloat", &SomeFloat));
}
