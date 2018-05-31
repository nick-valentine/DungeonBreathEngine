#ifndef LEVELEDITTILESCENE_H
#define LEVELEDITTILESCENE_H

#include <vector>

#include "Scene.h"
#include "TileSet.h"

class LevelEditTileScene : public Scene
{
public:
    LevelEditTileScene(sf::Vector2i size, std::string tileset);
    ~LevelEditTileScene() = default;

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    sf::View main_window;

    Scene::Status state = Scene::Status::nothing;
    Scene *next_scene = nullptr;
    sf::RectangleShape cursor;

    TileSet tileset;
    std::vector<int> keys;
    std::vector<std::unique_ptr<Tile> > tiles;

    std::vector<bool> last_input;
};

#endif //LEVELEDITTILESCENE_H
