#include "Particle.h"

namespace render {
    ParticleEffect::ParticleEffect(
        sf::Texture *tex, int base_size,
        sf::Vector2i sprite_pos,
        sf::Vector2i pos,
        sf::Vector2f velocity,
        sf::Vector2f velocity_randomness,
        sf::Vector2f acceleration,
        sf::Vector2f acceleration_randomness,
        float lifetime,
        float lifetime_randomness,
        float spawn_rate,
        float spawn_rate_randomness
    ) : sprites(tex, base_size),
        pos(pos),
        sprite_pos(sprite_pos),
        velocity(velocity),
        velocity_randomness(velocity_randomness),
        acceleration(acceleration),
        acceleration_randomness(acceleration_randomness),
        lifetime(lifetime),
        lifetime_randomness(lifetime_randomness),
        spawn_rate(spawn_rate),
        spawn_rate_randomness(spawn_rate_randomness)
    {

    }

    void ParticleEffect::set_location(sf::Vector2i loc)
    {
        this->pos = loc;
    }

    sf::Vector2i ParticleEffect::get_location()
    {
        return this->pos;
    }

    void ParticleEffect::update(int delta)
    {
        for (size_t i = 0; i < particles.size(); ++i) {
            particles[i].vel += particles[i].accel;
            particles[i].p->move(particles[i].vel);
        }
    }

    void ParticleEffect::draw(sf::RenderWindow &window)
    {
        for (const auto &i : particles) {
            window.draw(*i.p);
        }
    }
};
