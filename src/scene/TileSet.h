#ifndef TILESETSCENE_H
#define TILESETSCENE_H

#include <vector>
#include <fstream>

#include "Macros.h"
#include "core.h"
#include "Scene.h"
#include "ui.h"

namespace scene {
    class TileSet : public Scene
    {
    public:
        TileSet(sf::Vector2i size);
        ~TileSet();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        sf::View main_window;

        core::Index index = core::Index(TILESETDIR);

        Scene::Status state = Scene::nothing;
        Scene *next_scene = nullptr;

        ButtonGroup menu;
        std::vector<TextButton> tilesets;
        TextButton new_set = TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), core::StringProvider::get("tilesetmenu.new"));
        TextButton back = TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), core::StringProvider::get("tilesetmenu.back"));
    };
};

#endif //TILESETSCENE_H
