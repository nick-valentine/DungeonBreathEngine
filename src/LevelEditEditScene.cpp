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
}

LevelEditEditScene::LevelEditEditScene(sf::Vector2i size, std::string name) : Scene(size), name(name), last_input(Input::num_keys, false)
{
    load_level();
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

void LevelEditEditScene::update(int delta, sf::RenderWindow &window)
{
    if (cur_state == edit_level) {
        return update_edit(delta, window);
    }
    return update_select(delta, window);
}

void LevelEditEditScene::draw(sf::RenderWindow &window)
{
    if (cur_state == edit_level) {
        return draw_edit(window);
    }
    return draw_select(window);
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
    std::cout<<tileset<<std::endl;
    tiles = std::unique_ptr<TileSet>(new TileSet(tileset));
    world = std::unique_ptr<World>(
        new World(
            tileset, 
            std::unique_ptr<WorldGenerator>(
                new WorldLoader(LEVELDIR + filename)
            )
        )
    );
    tile_selector = std::unique_ptr<LevelEditTileScene>(
        new LevelEditTileScene(
            this->size,
            tileset
        )
    );
}

void LevelEditEditScene::save_level()
{

}

void LevelEditEditScene::update_edit(int delta, sf::RenderWindow &window)
{
    world->update(delta, window);
    auto new_input = app_container.get_input()->poll_all();
    if (new_input[Input::down] && !last_input[Input::down]) {
        cursor.move(sf::Vector2i(0, TILE_SIZE));
    } else if (new_input[Input::up] && !last_input[Input::up]) {
        cursor.move(sf::Vector2i(0, -TILE_SIZE));
    } else if (new_input[Input::left] && !last_input[Input::left]) {
        cursor.move(sf::Vector2i(-TILE_SIZE, 0));
    } else if (new_input[Input::right] && !last_input[Input::right]) {
        cursor.move(sf::Vector2i(TILE_SIZE, 0));
    } else if (!new_input[Input::escape] && last_input[Input::escape]) {
        this->world->save();
        this->state = Scene::Status::pop_scene;
        this->next_scene = nullptr;
    } else if (new_input[Input::alt_fire] && !last_input[Input::alt_fire]) {
        this->cur_state = select_tile;
    } else if (new_input[Input::fire] && !last_input[Input::fire]) {
        if (selected_tile != -1) {
            world->set_tile(tiles->spawn(selected_tile, cursor.get_location()), 0, cursor.get_location() / TILE_SIZE);
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
        this->cursor.set_tile(tiles->spawn(selected_tile, cursor.get_location()));
        this->cur_state = edit_level;
    }
}

void LevelEditEditScene::draw_select(sf::RenderWindow &window)
{
    this->tile_selector->draw(window);
}
