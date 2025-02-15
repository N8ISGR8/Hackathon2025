#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1200,900 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Load a sprite to display
    const sf::Texture texture("Assets/cute_image.jpg");
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    const sf::Font font("Assets/ARIAL.TTF");
    sf::Text text(font, "Hello SFML", 50);
    text.setFillColor(sf::Color::Black);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    return 0;
}