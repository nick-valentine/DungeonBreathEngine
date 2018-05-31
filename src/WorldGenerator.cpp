#include "WorldGenerator.h"

#include <iostream>

WorldLoader::WorldLoader(std::string file_name) : WorldGenerator(), file_name(file_name)
{

}

Dimension::Room WorldLoader::generate(std::unique_ptr<TileSet> &tile_set)
{
    auto world = Dimension::Room();
    std::ifstream ifile(file_name.c_str());
    if (!ifile.good()) {
        throw FileNotFoundException();
    }
    std::string name;
    std::getline(ifile, name);
    while (ifile.good()) {
        world.push_back(spawn_layer(ifile, tile_set));
    }
    ifile.close();
    return world;
}

Dimension::Layer WorldLoader::spawn_layer(std::ifstream &ifile, std::unique_ptr<TileSet> &tile_set)
{
    std::string line;
    Dimension::Layer layer;
    std::getline(ifile, line);
    int line_number = 0;
    while (ifile.good() && line != "---") {
        std::stringstream ss(line);
        int tile;
        ss>>tile;
        int col_number = 0;
        while (ss.good()) {
            layer.push_back(Dimension::Line());
            if (tile == -1) {
                layer[line_number].push_back(Dimension::TilePtr(nullptr));
            } else {
                layer[line_number].push_back(
                    Dimension::TilePtr(tile_set->spawn(
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
