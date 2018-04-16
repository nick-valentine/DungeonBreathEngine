#ifndef HERO_H
#define HERO_H

#include "Actor.h"
#include "Animation.h"
#include "SpriteSet.h"
#include "Logger/Logger.h"

class Hero : public Actor
{
public:
    enum Facing {
        up = 0,
        down,
        left,
        right
    };

    enum Action {
        idle = 0,
        walking,
        running
    };

    Hero(sf::Vector2i pos, sf::Vector2i scale);
    ~Hero();

    void update(int delta, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);
    void hurt(pain p);

    Actor *clone();

private:
    const char *sprite_sheet = "./GameData/img/character.png";
    constexpr static float velocity = 5.0;
    constexpr static int anim_speed = 10;
    constexpr static float scale_modifier = 25.0;

    void change_state(Facing f, Action a);
    inline void set_animation();

    Facing dir;
    Action act;

    Animation *current_animation;
    Animation walk_forwards;
    Animation walk_backwards;
    Animation walk_left;
    Animation walk_right;
};

#endif //HERO_H
