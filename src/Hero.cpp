#include "Hero.h"

Hero::Hero(sf::Vector2i pos, sf::Vector2i scale) :
    Actor(pos, scale),
    dir(down),
    act(idle),
    walk_forwards(TextureMap::request(sprite_sheet)),
    walk_backwards(TextureMap::request(sprite_sheet)),
    walk_left(TextureMap::request(sprite_sheet)),
    walk_right(TextureMap::request(sprite_sheet)),
    current_animation(&walk_forwards)
{
    walk_forwards.add_sprite(sf::IntRect(0, 0, 1, 2));
    walk_forwards.add_sprite(sf::IntRect(1, 0, 1, 2));
    walk_forwards.add_sprite(sf::IntRect(2, 0, 1, 2));
    walk_forwards.add_sprite(sf::IntRect(3, 0, 1, 2));

    walk_right.add_sprite(sf::IntRect(0, 2, 1, 2));
    walk_right.add_sprite(sf::IntRect(1, 2, 1, 2));
    walk_right.add_sprite(sf::IntRect(2, 2, 1, 2));
    walk_right.add_sprite(sf::IntRect(3, 2, 1, 2));

    walk_backwards.add_sprite(sf::IntRect(0, 4, 1, 2));
    walk_backwards.add_sprite(sf::IntRect(1, 4, 1, 2));
    walk_backwards.add_sprite(sf::IntRect(2, 4, 1, 2));
    walk_backwards.add_sprite(sf::IntRect(3, 4, 1, 2));

    walk_left.add_sprite(sf::IntRect(0, 6, 1, 2));
    walk_left.add_sprite(sf::IntRect(1, 6, 1, 2));
    walk_left.add_sprite(sf::IntRect(2, 6, 1, 2));
    walk_left.add_sprite(sf::IntRect(3, 6, 1, 2));
}

Hero::~Hero()
{
}

void Hero::update(int delta, Input *input, Logger *logger)
{
    sf::Vector2f vel(0,0);
    Facing face;
    if (input->is_key_pressed(Input::Key::right)) {
        vel.x = velocity;
        face = right;
    } else if (input->is_key_pressed(Input::Key::left)) {
        vel.x = -velocity;
        face = left;
    } else {
        vel.x = 0;
    }

    if (input->is_key_pressed(Input::Key::up)) {
        vel.y = -velocity;
        face = up;
    } else if (input->is_key_pressed(Input::Key::down)) {
        vel.y = velocity;
        face = down;
    } else {
        vel.y = 0;
    }

    change_state(face, act);
    this->set_velocity(vel);
    this->set_animation();

    if (vel.x == 0 && vel.y == 0) {
        change_state(dir, idle);
    } else {
        change_state(dir, walking);
    }

    current_animation->update(delta);
    Actor::update(delta, input, logger);
}

void Hero::draw(sf::RenderWindow &window)
{
    current_animation->draw(window, this->get_rect());
}

void Hero::hurt(pain p)
{
}

Actor *Hero::clone()
{
    Hero *temp = new Hero(*this);
    return temp;
}

void Hero::set_animation()
{
    switch (dir) {
    case up:
        current_animation = &walk_backwards;
        break;
    case right:
        current_animation = &walk_right;
        break;
    case down:
        current_animation = &walk_forwards;
        break;
    case left:
        current_animation = &walk_left;
        break;
    default:
        current_animation = &walk_forwards;
    }
}

void Hero::change_state(Facing f, Action a)
{
    static Facing last_f;
    static Action last_a;
    if (f != last_f || a != last_a) {
        current_animation->reset();
    }

    if (a == idle) {
        current_animation->pause();
    } else {
        current_animation->play();
    }

    last_f = dir;
    last_a = act;

    dir = f;
    act = a;
}
