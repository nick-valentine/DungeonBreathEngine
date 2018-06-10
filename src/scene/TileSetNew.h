#ifndef TILESETNEWSCENE_H
#define TILESETNEWSCENE_H

#include <vector>
#include <fstream>

#include "Macros.h"
#include "core.h"
#include "Scene.h"
#include "Keyboard.h"
#include "ui.h"

namespace scene {
    class TileSetNew : public Scene
    {
    public:
        enum player_state {
            in_menu = 0,
            in_keyboard
        };
        TileSetNew(sf::Vector2i size);
        ~TileSetNew() = default;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        void update_menu(int delta, sf::RenderWindow &window);
        void draw_menu(sf::RenderWindow &window);
        void update_keyboard(int delta, sf::RenderWindow &window);
        void draw_keyboard(sf::RenderWindow &window);

        void write_tileset_meta();

        sf::View main_window;

        core::Index index = core::Index(TILESETDIR);

        Scene::Status state = Scene::nothing;
        Scene *next_scene = nullptr;

        ui::Label name_label = ui::Label(sf::IntRect(100,100,300,50), core::StringProvider::get("tilesetnewmenu.name"));
        ui::Label spritesheet_label = ui::Label(sf::IntRect(100, 160, 300, 50), core::StringProvider::get("tilesetnewmenu.spritesheet"));
        ui::Label base_size_label = ui::Label(sf::IntRect(100, 220, 300, 50), core::StringProvider::get("tilesetnewmenu.base_size"));

        ui::TextButton *current_button = nullptr;

        ui::ButtonGroup menu;
        ui::TextButton name = ui::TextButton(sf::IntRect(400, 100, 300, 50), "");
        ui::TextButton spritesheet = ui::TextButton(sf::IntRect(400, 160, 300, 50), "");
        ui::TextButton base_size = ui::TextButton(sf::IntRect(400, 220, 300, 50), "");
        ui::TextButton proceed = ui::TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), core::StringProvider::get("tilesetnewmenu.proceed"));
        ui::TextButton back = ui::TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), core::StringProvider::get("tilesetnewmenu.back"));

        player_state pl_state = in_menu;
        Keyboard keyboard;
    };
};


#endif //TILESETNEWSCENE_H
