#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.gpp>
#include <SFML/Vector2.hpp>
#include <string>
#include <vector>

#include "TextureMap.h"

class Actor;

struct pain {
    int raw_dmg;
    CollideType direction;
    Actor *attacker;
    int knockback
};

class Actor
{
public:
    Actor(sf::Vector2i pos, sf::Vector2i scale, std::string image_name);
    virtual ~Actor();

    virtual void update(int delta) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void hurt(pain p);

    sf::Rect<int> get_rect() const;
    void set_rect(sf::Rect<int>& x);

    sf::Vector2f get_velocity() const;
    void set_velocity(sf::Vector2f vel);
private:
    sf::Vector2f velocity;
    sf::Rect<int> rect;

    sf::Texture *tex;
    std::string texture_name;
    std::vector<sf::Sprite> sprites

    TextureMap my_map;
};

#endif // ACTOR_H
