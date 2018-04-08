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

int Actor::add_sprite(sf::IntRect pos)
{
    sf::Sprite temp;
    temp.setTexture(*tex);
    temp.setTextureRect(pos);
    this->sprites.push_back(temp);
    return sprites.size() - 1;
}

sf::Sprite *Actor::get_sprite(int index)
{
    return &this->sprites[index];
}

int Actor::get_num_sprites() const
{
    return this->sprites.size();
}
