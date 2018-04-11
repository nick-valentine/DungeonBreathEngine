#include "Animation.h"

Animation::Animation(sf::Texture *tex, int anim_speed) :
    frames(tex), anim_speed(anim_speed * base_speed)
{

}

void Animation::add_sprite(sf::IntRect pos_and_size)
{
    this->frames.make_sprite(sf::Vector2i(pos_and_size.left, pos_and_size.top), sf::Vector2i(pos_and_size.width, pos_and_size.height));
}

void Animation::play()
{
    this->state = playing;
}

void Animation::pause()
{
    this->state = paused;
}

void Animation::reset()
{
    this->current_frame = 0;
}

void Animation::update(int delta)
{
    if (this->state == paused) {
        return;
    }
    this->accumulator += delta;
    if (this->accumulator > this->anim_speed) {
        this->current_frame = (this->current_frame + 1) % this->frames.size();
        this->accumulator = 0;
    }
}

void Animation::draw(sf::RenderWindow &window, sf::IntRect pos)
{
    auto spr = frames.get_sprite(current_frame);
    spr->setPosition(pos.left, pos.top);
    spr->setScale(pos.width, pos.height);
    window.draw(*spr);
}
