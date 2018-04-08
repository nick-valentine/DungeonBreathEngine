#include "Hero.h"

Hero::Hero(sf::Vector2i pos, sf::Vector2i scale) : Actor(pos, scale, "./GameData/img/Hero.png")
{
    this->add_sprite(sf::IntRect(0, 0, 100, 100));
    this->add_sprite(sf::IntRect(100, 0, 100, 100));
    this->add_sprite(sf::IntRect(0, 100, 100, 100));

    this->acceleration = sf::Vector2f(0.f, 0.f);
}

Hero::~Hero()
{
}

void Hero::update(int delta, Logger *logger)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->acceleration.x = accel_x;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->acceleration.x = -accel_x;
    } else {
        this->acceleration.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->acceleration.y = -accel_y;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->acceleration.y = accel_y;
    } else {
        this->acceleration.y = 0;
    }

    auto vel = this->get_velocity();
    vel = vel + this->acceleration;
    vel.x = vel.x - (vel.x / vel_damp);
    vel.y = vel.y - (vel.y / vel_damp);

    if ((vel.x < 1 && vel.x > 0) ||
        (vel.x > -1 && vel.x < 0))  {
        vel.x = 0;
    }

    if ((vel.y < 1 && vel.y > 0) ||
        (vel.y > -1 && vel.y < 0)) {
        vel.y = 0;
    }

    logger->info("hero velocity: %d, %d", vel.x, vel.y);
    this->set_velocity(vel);

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
