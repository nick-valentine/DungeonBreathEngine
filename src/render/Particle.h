#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "SpriteSet.h"
#include <time.h>
#include "core.h"

namespace render {
    
    struct particle
    {
        int die_in;
        sf::Vector2f vel;
        sf::Vector2f accel;
        sf::Sprite *p;
    };

    class ParticleEffect
    {
    public:
        ParticleEffect(
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
        );
        ~ParticleEffect();

        void set_location(sf::Vector2i loc);
        sf::Vector2i get_location();

        void update(int delta);
        void draw(sf::RenderWindow &window);
    private:
        SpriteSet sprites;
        std::vector<particle*> particles = std::vector<particle*>();
        std::vector<particle*> dead = std::vector<particle*>();

        float get_rand(float center, float range);
        void spawn_particle();
        void kill_particle(size_t i);
        particle *get_particle();

        sf::Vector2i pos;
        sf::Vector2i sprite_pos;

        sf::Vector2f velocity;
        sf::Vector2f velocity_randomness;
        sf::Vector2f acceleration;
        sf::Vector2f acceleration_randomness;
        float lifetime;
        float lifetime_randomness;
        float spawn_rate;
        float spawn_rate_randomness;

        int accumulator;
    };
};

#endif //PARTICLE_H
