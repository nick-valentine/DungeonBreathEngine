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
    constexpr static double accel_x = 1.5;
    constexpr static double accel_y = 1.5;

    constexpr static double vel_damp = 10.f;

    constexpr static int anim_speed = 10;

    sf::Vector2f acceleration;

    int active_sprite = 0;
    int update_count = 0;
};

#endif //HERO_H
