#include "Hero.h"

Hero::Hero(sf::Vector2i pos, sf::Vector2i scale) : Actor(pos, scale, "./GameData/img/Hero.png")
{
    this->add_sprite(sf::IntRect(0, 0, 100, 100));
    this->add_sprite(sf::IntRect(100, 0, 100, 100));
    this->add_sprite(sf::IntRect(0, 100, 100, 100));
}

Hero::~Hero()
{
}

void Hero::update(int delta, Logger *logger)
{
    sf::Vector2f vel(0,0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        vel.x = velocity;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        vel.x = -velocity;
    } else {
        vel.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        vel.y = -velocity;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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
        spr->setScale(get_rect().width / 100.0, get_rect().height / 100.0);
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
