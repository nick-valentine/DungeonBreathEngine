#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>

#include "Logger/Logger.h"
#include "TextureMap.h"
#include "Input.h"

class Actor;

struct pain {
    int raw_dmg;
    sf::Vector2f force;
    Actor *attacker;
};

class Actor
{
public:
    Actor(sf::Vector2i pos, sf::Vector2i scale);
    virtual ~Actor();

    virtual void update(int delta, Input *input, Logger *logger);
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void hurt(pain p);

    sf::Rect<int> get_rect() const;
    void set_rect(sf::Rect<int>& x);

    sf::Vector2f get_velocity() const;
    void set_velocity(sf::Vector2f vel);

    virtual Actor *clone() = 0;
private:
    sf::Vector2f velocity;
    sf::Rect<int> rect;
};

#endif // ACTOR_H
