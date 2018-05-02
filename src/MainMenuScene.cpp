#include "MainMenuScene.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    play_button(sf::Rect<int>(10, size.y - 160, 300, 50), StringProvider::get(L"mainmenu.new_game_button")),
    exit_button(sf::Rect<int>(10, size.y - 100, 300, 50), StringProvider::get(L"mainmenu.exit_button")),
	menu()
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

	menu.add_button("play", &play_button);
	menu.add_button("exit", &exit_button);
}

MainMenuScene::~MainMenuScene()
{
    MusicManager::stop();
}

void MainMenuScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::main_menu);
    }

	this->menu.update(delta, input, window);
	
	std::string pressed = this->menu.pressed_button();
    if (pressed == "play") {
        this->next_scene = new GameScene(this->size);
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
