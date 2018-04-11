#include "Hero.h"

Hero::Hero(sf::Vector2i pos, sf::Vector2i scale) :
    Actor(pos, scale),
    dir(down),
    act(idle),
    current_animation(nullptr),
    walk_forwards(TextureMap::request(sprite_sheet)),
    walk_backwards(TextureMap::request(sprite_sheet))
{
    walk_forwards.add_sprite(sf::IntRect(0, 0, 1, 2));
    walk_forwards.add_sprite(sf::IntRect(1, 0, 1, 2));
    walk_forwards.add_sprite(sf::IntRect(2, 0, 1, 2));
    walk_forwards.add_sprite(sf::IntRect(3, 0, 1, 2));

    walk_backwards.add_sprite(sf::IntRect(0, 2, 1, 2));
    walk_backwards.add_sprite(sf::IntRect(1, 2, 1, 2));
    walk_backwards.add_sprite(sf::IntRect(2, 2, 1, 2));
    walk_backwards.add_sprite(sf::IntRect(3, 2, 1, 2));
}

Hero::~Hero()
{
}

void Hero::update(int delta, Logger *logger)
{
    sf::Vector2f vel(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x = velocity;
        dir = right;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x = -velocity;
        dir = left;
    } else {
        vel.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        vel.y = -velocity;
        dir = up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        vel.y = velocity;
        dir = down;
    } else {
        vel.y = 0;
    }

    this->set_velocity(vel);

    switch (dir) {
    case up:
        current_animation = &walk_backwards;
        break;
    case down:
        current_animation = &walk_forwards;
        break;
    default:
        current_animation = &walk_forwards;
    }

    if (vel.x == 0 && vel.y == 0) {
        act = idle;
        current_animation->pause();
    } else {
        act = walking;
        current_animation->play();
    }

    current_animation->update(delta);
    Actor::update(delta, logger);
}

void Hero::draw(sf::RenderWindow &window)
{
    current_animation->draw(window, this->get_rect());
    //walk_forwards.draw(window, this->get_rect());
}

void Hero::hurt(pain p)
{
}

Actor *Hero::clone()
{
    Hero *temp = new Hero(*this);
    return temp;
}
