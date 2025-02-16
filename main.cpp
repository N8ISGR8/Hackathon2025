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
#include "Util.h"

int main()
{
    menu();
    //main menu: upload, browse, menu, fork, display
    //upload: enter file name
    //browse: get random IDs and names of those IDs, you can pick from a name
    //menu for when image is open, when window is open
    //fork: asks you for a name, list a number of tags (any amount!) and have you upload an image
    //display: given a name, displays all children of the image

    std::string fileName = "Untitled.png";
//    std::cin >> fileName; 
    std::ifstream file(fileName,std::ios::binary);
    std::string sendImg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    //MongoDB::SendImage("testname", 0, { "tag1", "tag2" }, sendImg);
    Sleep(1000);
    std::string img = MongoDB::ReadImageFromId(886385);
    bool kill = false;
    std::thread t = std::thread(WindowRun, sendImg, std::ref(kill));
    Sleep(10000);
    kill = true;
    while (1);
    return 0;
}
