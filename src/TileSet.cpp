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
		std::vector<sf::IntRect> positions;
		while (ss.good()) {
			positions.push_back(sf::IntRect(x, y, width, height));

			ss >> x >> y >> width >> height;
		}
		if (positions.size() == 1) {
			auto pos = positions[0];
			sf::Sprite temp;
			temp.setTexture(*tex);
			temp.setTextureRect(sf::IntRect(
				pos.left * base_size,
				pos.top * base_size,
				base_size * pos.width,
				base_size * pos.height
			));
			tiles[label] = new StaticTile(temp);
		} else if (positions.size() > 1) {
			auto size_mod_x = positions[0].width;
			auto size_mod_y = positions[0].height;
			auto temp = new DynamicTile(tex, sf::Vector2i(size_mod_x, size_mod_y));
			for (const auto &pos : positions) {
				temp->add_frame(pos);
			}
			tiles[label] = temp;
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

TileType TileSet::make_dynamic(int key, std::vector<sf::Vector2i> pos, sf::Vector2i size_mod)
{
    DynamicTile *dt = new DynamicTile(tex, size_mod);
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
