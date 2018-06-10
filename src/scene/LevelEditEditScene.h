#ifndef LEVELEDITEDITSCENE_H
#define LEVELEDITEDITSCENE_H

#include <fstream>
#include <sstream>
#include <vector>

#include "World.h"
#include "Scene.h"
#include "ui.h"
#include "core.h"
#include "LevelEditTileScene.h"
#include "LevelEditActorSelectScene.h"

namespace LevelEdit {
    class Cursor {
    public:
        Cursor();
        void move(sf::Vector2i offset);
        sf::Vector2i get_location();

        void draw(sf::RenderWindow &window);

        void set_tile(Tile *tile);
        void set_actor(std::string actor);

        std::string get_actor();
    private:
        sf::Vector2i loc = sf::Vector2i(0, 0);
        sf::Vector2i size;
        sf::RectangleShape shape;
        std::unique_ptr<Tile> current = nullptr;
        std::string actor;
    };
};

class LevelEditEditScene : public Scene
{
public:
    enum game_state {
        edit_level = 0,
        select_tile,
        select_actor,
        add_collision,
        in_menu
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

    void update_edit(int delta, sf::RenderWindow &window);
    void draw_edit(sf::RenderWindow &window);
    void update_select(int delta, sf::RenderWindow &window);
    void draw_select(sf::RenderWindow &window);
    void update_actor_select(int delta, sf::RenderWindow &window);
    void draw_actor_select(sf::RenderWindow &window);
    void update_menu(int delta, sf::RenderWindow &window);
    void draw_menu(sf::RenderWindow &window);

    void update_layer(int diff);

    sf::View main_window;
    sf::View menu_window;

    Scene::Status state = Scene::Status::nothing;
    Scene *next_scene = nullptr;

    std::unique_ptr<World> world = nullptr;
    std::unique_ptr<TileSet> tiles = nullptr;
    LevelEdit::Cursor cursor;
    int selected_tile;
    int layer = 0;
    int collision = 0;

    std::string title;
    std::string name;
    std::string tileset;

    std::unique_ptr<LevelEditTileScene> tile_selector = nullptr;
    LevelEditActorSelectScene actor_selector;

    NumberInput layer_input = NumberInput(sf::Vector2i(10, 100), StringProvider::get("leveleditmenu.layer_label"), 10, 0, 1);
    NumberInput collision_type = NumberInput(sf::Vector2i(10, 160), StringProvider::get("leveleditmenu.collision_label"), 10, 0, 1);

    ButtonGroup menu;
    TextButton edit;
    TextButton save;
    TextButton back;


    game_state cur_state = edit_level;

    std::vector<bool> last_input;
};

#endif //LEVELEDITEDITSCENE_H
