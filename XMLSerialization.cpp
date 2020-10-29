
#include <iostream>
#include <fstream>
#include "pugixml.hpp"
#include "Test.h"
#include "XMLSerializer.h"

int main()
{
    Test* a = new Test(666, 42.2f);
    Test* b = new Test(0, 0);
    std::fstream f("Test.xml", std::ios_base::in | std::ios_base::out);
    polySerial::XMLSerializer xmlSerializer;
    xmlSerializer.Serialize(a, f);
    f.close();
    std::fstream f1("Test.xml", std::ios_base::in | std::ios_base::out);
    xmlSerializer.Deserialize(b, f1);
    xmlSerializer.Serialize(b, std::cout);
    delete a;
    delete b;
}
