#include "Actor.h"

Actor::Actor(sf::Vector2i pos, sf::Vector2i scale)
{
    this->rect = sf::Rect<int>(pos.x, pos.y, scale.x, scale.y);
    this->velocity = sf::Vector2f(0, 0);
}

Actor::~Actor()
{
}

void Actor::update(int delta, Logger *logger)
{
    this->rect.left += this->velocity.x;
    this->rect.top += this->velocity.y;
}

void Actor::hurt(pain p)
{

}

sf::Rect<int> Actor::get_rect() const
{
        return this->rect;
}

void Actor::set_rect(sf::Rect<int>& x)
{
    this->rect = x;
}

sf::Vector2f Actor::get_velocity() const
{
    return this->velocity;
}

void Actor::set_velocity(sf::Vector2f vel)
{
    this->velocity = vel;
}
