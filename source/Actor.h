#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>

#include "Logger/Logger.h"
#include "TextureMap.h"

class Actor;

struct pain {
    int raw_dmg;
    sf::Vector2f force;
    Actor *attacker;
};

class Actor
{
public:
    Actor(sf::Vector2i pos, sf::Vector2i scale, std::string image_name);
    virtual ~Actor();

    virtual void update(int delta, Logger *logger);
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void hurt(pain p);

    sf::Rect<int> get_rect() const;
    void set_rect(sf::Rect<int>& x);

    sf::Vector2f get_velocity() const;
    void set_velocity(sf::Vector2f vel);

    virtual Actor *clone() = 0;
protected:
    int add_sprite(sf::IntRect pos);
    sf::Sprite *get_sprite(int index);
    int get_num_sprites() const;
private:
    sf::Vector2f velocity;
    sf::Rect<int> rect;

    sf::Texture *tex;
    std::string texture_name;
    std::vector<sf::Sprite> sprites;
};

#endif // ACTOR_H
