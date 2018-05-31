#include "LevelEditTileScene.h"

#define TILE_SIZE 64
#define CAMERA_LAG 10

LevelEditTileScene::LevelEditTileScene(sf::Vector2i size, std::string tileset) : Scene(size), tileset(tileset), last_input(Input::num_keys, false)
{
    cursor.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    cursor.setOutlineColor(sf::Color::Blue);
    cursor.setOutlineThickness(5.0f);
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setPosition(sf::Vector2f(0.0f, 0.0f));
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    keys = this->tileset.get_keys();
    int x = 0, y = 0;
    int maxY = 0;
    for (const auto &i : keys) {
        auto tmp = this->tileset.spawn(TileType(i), sf::Vector2i(x, y));
        tiles.push_back(std::unique_ptr<Tile>(tmp));
        auto size = tmp->get_size();
        x += size.x;
        if (size.y > maxY) {
            maxY = size.y;
        }
        if (x >= this->size.x) {
            x = 0;
            y += maxY;
            maxY = 0;
        }
    }
}

void LevelEditTileScene::update(int delta, sf::RenderWindow &window)
{
    auto new_input = app_container.get_input()->poll_all();
    if (new_input[Input::down] && !last_input[Input::down]) {
        cursor.move(sf::Vector2f(0, TILE_SIZE));
    } else if (new_input[Input::up] && !last_input[Input::up]) {
        cursor.move(sf::Vector2f(0, -TILE_SIZE));
    } else if (new_input[Input::left] && !last_input[Input::left]) {
        cursor.move(sf::Vector2f(-TILE_SIZE, 0));
    } else if (new_input[Input::right] && !last_input[Input::right]) {
        cursor.move(sf::Vector2f(TILE_SIZE, 0));
    } else if (!new_input[Input::escape] && last_input[Input::escape]) {
        update_selected();
        this->state = Scene::Status::pop_scene;
        this->next_scene = nullptr;
    } 

    last_input = new_input;
    auto target_camera_center = cursor.getPosition();
    auto camera_center = this->main_window.getCenter();
    sf::Vector2f camera_diff;
    camera_diff.x = (target_camera_center.x - camera_center.x) / CAMERA_LAG;
    camera_diff.y = (target_camera_center.y - camera_center.y) / CAMERA_LAG;

    this->main_window.move(camera_diff);

    for (const auto &i : tiles) {
        i->update(delta);
    }
}

void LevelEditTileScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    for (const auto &i : tiles) {
        i->draw(window);
    }
    window.draw(cursor);
}

int LevelEditTileScene::get_selected()
{
    return current_selected;
}

Scene::Status LevelEditTileScene::status()
{
    return this->state;
}

Scene *LevelEditTileScene::new_scene()
{
    return this->next_scene;
}

void LevelEditTileScene::reset_status()
{
    this->state = Scene::Status::nothing;
    this->next_scene = nullptr;
}

void LevelEditTileScene::update_selected()
{
    auto i = 0;
    for (const auto &t : tiles) {
        auto pos = t->get_location();
        auto size = t->get_size();
        auto rect = sf::IntRect(pos.x, pos.y, size.x, size.y);
        auto cpos = cursor.getPosition();
        if (rect.contains(cpos.x + 1, cpos.y + 1)) {
            current_selected = keys[i];
            return;
        }
        ++i;
    }
}
