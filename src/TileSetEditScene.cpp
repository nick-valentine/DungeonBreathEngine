#include "TileSetEditScene.h"
#include "TileSetScene.h"

#include <iostream>

#define START_TEX_X 100.f
#define START_TEX_Y 100.f

TileMarker::TileMarker(sf::IntRect pos, int label) :
    pos(pos), shape(), label(label), number_label(pos, "")
{
    shape.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
    shape.setSize(sf::Vector2f(float(pos.width), float(pos.height)));
    shape.setOutlineColor(sf::Color::Blue);
    shape.setOutlineThickness(1);
    shape.setFillColor(sf::Color::Transparent);
    char l[50];
    sprintf(l, "%d", label);
    number_label.set_character_size(14);
    number_label.set_string(l);

}

void TileMarker::set_pos(int base_size, int x, int y)
{
    pos = sf::IntRect(x*base_size+START_TEX_X, y*base_size+START_TEX_Y, pos.width, pos.height);
    shape.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
}

void TileMarker::set_size(int base_size, int x, int y)
{
    pos.width = x*base_size;
    pos.height = y*base_size;
    shape.setSize(sf::Vector2f(float(pos.width), float(pos.height)));
}

void TileMarker::set_color(sf::Color c)
{
    shape.setOutlineColor(c);
}

void TileMarker::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    number_label.draw(window);
}

TileSetEditScene::TileSetEditScene(sf::Vector2i size, std::string tileset) : Scene(size),
    state(Scene::nothing),
    next_scene(nullptr),
    inner_state(editing),
    current_marker(sf::IntRect(START_TEX_X, START_TEX_Y, 0, 0), 0),
    current_x(0), current_y(0), current_width(1), current_height(1),
    tileset(tileset),
    tileset_label(sf::IntRect(10, 10, 300, 50), Strings::utf8_to_sfml(tileset)),
    edit(sf::IntRect(size.x - 400, size.y - 160, 300, 50), StringProvider::get("tileseteditmenu.edit")),
    back(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("optionsmenu.back_button"))
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    menu.add_button("edit", &edit);
    menu.add_button("exit_menu", &back);

    auto filename = TILESETDIR + tileset + ".txt";
    std::ifstream ifile(filename.c_str());
    if (!ifile.good()) {
        throw FileNotFoundException();
    }
    ifile>>name>>size_key>>base_size>>texture_key>>texture_name;
    int label = 0;
    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        std::stringstream ss(line);
        int x, y, width, height;
        do {
            ss>>x>>y>>width>>height;
            x*=base_size;
            x+=START_TEX_X;
            y*=base_size;
            y+=START_TEX_Y;
            height*=base_size;
            width*=base_size;

            markers.push_back(TileMarker(sf::IntRect(x, y, width, height), label));
        } while (ss.good());
        ++label;
    }
    ifile.close();

    std::string full_tex_name = IMGDIR + texture_name;
    tex = TextureMap::request(full_tex_name.c_str());
    spr = sf::Sprite(*tex);
    spr.setPosition(sf::Vector2f(START_TEX_X, START_TEX_Y));

    current_marker.set_size(base_size, 1, 1);
    current_marker.set_color(sf::Color::Red);

}

TileSetEditScene::~TileSetEditScene()
{

}

void TileSetEditScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    if (inner_state == editing) {
        update_editing(delta, window, input, logger);
    } else {
        update_menu(delta, window, input, logger);
    }
}

void TileSetEditScene::draw(sf::RenderWindow &window)
{
    window.draw(spr);
    window.setView(this->main_window);
    if (inner_state == editing) {
        draw_editing(window);
    } else {
        draw_menu(window);
    }
}

Scene::Status TileSetEditScene::status()
{
    return state;
}

Scene *TileSetEditScene::new_scene()
{
    return next_scene;
}

void TileSetEditScene::update_editing(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    auto new_input = input->poll_all();

    if (new_input[Input::up] && !last_input[Input::up] && new_input[Input::alt_fire]) {
        current_height++;
        current_marker.set_size(base_size, current_width, current_height);
    } else if (new_input[Input::right] && !last_input[Input::right]) {
        current_x++;
        current_marker.set_pos(base_size, current_x, current_y);
    } else if (new_input[Input::left] && !last_input[Input::left]) {
        current_x--;
        current_marker.set_pos(base_size, current_x, current_y);
    } else if (new_input[Input::up] && !last_input[Input::up]) {
        current_y--;
        current_marker.set_pos(base_size, current_x, current_y);
    } else if (new_input[Input::down] && !last_input[Input::down]) {
        current_y++;
        current_marker.set_pos(base_size, current_x, current_y);
    } else if (new_input[Input::escape] && !last_input[Input::escape]) {
        inner_state = in_menu;
    }

    last_input = new_input;
}

void TileSetEditScene::update_menu(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    menu.update(delta, input, window);
    std::string pressed = this->menu.neg_edge_button();

    if (pressed == "edit") {
        this->inner_state = editing;
    } else if (pressed == "exit_menu") {
        this->next_scene = new TileSetScene(this->size);
        this->state = Scene::switch_scene;
    }
}

void TileSetEditScene::draw_editing(sf::RenderWindow &window)
{
    tileset_label.draw(window);
    for (auto &i : markers) {
        i.draw(window);
    }

    current_marker.draw(window);
}

void TileSetEditScene::draw_menu(sf::RenderWindow &window)
{
    menu.draw(window);
}

