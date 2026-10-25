#include <iostream>
#include "ColorPaletteManager.h"

int main()
{
    sf::Vector2u windowSize{ 1200, 800 };
    std::string fontPath{ "fonts/arial.ttf" };

    sf::RenderWindow window(sf::VideoMode(windowSize), "Different Color Palettes", sf::Style::Titlebar | sf::Style::Close);

    const sf::Event::KeyPressed* keyEvent;

    ColorPaletteManager manager(windowSize, fontPath);

    sf::Clock clock;
    float deltaTime = 0.f;
    
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            manager.processEvent(event);
            if (event->is<sf::Event::Closed>())
                window.close();
            if (keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyEvent->code)
                {
                case (sf::Keyboard::Key::Escape):
                    window.close();
                    break;
                }
            }
        }
        deltaTime = clock.reset().asMilliseconds();

        manager.onUpdate(deltaTime);

        window.clear(sf::Color::White);
        window.draw(manager);
        window.display();
    }
}