#include "Window.h"
#include <SFML/Graphics.hpp>

void WindowRun(std::string imageContent, bool& kill)
{
    sf::MemoryInputStream mis = sf::MemoryInputStream(imageContent.c_str(), imageContent.size());

    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "SFML works!");
    sf::Texture tex = sf::Texture(sf::Image(mis));
    sf::Sprite sprite(tex);
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
