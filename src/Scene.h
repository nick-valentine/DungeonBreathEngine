#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Logger.h"
#include "Input.h"

class Scene
{
public:
    enum Status {
        nothing,
        exit_program,
        switch_scene
    };

    Scene(sf::Vector2i size);
    virtual ~Scene();

    virtual void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    virtual Status status() = 0;
    virtual Scene *new_scene() = 0;
protected:
    sf::Vector2i size;
};

#endif // SCENE_H
