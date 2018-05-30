#include "LevelEditEditScene.h"

LevelEditEditScene::LevelEditEditScene(sf::Vector2i size, std::string name) : Scene(size), name(name)
{
    load_level();
}

void LevelEditEditScene::update(int delta, sf::RenderWindow &window)
{
    world->update(delta, window);
}

void LevelEditEditScene::draw(sf::RenderWindow &window)
{
    world->draw(window);
}

Scene::Status LevelEditEditScene::status()
{
    return this->state;
}

Scene *LevelEditEditScene::new_scene()
{
    return this->next_scene;
}

void LevelEditEditScene::reset_status()
{
    this->next_scene = nullptr;
    this->state = Scene::Status::nothing;
}

void LevelEditEditScene::load_level()
{
    std::string filename = name + ".txt";
    std::ifstream ifile(LEVELDIR + filename);
    app_container.get_logger()->info(filename.c_str());
    if (!ifile.good()) {
        throw FileNotFoundException();
    }
    std::getline(ifile, title);
    ifile>>tileset;
    ifile.close();
    world = std::unique_ptr<World>(
        new World(
            std::unique_ptr<TileSet>(
                new TileSet(tileset)
            ), 
            std::unique_ptr<WorldGenerator>(
                new WorldLoader(LEVELDIR + filename)
            )
        )
    );
}

void LevelEditEditScene::save_level()
{

}
