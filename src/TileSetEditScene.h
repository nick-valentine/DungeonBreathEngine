#ifndef TILESETEDITSCENE_H
#define TILESETEDITSCENE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "Macros.h"
#include "Exceptions.h"
#include "Strings.h"
#include "Container.h"
#include "Scene.h"
#include "TextButton.h"
#include "SpriteButton.h"
#include "ButtonGroup.h"
#include "StringProvider.h"
#include "Label.h"
#include "TextureMap.h"

class TileMarker
{
public:
    TileMarker(int base_size, sf::IntRect pos, int label, int sub_label);

    void set_pos(int base_size, int x, int y);
    void set_size(int base_size, int x, int y);
    void set_color(sf::Color c);
    int get_label() const;
    int get_sub_label() const;
    sf::IntRect get_export_pos() const;

    void draw(sf::RenderWindow &window);
private:
    sf::IntRect export_pos;
    sf::IntRect pos;
    sf::RectangleShape shape;
    int label;
    int sub_label;
    Label number_label;
};

class TileSetEditScene : public Scene
{
public:
    enum game_state {
        editing = 0,
        in_menu
    };
    TileSetEditScene(sf::Vector2i size, std::string tileset);
    ~TileSetEditScene();

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    void update_editing(int delta, sf::RenderWindow &window);
    void update_menu(int delta, sf::RenderWindow &window);
    void draw_editing(sf::RenderWindow &window);
    void draw_menu(sf::RenderWindow &window);

    void place_marker();

    void load_tile_set();
    void save_tile_set();
    void delete_markers();

    std::string grouped_anim_tile(int id);

    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    game_state inner_state;

    sf::Texture *tex;
    sf::Sprite spr;

    std::vector<TileMarker> markers;
    std::string name, texture_name;
    int base_size, anim_speed;

    std::vector<bool> last_input;

    TileMarker current_marker;
    int current_x;
    int current_y;
    int current_width;
    int current_height;
    int current_id;
    int current_sub_id;

    ButtonGroup menu;
    std::string tileset;
    Label tileset_label;

    TextButton edit;
    TextButton save;
    TextButton back;
};

#endif //TILESETEDITSCENE_H
