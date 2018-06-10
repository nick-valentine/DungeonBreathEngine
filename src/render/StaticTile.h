#ifndef STATICTILE_H
#define STATICTILE_H

#include "Tile.h"

namespace render {
    class StaticTile : public Tile
    {
    public:
        StaticTile(int key, sf::Sprite sprite);

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
        sf::Sprite sprite;
        int key;
    };
};

#endif // STATICTILE_H
