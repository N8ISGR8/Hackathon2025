#include <cstdint>
#include <iostream>
#include <vector>
#include "DBHandler.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const char* test = "go fuck yourself";
int main()
{
    sf::Window(sf::VideoMode({200,200}), "Name", sf::State::Windowed);
    MongoDB::SendImage("testname", 0, {"tag1", "tag2"}, test);
    Sleep(1000);
    std::cout << MongoDB::ReadImageFromId(198424) << std::endl;
    while (1);
    return 0;
}
