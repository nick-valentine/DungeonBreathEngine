#ifndef HERO_H
#define HERO_H

#include "Actor.h"
#include "Logger/Logger.h"

class Hero : public Actor
{
public:
    Hero(sf::Vector2i pos, sf::Vector2i scale);
    ~Hero();

    void update(int delta, Logger *logger);
    void draw(sf::RenderWindow &window);
    void hurt(pain p);

    Actor *clone();

private:
    constexpr static float velocity = 5.0;
    constexpr static int anim_speed = 10;
    constexpr static float scale_modifier = 25.0;

    int active_sprite = 0;
    int update_count = 0;
};

#endif //HERO_H
