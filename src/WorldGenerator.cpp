#include "WorldGenerator.h"

#include <iostream>

WorldLoader::WorldLoader(std::string file_name) : WorldGenerator(), file_name(file_name)
{

}

std::vector<Tile*> WorldLoader::generate(std::unique_ptr<TileSet> &tile_set)
{
    auto world = std::vector<Tile*>();
    std::ifstream ifile(file_name.c_str());
    if (!ifile.good()) {
        throw FileNotFoundException();
    }
    std::string name, line;
    std::getline(ifile, name);
    std::getline(ifile, line);
    int line_number = 0;
    while (ifile.good()) {
        std::stringstream ss(line);
        int tile;
        ss>>tile;
        int col_number = 0;
        while (ss.good()) {
            if (tile != -1) {
                world.push_back(
                    tile_set->spawn(
                        tile,
                        sf::Vector2i(
                            col_number * TileSet::tile_size(), 
                            line_number * TileSet::tile_size()
                        )
                    )
                );
            }
            ++col_number;
            ss>>tile;
        }
        ++line_number;
        std::getline(ifile, line);
    }
    ifile.close();
    return world;
}
