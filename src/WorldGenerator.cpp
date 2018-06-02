#include "WorldGenerator.h"

#include <iostream>

WorldLoader::WorldLoader(std::string file_name) : WorldGenerator(), file_name(file_name)
{

}

Dimension::Room WorldLoader::generate(std::string tile_set)
{
    auto world = Dimension::Room();
    std::ifstream ifile(file_name.c_str());
    if (!ifile.good()) {
        throw FileNotFoundException();
    }
    std::string name, f_tileset;
    std::getline(ifile, name);
    std::getline(ifile, f_tileset);
    ifile>>size.x>>size.y;
    TileSet tileset(f_tileset);
    this->tile_set = f_tileset;
    while (ifile.good()) {
        world.push_back(spawn_layer(ifile, tileset));
    }
    ifile.close();
    return world;
}

std::string WorldLoader::get_name()
{
    std::ifstream ifile(file_name.c_str());
    if (!ifile.good()) {
        throw FileNotFoundException();
    }
    std::string name;
    std::getline(ifile, name);
    ifile.close();
    return name;
}

std::string WorldLoader::get_filename()
{
    return this->file_name;
}

std::string WorldLoader::get_tileset()
{
    return this->tile_set;
}

sf::Vector2i WorldLoader::get_size()
{
    return this->size;
}

Dimension::Layer WorldLoader::spawn_layer(std::ifstream &ifile, TileSet &tile_set)
{
    std::string line;
    Dimension::Layer layer;
    std::getline(ifile, line);
    int line_number = 0;
    while (ifile.good() && line != "---") {
        layer.push_back(Dimension::Line());
        std::stringstream ss(line);
        int tile;
        ss>>tile;
        int col_number = 0;
        while (ss.good()) {
            if (tile == -1) {
                layer[line_number].push_back(Dimension::TilePtr(nullptr));
            } else {
                layer[line_number].push_back(
                    Dimension::TilePtr(tile_set.spawn(
                        tile,
                        sf::Vector2i(
                            col_number * TileSet::tile_size(), 
                            line_number * TileSet::tile_size()
                        )
                    ))
                );
            }
            ++col_number;
            ss>>tile;
        }
        ++line_number;
        std::getline(ifile, line);
    }
    return layer;
}
