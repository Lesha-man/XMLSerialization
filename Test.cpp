#include "Test.h"

Test::Test() : ISerializable()
{
	AddSerializable("SomeInt", SomeInt);
	AddSerializable("SomeFloat", SomeFloat);
}
