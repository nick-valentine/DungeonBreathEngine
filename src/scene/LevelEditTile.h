#ifndef LEVELEDITTILESCENE_H
#define LEVELEDITTILESCENE_H

#include <vector>

#include "core.h"
#include "Scene.h"
#include "render.h"

namespace scene {
    class LevelEditTile : public Scene
    {
    public:
        LevelEditTile(sf::Vector2i size, std::string tileset);
        ~LevelEditTile() = default;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        int get_selected();

        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        void update_selected();
        sf::View main_window;

        Scene::Status state = Scene::Status::nothing;
        Scene *next_scene = nullptr;
        sf::RectangleShape cursor;

        render::TileSet tileset;
        std::vector<int> keys;
        std::vector<std::unique_ptr<render::Tile> > tiles;

        int current_selected = -1;

        std::vector<bool> last_input;
    };
};

#endif //LEVELEDITTILESCENE_H
