#ifndef LEVELEDITNEWSCENE_H
#define LEVELEDITNEWSCENE_H

#include "core.h"
#include "ui.h"
#include "Scene.h"

namespace scene {
    class LevelEditNew : public Scene
    {
    public:
        LevelEditNew(sf::Vector2i size);
        ~LevelEditNew() = default;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        void wakeup(sf::String message);
        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        void write_level_meta();
        sf::View main_window;

        core::Index index = core::Index(LEVELDIR);

        Scene::Status state = Scene::nothing;
        Scene *next_scene = nullptr;

        ui::Label name_label = ui::Label(sf::IntRect(100, 100, 300, 50), core::StringProvider::get("levelnewmenu.name"));
        ui::Label spritesheet_label = ui::Label(sf::IntRect(100, 160, 300, 50), core::StringProvider::get("levelnewmenu.spritesheet"));

        ui::TextButton *current_button = nullptr;

        ui::ButtonGroup menu;
        ui::TextButton name = ui::TextButton(sf::IntRect(400, 100, 300, 50), "");
        ui::TextButton spritesheet = ui::TextButton(sf::IntRect(400, 160, 300, 50), "");

        ui::TextButton proceed = ui::TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), core::StringProvider::get("levelnewmenu.proceed"));
        ui::TextButton back = ui::TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), core::StringProvider::get("levelnewmenu.back"));
    };
};

#endif //LEVELEDITNEWSCENEE_H
