#include "Hero.h"

Hero::Hero(sf::Vector2i pos, sf::Vector2i scale) : Actor(pos, scale, "./GameData/img/character.png")
{
    constexpr int sprite_width = 16;
    this->add_sprite(sf::IntRect(sprite_width * 0, 0, sprite_width, 30));
    this->add_sprite(sf::IntRect(sprite_width * 1, 0, sprite_width, 30));
    this->add_sprite(sf::IntRect(sprite_width * 2, 0, sprite_width, 30));
    this->add_sprite(sf::IntRect(sprite_width * 3, 0, sprite_width, 30));
}

Hero::~Hero()
{
}

void Hero::update(int delta, Logger *logger)
{
    sf::Vector2f vel(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x = velocity;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x = -velocity;
    } else {
        vel.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        vel.y = -velocity;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        vel.y = velocity;
    } else {
        vel.y = 0;
    }

    this->set_velocity(vel);

    logger->info("hero velocity: %1.1f, %1.1f", vel.x, vel.y);

    this->update_count++;
    if (this->update_count > anim_speed) {
        this->update_count = 0;
        this->active_sprite = (this->active_sprite + 1) % this->get_num_sprites();
    }

    Actor::update(delta, logger);
}

void Hero::draw(sf::RenderWindow &window)
{
    if (active_sprite != -1) {
        auto spr = get_sprite(active_sprite);
        spr->setPosition(get_rect().left, get_rect().top);
        spr->setScale(get_rect().width / scale_modifier, get_rect().height / scale_modifier);
        window.draw(*spr);
    }
}

void Hero::hurt(pain p)
{
}

Actor *Hero::clone()
{
    Hero *temp = new Hero(*this);
    return temp;
}
