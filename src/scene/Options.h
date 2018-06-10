#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include <fstream>
#include <stdlib.h>

#include "core.h"

#include "audio.h"
#include "Scene.h"
#include "ui.h"

namespace scene {
    class Options : public Scene
    {
    public:
        Options(sf::Vector2i size);
        ~Options();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        sf::View main_window;

        Scene::Status state = Scene::Status::nothing;
        Scene *next_scene = nullptr;

        Label lang_label = Label(sf::IntRect(60, 100, 300, 50), core::ConfigLoader::get_string_option("language", "eng"));
        SpriteButton lang_button_left = SpriteButton(ui::left(sf::IntRect(10, 100, 50, 50)));
        SpriteButton lang_button_right = SpriteButton(ui::right(sf::IntRect(410, 100, 50, 50)));
        NumberInput volume_input = NumberInput(sf::Vector2i(10, 150), core::StringProvider::get("optionsmenu.volume_label"), 100, 0, 5);
        TextButton key_bind_button = TextButton(sf::Rect<int>(10, 200, 300, 50), core::StringProvider::get("optionsmenu.key_bind_button"));
        TextButton back_button;
        ButtonGroup menu;

        bool first_loop = true;

        typedef std::pair<std::string, sf::String> langpair;
        std::vector<langpair> langs;
        size_t current_lang = 0;

        int current_volume = core::ConfigLoader::get_int_option("volume");

        void load_supported_langs();
        void set_language();
        void set_volume();
    };
};

#endif //OPTIONSSCENE_H
