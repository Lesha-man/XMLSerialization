#include "Test2.h"
Test2::Test2(int i, float f) : Test3(i, f)
{
	Flo = 10.10f;
	AddSerializable(new polySerial::SerializeElement("Flo", &Flo));
}