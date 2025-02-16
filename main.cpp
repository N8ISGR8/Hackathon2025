#include <cstdint>
#include <iostream>
#include <vector>
#include "DBHandler.h"

const char* test = "go fuck yourself";
int main()
{
    MongoDB::SendImage("testname", 0, {"tag1", "tag2"}, test);
    return 0;
}
