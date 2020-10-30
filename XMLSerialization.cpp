
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
    f.seekg(f.beg);
    xmlSerializer.Deserialize(b, f);
    f.close();
    xmlSerializer.Serialize(b, std::cout);
    delete a;
    delete b;
}
