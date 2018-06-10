#include "TileSet.h"
#include "TileSetEdit.h"
#include "TileSetNew.h"

namespace scene {
    TileSet::TileSet(sf::Vector2i size) : Scene(size)
    {
        std::vector<std::string> tileset_index;

        for (const auto &i : index.get()) {
            tileset_index.push_back(i);
        } 

        tilesets.reserve(tileset_index.size());
        for (size_t i = 0; i < tileset_index.size(); ++i) {
            tilesets.push_back(
                ui::TextButton(sf::IntRect(10, (i+1) * 50, 300, 50), Strings::utf8_to_sfml(tileset_index[i]))
            );
            menu.add_button(tileset_index[i], &tilesets[i]);
        }
        menu.add_button("new", &new_set);
        menu.add_button("exit_menu", &back);
    }

    TileSet::~TileSet()
    {

    }

    void TileSet::update(int delta, sf::RenderWindow &window)
    {
        menu.update(delta, core::app_container.get_input(), window);
        std::string pressed = this->menu.neg_edge_button();

        if (pressed == "exit_menu") {
            this->next_scene = nullptr;
            this->state = Scene::Status::pop_scene;
        } else if (pressed == "new") {
            this->next_scene = new TileSetNew(this->size);
            this->state = Scene::Status::push_scene;
        } else if (pressed != "") {
            this->next_scene = new TileSetEdit(this->size, pressed);
            this->state = Scene::Status::push_scene;
        }
    }

    void TileSet::draw(sf::RenderWindow &window)
    {
        menu.draw(window);
    }

    Scene::Status TileSet::status()
    {
        return state;
    }

    Scene *TileSet::new_scene()
    {
        return next_scene;
    }

    void TileSet::reset_status()
    {
        this->state = Scene::Status::nothing;
        this->next_scene = nullptr;
    }
};
