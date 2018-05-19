#include "MainMenuScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "TileSetScene.h"

MainMenuScene::MainMenuScene(sf::Vector2i size, Input *input, Logger *logger) :
    Scene(size, input, logger),
    state(Scene::Status::nothing),
    next_scene(nullptr),
    tile_editor_button(sf::Rect<int>(10, size.y - 280, 300, 50), StringProvider::get("mainmenu.tile_editor_button")),
    play_button(sf::Rect<int>(10, size.y - 220, 300, 50), StringProvider::get("mainmenu.new_game_button")),
    options_button(sf::Rect<int>(10, size.y - 160, 300, 50), StringProvider::get("mainmenu.options_button")),
    exit_button(sf::Rect<int>(10, size.y - 100, 300, 50), StringProvider::get("mainmenu.exit_button")),
    menu()
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    menu.add_button("tile_editor", &tile_editor_button);
    menu.add_button("play", &play_button);
    menu.add_button("options", &options_button);
    menu.add_button("exit", &exit_button);
}

MainMenuScene::~MainMenuScene()
{
    MusicManager::stop();
}

void MainMenuScene::update(int delta, sf::RenderWindow &window)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::main_menu);
    }

    this->menu.update(delta, input, window);
    
    std::string pressed = this->menu.neg_edge_button();
    if (pressed == "play") {
        this->next_scene = new GameScene(this->size, this->input, this->logger);
        this->state = Scene::Status::switch_scene;
    }
    if (pressed == "options") {
        this->next_scene = new OptionsScene(this->size, this->input, this->logger);
        this->state = Scene::Status::switch_scene;
    }
    if (pressed == "tile_editor") {
        this->next_scene = new TileSetScene(this->size, this->input, this->logger);
        this->state = Scene::Status::switch_scene;
    }
    if (pressed == "exit") {
        this->next_scene = nullptr;
        this->state = Scene::Status::exit_program;
    }
}

void MainMenuScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->menu.draw(window);
}

Scene::Status MainMenuScene::status()
{
    return this->state;
}

Scene *MainMenuScene::new_scene()
{
    return this->next_scene;
}
