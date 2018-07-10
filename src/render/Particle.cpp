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
        srand( time(NULL) );
    }

    ParticleEffect::~ParticleEffect()
    {
        for (auto i = 0; i < particles.size(); ++i) {
            delete particles[i];
        }
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
            particles[i]->die_in -= delta;
            if (particles[i]->die_in <= 0) {
                kill_particle(i);
                i--;
                continue;
            }
            particles[i]->vel += particles[i]->accel;
            particles[i]->p->move(particles[i]->vel);
        }
        accumulator += delta;
        if (accumulator > get_rand(spawn_rate, spawn_rate_randomness)) {
            accumulator = 0;
            spawn_particle();
        }
    }

    void ParticleEffect::draw(sf::RenderTarget &window)
    {
        for (const auto &i : particles) {
            window.draw(*i->p);
        }
    }

    float ParticleEffect::get_rand(float center, float range)
    {
        if (range == 0) {
            return center;
        }
        const float resolution = 10000.f;
        center *= resolution;
        range *= resolution;
        int modifier = rand() % (int)(range * 2);
        modifier -= range;

        return (modifier + center) / resolution;
    }

    void ParticleEffect::spawn_particle()
    {
        auto p = get_particle();
        p->die_in = get_rand(lifetime, lifetime_randomness);
        p->vel = sf::Vector2f(
            get_rand(velocity.x, velocity_randomness.x),
            get_rand(velocity.y, velocity_randomness.y)
        );
        p->accel = sf::Vector2f(
            get_rand(acceleration.x, acceleration_randomness.x),
            get_rand(acceleration.y, acceleration_randomness.y)
        );
        auto h = sprites.make_sprite(sprite_pos);
        p->p = sprites.get_sprite(h);
        p->p->setPosition(pos.x, pos.y);
        this->particles.push_back(p);
    }

    void ParticleEffect::kill_particle(size_t i)
    {
        dead.push_back(particles[i]);
        if (particles.size() > 1) {
            particles[i] = particles[particles.size()-1];
        }
        particles.pop_back();
    }

    particle *ParticleEffect::get_particle()
    {
        if (dead.size() > 0) {
            auto p = dead[dead.size() - 1];
            dead.pop_back();
            return p;
        }
        return new particle;
    }
};
