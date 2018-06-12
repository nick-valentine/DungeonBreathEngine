#include "MainMenu.h"
#include "Game.h"
#include "Options.h"
#include "TileSet.h"
#include "LevelEdit.h"

namespace scene {
    MainMenu::MainMenu(sf::Vector2i size) : Scene(size)
    {
        this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

        auto level_edit = menu.add_text_button("level_editor", sf::Vector2i(10, size.y-340), "mainmenu.level_editor_button");
        auto tile_edit = menu.add_text_button("tile_editor", sf::Vector2i(10, size.y-280), "mainmenu.tile_editor_button");
        auto new_game = menu.add_text_button("play", sf::Vector2i(10, size.y-220), "mainmenu.new_game_button");
        auto options = menu.add_text_button("options", sf::Vector2i(10, size.y-160), "mainmenu.options_button");
        auto exit = menu.add_text_button("exit", sf::Vector2i(10, size.y-100), "mainmenu.exit_button");
        level_edit->set_down(tile_edit);
        tile_edit->set_down(new_game);
        new_game->set_down(options);
        options->set_down(options);
        //menu.set_current(level_edit);
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::update(int delta, sf::RenderWindow &window)
    {
        this->menu.update(delta, window);

        if (!menu.has_signal()) {
            return;
        }

        std::string pressed = this->menu.signal_tag();
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
        load_ui();
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

    void MainMenu::load_ui()
    {
        auto buttons = this->menu.get();
        for (const auto &i : *buttons) {
            if (i == nullptr) {
                continue;
            }
            std::string tag = i->get_tag();
//            auto b = std::dynamic_pointer_cast<ui::TextButton>(i->raw());
            ui::TextButton *b = nullptr;
            if (b == nullptr) {
                continue;
            }
            if (tag == "level_editor") {
                b->set_label(core::StringProvider::get("mainmenu.level_editor_button"));
            } else if (tag == "tile_editor") {
                b->set_label(core::StringProvider::get("mainmenu.tile_editor_button"));
            } else if (tag == "play") {
                b->set_label(core::StringProvider::get("mainmenu.new_game_button"));
            } else if (tag == "options") {
                b->set_label(core::StringProvider::get("mainmenu.options_button"));
            } else if (tag == "exit") {
                b->set_label(core::StringProvider::get("mainmenu.exit_button"));
            }
        }
    }
};
