#include "TileSet.h"

namespace render {

    TileSet::TileSet(std::string def_file)
    {
        std::string filename = TILESETDIR;
        filename += def_file + ".txt";
        std::ifstream ifile(filename);
        if (!ifile.good()) {
            throw new core::FileNotFoundException();
        }
        ifile >> this->name;
        std::string key;
        ifile >> key;
        while (key != "---") {
            if (key == "size") {
                ifile >> base_size;
            } else if (key == "tex") {
                std::string tex_name = "";
                ifile >> tex_name;
                std::string filename = IMGDIR;
                filename += tex_name;
                tex = TextureMap::request(filename);
            } else if (key == "anim_speed") {
                ifile >> anim_speed;
            }
            ifile >> key;
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
                TileSet::make_dynamic(label, positions, sf::Vector2i(width, height), anim_speed);
            }
        }
        ifile.close();
        
    }

    TileSet::TileSet(sf::Texture *tex, int base_size) : tex(tex), base_size(base_size), tiles()
    {
    }

    TileSet::~TileSet()
    {
    }

    std::string TileSet::get_name() const
    {
        return this->name;
    }

    TileType TileSet::make_static(int key, sf::Vector2i pos, sf::Vector2i size_mod)
    {
        SpriteSet ss(tex, base_size);
        auto t = ss.make_sprite(pos, size_mod);
        tiles[key] = std::unique_ptr<Tile>(new StaticTile(key, *ss.get_sprite(t)));
        return tiles.size() - 1;
    }

    TileType TileSet::make_dynamic(int key, std::vector<sf::Vector2i> pos, sf::Vector2i size_mod, int anim_speed)
    {
        DynamicTile *dt = new DynamicTile(key, tex, size_mod, anim_speed, this->base_size);
        for (auto &p: pos){
            dt->add_frame(sf::IntRect(p.x, p.y, size_mod.x, size_mod.y));
        }
        tiles[key] = std::unique_ptr<Tile>(dt);
        return tiles.size() - 1;
    }

    Tile *TileSet::spawn(TileType t, sf::Vector2i loc)
    {
        auto tile = tiles[t]->clone();
        tile->set_location(loc);
        return tile;
    }

    std::vector<int> TileSet::get_keys() const
    {
        std::vector<int> keys;
        for (const auto &i : tiles) {
            keys.push_back(i.first);
        }
        return keys;
    }
}
