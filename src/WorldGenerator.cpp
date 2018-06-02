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
    spawn_actors(ifile);
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

std::shared_ptr<ActorManager> WorldLoader::get_actor_manager()
{
    return this->actor_man;
}

Dimension::Layer WorldLoader::spawn_layer(std::ifstream &ifile, TileSet &tile_set)
{
    std::string line;
    // consume lines up to layer start
    while ((line == "---" || line == "") && ifile.good()) {
        std::getline(ifile, line);
    }
    Dimension::Layer layer;
    int line_number = 0;
    while (ifile.good() && line != "---") {
        layer.push_back(spawn_line(line, line_number, tile_set));
        ++line_number;
        std::getline(ifile, line);
    }
    return layer;
}

Dimension::Line WorldLoader::spawn_line(std::string &line, int line_number, TileSet &tile_set)
{
    Dimension::Line l;
    std::stringstream ss(line);
    int tile;
    ss>>tile;
    int col_number = 0;
    while (ss.good()) {
        if (tile == -1) {
            l.push_back(Dimension::TilePtr(nullptr));
        } else {
            l.push_back(
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
    return l;
}

void WorldLoader::spawn_actors(std::ifstream &ifile)
{
    actor_man.reset(new ActorManager);
    std::string line;
    while((line == "---" || line == "") && ifile.good()) {
        std::getline(ifile, line);
    }

    while (line != "---" && ifile.good()) {
        std::stringstream ss(line);
        std::string name;
        sf::Vector2i pos;
        ss>>name>>pos.x>>pos.y;
        actor_man->spawn(name, pos);
        std::getline(ifile, line);
    }
}
