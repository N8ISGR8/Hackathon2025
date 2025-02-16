#include "Window.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>


void WindowRun(std::string imageContent, bool& kill)
{
    sf::MemoryInputStream mis = sf::MemoryInputStream(imageContent.c_str(), imageContent.size());

    sf::Texture tex = sf::Texture(sf::Image(mis));
    sf::Sprite sprite(tex);
    sf::RenderWindow window(sf::VideoMode({ tex.getSize().x, tex.getSize().y }), "SFML works!", sf::Style::Close);
    sf::WindowHandle wh = window.getNativeHandle();
    CreateMenu();
    while (window.isOpen() && !kill)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
