
#include <iostream>
#include "pugixml.hpp"
#include "Test.h"

int main()
{
    Test *a = new Test();
    std::cout << typeid(a).name();
}
