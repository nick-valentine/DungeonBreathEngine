#include "Actor.h"

Actor::Actor(sf::Vector2i pos, sf::Vector2i scale, std::string image_name)
{
    this->rect = sf::Rect<int>(pos.x, pos.y, scale.x, scale.y);
    this->velocity = sf::Vector2f(0, 0);
    this->texture_name = image_name;
    this->tex = my_map.request(image_name);
}

Actor::~Actor()
{
}

void Actor::hurt(pain p)
{

}
