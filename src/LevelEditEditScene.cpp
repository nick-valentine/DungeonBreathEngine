#include "LevelEditEditScene.h"

#define TILE_SIZE 64
#define CAMERA_LAG 10

LevelEdit::Cursor::Cursor() : size(TILE_SIZE, TILE_SIZE)
{
    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setOutlineColor(sf::Color::Blue);
    shape.setOutlineThickness(5.0f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(sf::Vector2f(0.0f, 0.0f));
}

void LevelEdit::Cursor::move(sf::Vector2i offset)
{
    this->loc += offset;
    shape.move(offset.x, offset.y);
    if (current != nullptr) {
        current->set_location(this->loc);
    }
}

sf::Vector2i LevelEdit::Cursor::get_location()
{
    return loc;
}

void LevelEdit::Cursor::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    if (current != nullptr) {
        current->draw(window);
    }
}

void LevelEdit::Cursor::set_tile(Tile *tile)
{
    current.reset(tile);
    size = current->get_size();
    current->set_location(loc);
    shape.setSize(sf::Vector2f(size.x, size.y));
    this->actor = "";
}

void LevelEdit::Cursor::set_actor(std::string actor)
{
    this->actor = actor;
    current.reset(nullptr);
}

std::string LevelEdit::Cursor::get_actor()
{
    return this->actor;
}

LevelEditEditScene::LevelEditEditScene(sf::Vector2i size, std::string name) : 
    Scene(size), name(name), actor_selector(size),
    edit(sf::IntRect(size.x - 400, size.y - 220, 300, 50), StringProvider::get("leveleditmenu.edit")),
    save(sf::IntRect(size.x - 400, size.y - 160, 300, 50), StringProvider::get("leveleditmenu.save")),
    back(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("leveleditmenu.back_button")),
    last_input(Input::num_keys, false)
{
    load_level();
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    this->menu_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    menu.add_button("layer_right", &layer_button_right);
    menu.add_button("layer_left", &layer_button_left);
    menu.add_button("edit", &edit);
    menu.add_button("save", &save);
    menu.add_button("exit_menu", &back);
}

void LevelEditEditScene::update(int delta, sf::RenderWindow &window)
{
    switch (cur_state) {
    case edit_level:
        return update_edit(delta, window);
    case select_tile:
        return update_select(delta, window);
    case select_actor:
        return update_actor_select(delta, window);
    case in_menu:
        return update_menu(delta, window);
    }
}

void LevelEditEditScene::draw(sf::RenderWindow &window)
{
    switch (cur_state) {
    case edit_level:
        return draw_edit(window);
    case select_tile:
        return draw_select(window);
    case select_actor:
        return draw_actor_select(window);
    case in_menu:
        return draw_menu(window);
    }
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
    tiles = std::unique_ptr<TileSet>(new TileSet(tileset));
    world = std::unique_ptr<World>(
        new World(
            tileset, 
            std::unique_ptr<WorldGenerator>(
                new WorldLoader(LEVELDIR + filename)
            )
        )
    );
    world->set_edit_mode(true);
    tile_selector = std::unique_ptr<LevelEditTileScene>(
        new LevelEditTileScene(
            this->size,
            tileset
        )
    );
}

void LevelEditEditScene::update_edit(int delta, sf::RenderWindow &window)
{
    world->update(delta, window);
    auto new_input = app_container.get_input()->poll_all();
    if (new_input[Input::accept] && (new_input[Input::fire] && !last_input[Input::fire])) {
        world->remove_tile(layer, cursor.get_location() / TILE_SIZE);
    } else if (new_input[Input::accept] && (new_input[Input::alt_fire] && !last_input[Input::alt_fire])) {
        this->cur_state = select_actor;
    } else if (new_input[Input::down] && !last_input[Input::down]) {
        cursor.move(sf::Vector2i(0, TILE_SIZE));
    } else if (new_input[Input::up] && !last_input[Input::up]) {
        cursor.move(sf::Vector2i(0, -TILE_SIZE));
    } else if (new_input[Input::left] && !last_input[Input::left]) {
        cursor.move(sf::Vector2i(-TILE_SIZE, 0));
    } else if (new_input[Input::right] && !last_input[Input::right]) {
        cursor.move(sf::Vector2i(TILE_SIZE, 0));
    } else if (!new_input[Input::escape] && last_input[Input::escape]) {
        this->cur_state = in_menu;
    } else if (new_input[Input::alt_fire] && !last_input[Input::alt_fire]) {
        this->cur_state = select_tile;
    } else if (new_input[Input::fire] && !last_input[Input::fire]) {
        if (selected_tile != -1) {
            world->set_tile(tiles->spawn(selected_tile, cursor.get_location()), layer, cursor.get_location() / TILE_SIZE);
        } else {
            world->add_actor(cursor.get_actor(), cursor.get_location());
        }
    }
    last_input = new_input;
    auto target_camera_center = cursor.get_location();
    auto camera_center = this->main_window.getCenter();
    sf::Vector2f camera_diff;
    camera_diff.x = (target_camera_center.x - camera_center.x) / CAMERA_LAG;
    camera_diff.y = (target_camera_center.y - camera_center.y) / CAMERA_LAG;

    this->main_window.move(camera_diff);
}

void LevelEditEditScene::draw_edit(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    world->draw(window);
    cursor.draw(window);
}

void LevelEditEditScene::update_select(int delta, sf::RenderWindow &window)
{
    this->tile_selector->update(delta, window);
    if (this->tile_selector->status() == Scene::Status::pop_scene) {
        this->tile_selector->reset_status();
        this->selected_tile = this->tile_selector->get_selected();
        if (this->selected_tile != -1) {
            this->cursor.set_tile(tiles->spawn(selected_tile, cursor.get_location()));
        }
        this->cur_state = edit_level;
    }
}

void LevelEditEditScene::draw_select(sf::RenderWindow &window)
{
    this->tile_selector->draw(window);
}

void LevelEditEditScene::update_actor_select(int delta, sf::RenderWindow &window)
{
    this->actor_selector.update(delta, window);
    if (this->actor_selector.status() == Scene::Status::pop_scene) {
        this->actor_selector.reset_status();
        this->cursor.set_actor(this->actor_selector.get_selected());
        this->cur_state = edit_level;
        this->selected_tile = -1;
    }
}

void LevelEditEditScene::draw_actor_select(sf::RenderWindow &window)
{
    this->actor_selector.draw(window);
}

void LevelEditEditScene::update_menu(int delta, sf::RenderWindow &window)
{
    menu.update(delta, app_container.get_input(), window);

    std::string pressed = this->menu.neg_edge_button();

    if (pressed == "layer_left") {
        this->update_layer(1);
    } else if (pressed == "layer_right") {
        this->update_layer(-1);
    } else if (pressed == "edit") {
        this->cur_state= edit_level;
    } else if (pressed == "exit_menu") {
        this->next_scene = nullptr;
        this->state = Scene::pop_scene;
    } else if (pressed == "save") {
        this->world->save();
    }
}

void LevelEditEditScene::draw_menu(sf::RenderWindow &window)
{
    window.setView(this->menu_window);
    layer_label.draw(window);
    layer_value_label.draw(window);
    menu.draw(window);
}

void LevelEditEditScene::update_layer(int diff)
{
    layer+=diff;
    if (layer < 0) {
        layer = 0;
    }
    char layer_lab[50];
    sprintf(layer_lab, "%d", layer);
    sf::String str = Strings::utf8_to_sfml(layer_lab);
    layer_value_label.set_string(str);
}
