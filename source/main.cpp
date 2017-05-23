#include <SFML/Graphics.hpp>

#include "../headers/ConfigLoader.h"

void handleEvents(sf::RenderWindow &window);

int main()
{
    ConfigLoader::load();
    int resolutionX = ConfigLoader::getIntOption("resolutionX", 200);
    int resolutionY = ConfigLoader::getIntOption("resolutionY", 200);
    const int frameFrequency = 33333; // 1/30 of a second

    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Zelda Clone");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock timer;

    float delta = 0.0;
    while (window.isOpen()) {

        delta = timer.restart().asMicroseconds();
        sf::sleep(sf::microseconds(std::max(frameFrequency - delta, 0.0f)));

        handleEvents(window);

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }

    return 0;
}

void handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
