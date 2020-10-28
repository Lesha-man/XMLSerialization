
#include <iostream>
#include "pugixml.hpp"
#include "Test.h"
#include "XMLSerializer.h"

int main()
{
    Test* a = new Test(666, 42.2f);
    Test* b = new Test(0, 0);
    XMLSerializer xmlSerializer;
    xmlSerializer.Serialize(a, (char*)"Test.xml");
    xmlSerializer.Deserialize(b, (char*)"Test.xml");
    delete a;
    delete b;
}
