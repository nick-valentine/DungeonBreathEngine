#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "SpriteSet.h"

class Animation
{
public:
    enum State {
        playing,
        paused
    };

    Animation(sf::Texture *tex, int anim_speed = 1, int base_size = 16);
    void add_sprite(sf::IntRect pos);

    void play();
    void pause();
    void reset();

    void update(int delta);
    void draw(sf::RenderWindow &window, sf::IntRect pos);
private:
    constexpr static int base_speed = 10000;
    SpriteSet frames;
    int anim_speed = 0;
    int current_frame = 0;
    int accumulator = 0;
    State state = playing;
};

#endif // ANIMATION_H
