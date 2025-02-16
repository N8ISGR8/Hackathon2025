#include <cstdint>
#include <iostream>
#include <vector>
#include "DBHandler.h"
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <istream>
#include <thread>
#include "Window.h"

int main()
{
    std::string fileName = "cute_image.png";
//    std::cin >> fileName; 
    std::ifstream file(fileName,std::ios::binary);
    std::string sendImg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    MongoDB::SendImage("testname", 0, { "tag1", "tag2" }, sendImg);
    Sleep(1000);
    std::string img = MongoDB::ReadImageFromId(886385);
    bool kill = false;
    std::thread t = std::thread(WindowRun, img, std::ref(kill));
    Sleep(10000);
    kill = true;
    while (1);
    return 0;
}
