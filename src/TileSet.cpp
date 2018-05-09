#include "TileSet.h"

StaticTile::StaticTile(sf::Sprite sprite) : Tile()
{
    this->sprite = sprite;
    this->sprite.setScale(Tile::scale, Tile::scale);
}

void StaticTile::set_location(sf::Vector2i loc)
{
    this->sprite.setPosition(loc.x, loc.y);
}

void StaticTile::update(int delta)
{

}

void StaticTile::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

Tile *StaticTile::clone()
{
    StaticTile *temp = new StaticTile(*this);
    return temp;
}

DynamicTile::DynamicTile(sf::Texture *tex, sf::Vector2i size_mod) : 
    Tile(), anim(tex), loc(sf::Vector2i(0,0)), size_mod(size_mod)
{

}

void DynamicTile::add_frame(sf::IntRect pos)
{
    anim.add_sprite(pos);
}

void DynamicTile::set_location(sf::Vector2i loc)
{
    this->loc = loc;
}

void DynamicTile::update(int delta)
{
    anim.update(delta);
}

void DynamicTile::draw(sf::RenderWindow &window)
{
    anim.draw(window, sf::IntRect(loc.x, loc.y, Tile::size(), Tile::size()));
}

Tile *DynamicTile::clone()
{
    DynamicTile *temp = new DynamicTile(*this);
    return temp;
}

TileSet::TileSet(sf::Texture *tex, int base_size) : tex(tex), base_size(base_size), tiles()
{
}

TileSet::~TileSet()
{
    for (size_t i = 0; i < tiles.size(); ++i) {
        delete tiles[i];
    }
}

TileType TileSet::make_static(sf::Vector2i pos, sf::Vector2i size_mod)
{
    SpriteSet ss(tex, base_size);
    auto t = ss.make_sprite(pos, size_mod);
    tiles.push_back(new StaticTile(*ss.get_sprite(t)));
    return tiles.size() - 1;
}

TileType TileSet::make_dynamic(std::vector<sf::Vector2i> pos, sf::Vector2i size_mod)
{
    DynamicTile *dt = new DynamicTile(tex, size_mod);
    for (auto &p: pos){
        dt->add_frame(sf::IntRect(p.x, p.y, size_mod.x, size_mod.y));
    }
    tiles.push_back(dt);
    return tiles.size() - 1;
}

Tile *TileSet::spawn(TileType t, sf::Vector2i loc)
{
    auto tile = tiles[t]->clone();
    tile->set_location(loc);
    return tile;
}

std::unique_ptr<TileSet> TileSets::overworld()
{
    std::unique_ptr<TileSet> ts(new TileSet(TextureMap::request(IMGDIR "/Overworld.png")));
    ts->make_static(sf::Vector2i(0,0)); //grass thick
    ts->make_static(sf::Vector2i(0, 3), sf::Vector2i(2, 2)); //grass to thick
    ts->make_static(sf::Vector2i(1, 3), sf::Vector2i(2, 2));
    ts->make_static(sf::Vector2i(0, 4), sf::Vector2i(2, 2));
    ts->make_static(sf::Vector2i(1, 4), sf::Vector2i(2, 2));
    ts->make_static(sf::Vector2i(0, 6)); //thick to grass
    ts->make_static(sf::Vector2i(1, 6));
    ts->make_static(sf::Vector2i(0, 7));
    ts->make_static(sf::Vector2i(1, 7));
    ts->make_static(sf::Vector2i(2, 6), sf::Vector2i(2, 2)); //thick to water
    ts->make_static(sf::Vector2i(3, 6), sf::Vector2i(2, 2));
    ts->make_static(sf::Vector2i(2, 7), sf::Vector2i(2, 2));
    ts->make_static(sf::Vector2i(3, 7), sf::Vector2i(2, 2));
    ts->make_static(sf::Vector2i(3, 6)); //thick to water t
    ts->make_static(sf::Vector2i(2, 7)); // l
    ts->make_static(sf::Vector2i(4, 7)); // r
    ts->make_static(sf::Vector2i(3, 8)); // b
    ts->make_static(sf::Vector2i(3, 9)); // water to thick
    ts->make_static(sf::Vector2i(2, 10));
    ts->make_static(sf::Vector2i(3, 10));
    ts->make_static(sf::Vector2i(4, 1), sf::Vector2i(2, 2));
    ts->make_dynamic(
        std::vector<sf::Vector2i>{
            sf::Vector2i(0,1),
            sf::Vector2i(1,1),
            sf::Vector2i(2,1),
            sf::Vector2i(3,1),
            sf::Vector2i(0,2),
            sf::Vector2i(1,2),
            sf::Vector2i(2,2),
            sf::Vector2i(3,2),
        }
    );
    ts->make_dynamic(
        std::vector<sf::Vector2i>{
            sf::Vector2i(3, 3),
            sf::Vector2i(4, 3),
            sf::Vector2i(5, 3),
            sf::Vector2i(3, 4),
            sf::Vector2i(4, 4),
            sf::Vector2i(5, 4),
        }
    );

    return ts;
}
