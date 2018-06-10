#ifndef LEVELEDITSCENE_H
#define LEVELEDITSCENE_H

#include "core.h"
#include "Scene.h"
#include "ui.h"

namespace scene {
    class LevelEdit : public Scene
    {
    public:
        LevelEdit(sf::Vector2i size);
        ~LevelEdit() = default;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        sf::View main_window;

        core::Index index = core::Index(LEVELDIR);

        Scene::Status state = Scene::nothing;
        Scene *next_scene = nullptr;

        ui::ButtonGroup menu;
        std::vector<ui::TextButton> levels;
        ui::TextButton new_level = ui::TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), core::StringProvider::get("leveleditmenu.new"));
        ui::TextButton back = ui::TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), core::StringProvider::get("leveleditmenu.back"));
    };
};

#endif //LEVELEDITSCENE_H
