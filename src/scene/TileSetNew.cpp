#include "TileSetNew.h"
#include "TileSetEdit.h"
#include "Keyboard.h"

namespace scene {
    TileSetNew::TileSetNew(sf::Vector2i size) : Scene(size)
    {
        menu.add_button("name", &name);
        menu.add_button("spritesheet", &spritesheet);
        menu.add_button("basesize", &base_size);
        menu.add_button("proceed", &proceed);
        menu.add_button("back", &back);
    }

    void TileSetNew::update(int delta, sf::RenderWindow &window)
    {
        return update_menu(delta, window);
    }

    void TileSetNew::draw(sf::RenderWindow &window)
    {
        return draw_menu(window);
    }

    void TileSetNew::wakeup(sf::String message)
    {
        if (current_button != nullptr) {
            current_button->set_label(message);
        }
        pl_state = in_menu;
    }

    Scene::Status TileSetNew::status()
    {
        return state;
    }

    Scene *TileSetNew::new_scene()
    {
        return next_scene;
    }

    void TileSetNew::update_menu(int delta, sf::RenderWindow &window)
    {
        menu.update(delta, core::app_container.get_input(), window);
        auto pressed = this->menu.neg_edge_button();

        if (pressed == "proceed") {
            write_tileset_meta();
            this->next_scene = new TileSetEdit(this->size, name.get_label());
            this->state = Scene::Status::push_scene;
        } else if (pressed == "name") {
            pl_state = in_keyboard;
            current_button = &name;
            this->next_scene = new Keyboard(this->size);
            this->state = Scene::Status::push_scene;
        } else if (pressed == "spritesheet") {
            pl_state = in_keyboard;
            current_button = &spritesheet;
            this->next_scene = new Keyboard(this->size);
            this->state = Scene::Status::push_scene;
        } else if (pressed == "basesize") {
            pl_state = in_keyboard;
            current_button = &base_size;
            this->next_scene = new Keyboard(this->size);
            this->state = Scene::Status::push_scene;
        }else if (pressed == "back") {
            this->next_scene = nullptr;
            this->state = Scene::Status::pop_scene;
        }
    }

    void TileSetNew::draw_menu(sf::RenderWindow &window)
    {
        name_label.draw(window);
        spritesheet_label.draw(window);
        base_size_label.draw(window);
        menu.draw(window);
    }

    void TileSetNew::write_tileset_meta()
    {
        index.add(name.get_label().toAnsiString());
        index.save();

        // @todo: this breaks internationalizatin a bit
        std::string filename = name.get_label().toAnsiString(); 
        filename += ".txt";
        std::ofstream datafile(TILESETDIR + filename);
        datafile<<name.get_label().toUtf8().c_str()<<"\n";
        datafile<<"size "<<base_size.get_label().toUtf8().c_str()<<"\n";
        datafile<<"tex "<<spritesheet.get_label().toUtf8().c_str()<<"\n";
        datafile.close();
    }

    void TileSetNew::reset_status()
    {
        this->state = Scene::Status::nothing;
        this->next_scene = nullptr;
    }
};
