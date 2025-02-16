#include <cstdint>
#include <iostream>
#include <vector>
#include "DBHandler.h"
#include <Windows.h>

const char* test = "go fuck yourself";
int main()
{
    MongoDB::SendImage("testname", 0, {"tag1", "tag2"}, test);
    Sleep(1000);
    std::cout <<  MongoDB::ReadImageFromId(198424) << std::endl;
    return 0;
}
