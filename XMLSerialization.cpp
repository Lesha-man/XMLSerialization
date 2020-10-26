
#include <iostream>
#include "pugixml.hpp"
#include "Test.h"
#include "XMLSerializer.h"

int main()
{
    Test* a = new Test(666, 42.2f);
    Test* b = new Test(0, 0);
    XMLSerializer* xmlSerializer = new XMLSerializer(new pugi::xml_document());
    xmlSerializer->Serialize(a);
    xmlSerializer->Deserialize(b);
    delete xmlSerializer;
}
