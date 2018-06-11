#include "MainMenu.h"
#include "Game.h"
#include "Options.h"
#include "TileSet.h"
#include "LevelEdit.h"

namespace scene {
    MainMenu::MainMenu(sf::Vector2i size) : Scene(size)
    {
        this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

        menu.add_button("level_editor", &level_edit_button);
        menu.add_button("tile_editor", &tile_editor_button);
        menu.add_button("play", &play_button);
        menu.add_button("options", &options_button);
        menu.add_button("exit", &exit_button);
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::update(int delta, sf::RenderWindow &window)
    {
        this->menu.update(delta, core::app_container.get_input(), window);
        
        std::string pressed = this->menu.neg_edge_button();
        if (pressed == "play") {
            this->next_scene = new Game(this->size);
            this->state = Scene::Status::push_scene;
        }
        if (pressed == "options") {
            this->next_scene = new Options(this->size);
            this->state = Scene::Status::push_scene;
        }
        if (pressed == "tile_editor") {
            this->next_scene = new TileSet(this->size);
            this->state = Scene::Status::push_scene;
        }
        if (pressed == "level_editor") {
            this->next_scene = new LevelEdit(this->size);
            this->state = Scene::Status::push_scene;
        }
        if (pressed == "exit") {
            this->next_scene = nullptr;
            this->state = Scene::Status::pop_scene;
        }
    }

    void MainMenu::draw(sf::RenderWindow &window)
    {
        window.setView(this->main_window);
        this->menu.draw(window);
    }

    void MainMenu::wakeup(sf::String message)
    {
        audio::MusicManager::play(audio::MusicManager::Song::main_menu);
    }

    Scene::Status MainMenu::status()
    {
        return this->state;
    }

    Scene *MainMenu::new_scene()
    {
        return this->next_scene;
    }

    void MainMenu::reset_status()
    {
        this->state = Scene::Status::nothing;
        this->next_scene = nullptr;
    }
};
