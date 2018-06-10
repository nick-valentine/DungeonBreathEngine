#ifndef DYNAMICTILE_H
#define DYNAMICTILE_H

#include "Tile.h"
#include "render/Macros.h"
#include "SpriteSet.h"
#include "Animation.h"

namespace render {
    typedef int TileType;

    class DynamicTile : public Tile
    {
    public:
        DynamicTile(int key, sf::Texture *tex, sf::Vector2i size_mod = sf::Vector2i(1,1), int anim_speed = 1, int base_size = 16);
        void add_frame(sf::IntRect pos);

        sf::Vector2i get_location();
        void set_location(sf::Vector2i loc);

        virtual void play();
        virtual void pause();
        virtual void reset();

        virtual int get_key();
        virtual sf::Vector2i get_size();
        virtual void set_scale(sf::Vector2f scale);
        virtual void set_origin(sf::Vector2f scale);

        void update(int delta);
        void draw(sf::RenderWindow &window);

        Tile *clone();
    private:
        Animation anim;
        sf::Vector2i loc;
        sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
        sf::Vector2i size_mod;
        int key;
    };
};

#endif //DYNAMICTILE_H
