#include "TileSet.h"

#define NUM_VALUEPAIRS 2

StaticTile::StaticTile(sf::Sprite sprite) : Tile()
{
    this->sprite = sprite;
    this->sprite.setScale(Tile::scale, Tile::scale);
}

void StaticTile::set_location(sf::Vector2i loc)
{
    this->sprite.setPosition(loc.x, loc.y);
}

void StaticTile::play()
{

}

void StaticTile::pause()
{

}

void StaticTile::reset()
{

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

DynamicTile::DynamicTile(sf::Texture *tex, sf::Vector2i size_mod, int anim_speed, int base_size) : 
    Tile(), anim(tex, anim_speed, base_size), loc(sf::Vector2i(0,0)), size_mod(size_mod)
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

void DynamicTile::play()
{
	anim.play();
}

void DynamicTile::pause()
{
	anim.pause();
}

void DynamicTile::reset()
{
	anim.reset();
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

TileSet::TileSet(std::string def_file)
{
	std::string filename = TILESETDIR;
	filename += def_file + ".txt";
	std::ifstream ifile(filename);
	if (!ifile.good()) {
		throw new FileNotFoundException();
	}
	ifile >> this->name;
	std::string key;
	for (int i = 0; i < NUM_VALUEPAIRS; ++i) {
		ifile >> key;
		if (key == "size") {
			ifile >> base_size;
		} else if (key == "tex") {
			std::string tex_name = "";
			ifile >> tex_name;
			std::string filename = IMGDIR;
			filename += tex_name;
			tex = TextureMap::request(filename);
		}
	}
	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		std::stringstream ss(line + "\n");
		int label = 0, x = 0, y = 0, width = 0, height = 0;
		ss >> label >> x >> y >> width >> height;
		std::vector<sf::Vector2i> positions;
		while (ss.good()) {
			positions.push_back(sf::Vector2i(x, y));

			ss >> x >> y >> width >> height;
		}
		if (positions.size() == 1) {
			auto pos = positions[0];
			TileSet::make_static(label, pos, sf::Vector2i(width, height));
		} else if (positions.size() > 1) {
			TileSet::make_dynamic(label, positions, sf::Vector2i(width, height), 1);
		}
	}
	ifile.close();
	
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

std::string TileSet::get_name() const
{
	return this->name;
}

TileType TileSet::make_static(int key, sf::Vector2i pos, sf::Vector2i size_mod)
{
    SpriteSet ss(tex, base_size);
    auto t = ss.make_sprite(pos, size_mod);
    tiles[key] = new StaticTile(*ss.get_sprite(t));
    return tiles.size() - 1;
}

TileType TileSet::make_dynamic(int key, std::vector<sf::Vector2i> pos, sf::Vector2i size_mod, int anim_speed)
{
    DynamicTile *dt = new DynamicTile(tex, size_mod, anim_speed, this->base_size);
    for (auto &p: pos){
        dt->add_frame(sf::IntRect(p.x, p.y, size_mod.x, size_mod.y));
    }
    tiles[key] = dt;
    return tiles.size() - 1;
}

Tile *TileSet::spawn(TileType t, sf::Vector2i loc)
{
    auto tile = tiles[t]->clone();
    tile->set_location(loc);
    return tile;
}
