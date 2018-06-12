#include "LevelEditNew.h"
#include "LevelEditEdit.h"
#include "Keyboard.h"

namespace scene {
    LevelEditNew::LevelEditNew(sf::Vector2i size) : Scene(size)
    {
        menu.add_button("name", &name);
        menu.add_button("spritesheet", &spritesheet);
        menu.add_button("proceed", &proceed);
        menu.add_button("back", &back);
    }

    void LevelEditNew::update(int delta, sf::RenderWindow &window)
    {
        menu.update(delta, core::app_container.get_input(), window);
        auto pressed = this->menu.neg_edge_button();

        if (pressed == "proceed") {
            write_level_meta();
            this->next_scene = new LevelEditEdit(this->size, this->name.get_label().toAnsiString());
            this->state = Scene::Status::push_scene;
        } else if (pressed == "name") {
            current_button = &name;
            this->next_scene = new Keyboard(this->size);
            this->state = Scene::Status::push_scene;
        } else if (pressed == "spritesheet") {
            current_button = &spritesheet;
            this->next_scene = new Keyboard(this->size);
            this->state = Scene::Status::push_scene;
        } else if (pressed == "back") {
            this->next_scene = nullptr;
            this->state = Scene::Status::pop_scene;
        }
    }

    void LevelEditNew::draw(sf::RenderWindow &window)
    {
        name_label.draw(window);
        spritesheet_label.draw(window);
        menu.draw(window);
    }

    void LevelEditNew::wakeup(sf::String message)
    {
        if (current_button != nullptr) {
            current_button->set_label(message);
        }
    }

    Scene::Status LevelEditNew::status()
    {
        return state;
    }

    Scene *LevelEditNew::new_scene()
    {
        return next_scene;
    }

    void LevelEditNew::reset_status()
    {
        this->state = Scene::Status::nothing;
        this->next_scene = nullptr;
    }

    void LevelEditNew::write_level_meta()
    {
        index.add(name.get_label().toAnsiString());
        index.save();

        std::string filename = name.get_label().toAnsiString();
        filename += ".txt";
        std::ofstream datafile(LEVELDIR + filename);
        datafile<<name.get_label().toUtf8().c_str()<<"\n";
        datafile<<"tex "<<spritesheet.get_label().toUtf8().c_str()<<"\n";
        datafile.close();
    }
};
