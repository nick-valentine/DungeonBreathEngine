#ifndef LEVELEDITEDITSCENE_H
#define LEVELEDITEDITSCENE_H

#include <fstream>
#include <sstream>
#include <vector>

#include "World.h"
#include "Scene.h"
#include "ButtonGroup.h"
#include "Exceptions.h"
#include "LevelEditTileScene.h"

class LevelEditEditScene : public Scene
{
public:
    enum game_state {
        edit_level = 0,
        select_tile
    };
    LevelEditEditScene(sf::Vector2i size, std::string name);
    ~LevelEditEditScene() = default;

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    void load_level();
    void save_level();

    void update_edit(int delta, sf::RenderWindow &window);
    void draw_edit(sf::RenderWindow &window);
    void update_select(int delta, sf::RenderWindow &window);
    void draw_select(sf::RenderWindow &window);

    sf::View main_window;

    Scene::Status state = Scene::Status::nothing;
    Scene *next_scene = nullptr;

    std::unique_ptr<World> world = nullptr;
    sf::RectangleShape cursor;

    std::string title;
    std::string name;
    std::string tileset;

    std::unique_ptr<LevelEditTileScene> tile_selector = nullptr;
    ButtonGroup menu;

    game_state cur_state = edit_level;

    std::vector<bool> last_input;
};

#endif //LEVELEDITEDITSCENE_H
