#include "LevelEditEditScene.h"

#define TILE_SIZE 64
#define CAMERA_LAG 10

LevelEditEditScene::LevelEditEditScene(sf::Vector2i size, std::string name) : Scene(size), name(name), cursor()
{
    load_level();
    cursor.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    cursor.setOutlineColor(sf::Color::Blue);
    cursor.setFillColor(sf::Color::White);
    cursor.setPosition(sf::Vector2f(0.0f, 0.0f));
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
        cursor.move(sf::Vector2f(0, TILE_SIZE));
    } else if (new_input[Input::up] && !last_input[Input::up]) {
        cursor.move(sf::Vector2f(0, -TILE_SIZE));
    } else if (new_input[Input::left] && !last_input[Input::left]) {
        cursor.move(sf::Vector2f(-TILE_SIZE, 0));
    } else if (new_input[Input::right] && !last_input[Input::right]) {
        cursor.move(sf::Vector2f(TILE_SIZE, 0));
    } else if (new_input[Input::escape] && !last_input[Input::escape]) {
        this->state = Scene::Status::pop_scene;
        this->next_scene = nullptr;
    } else if (new_input[Input::alt_fire] && !last_input[Input::alt_fire]) {
        this->cur_state = select_tile;
    }
    last_input = new_input;
    auto target_camera_center = cursor.getPosition();
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
    window.draw(cursor);
}

void LevelEditEditScene::update_select(int delta, sf::RenderWindow &window)
{
    this->tile_selector->update(delta, window);
}

void LevelEditEditScene::draw_select(sf::RenderWindow &window)
{
    this->tile_selector->draw(window);
}
