#include "Options.h"

namespace scene {
    Options::Options(sf::Vector2i size) :
        Scene(size),
        back_button(sf::Rect<int>(10, size.y - 100, 300, 50), core::StringProvider::get("optionsmenu.back_button")),
        menu(),
        langs()
    {
        this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
        set_volume();
        volume_input.set_value(current_volume);
        volume_input.set_fmt_string(": %d%%");
        menu.add_button("lang_left", &lang_button_left);
        menu.add_button("lang_right", &lang_button_right);
        volume_input.add("volume", menu);
        menu.add_button("key_bind", &key_bind_button);
        menu.add_button("back", &back_button);

        auto lang = core::ConfigLoader::get_string_option("language");
        load_supported_langs();
        for (size_t i = 0; i < langs.size(); ++i) {
            if (langs[i].first == lang) {
                current_lang = i;
                break;
            }
        }
    }

    Options::~Options()
    {
        audio::MusicManager::stop();
    }

    void Options::update(int delta, sf::RenderWindow &window)
    {
        if (first_loop) {
            first_loop = false;
            audio::MusicManager::play(audio::MusicManager::Song::main_menu);
        }
        this->menu.update(delta, core::app_container.get_input(), window);
        
        std::string pressed = this->menu.neg_edge_button();
        volume_input.update(pressed);
        if (pressed == "back") {
            core::ConfigLoader::save();
            this->next_scene = nullptr;
            this->state = Scene::Status::pop_scene;
        }

        if (pressed == "key_bind") {
            core::app_container.get_logger()->info("todo: implement key bind state");
        }

        if (pressed == "lang_left") {
            if (current_lang == 0) {
                current_lang = langs.size();
            } 
            --current_lang;
            set_language();
        }
        if (pressed == "lang_right") {
            current_lang = (current_lang + 1) % langs.size();
            set_language();
        }
        if (pressed == "volume_right") {
            current_volume = volume_input.value();
            set_volume();
        }
        if (pressed == "volume_left") {
            current_volume = volume_input.value();
            set_volume();
        }
        lang_label.set_string(langs[current_lang].second);
    }

    void Options::draw(sf::RenderWindow &window)
    {
        window.setView(this->main_window);
        this->menu.draw(window);
        this->lang_label.draw(window);
        this->volume_input.draw(window);
    }

    Scene::Status Options::status()
    {
        return this->state;
    }

    Scene *Options::new_scene()
    {
        return this->next_scene;
    }

    void Options::load_supported_langs()
    {
        std::ifstream ifile(LANGDIR "supported.txt");
        while (ifile.good()) {
            std::string key, label;
            ifile>>key>>label;
            if (label != "") {
                langs.push_back(langpair(key, Strings::utf8_to_sfml(label)));
            }
        }
        ifile.close();
    }

    void Options::set_language()
    {
        core::StringProvider::load(langs[current_lang].first);
        core::ConfigLoader::mutate_option("language", langs[current_lang].first);
        back_button.set_label(core::StringProvider::get("optionsmenu.back_button"));
        key_bind_button.set_label(core::StringProvider::get("optionsmenu.key_bind_button"));
        set_volume();
    }

    void Options::set_volume()
    {
        audio::MusicManager::set_volume(current_volume);
        core::ConfigLoader::mutate_option("volume", current_volume);
    }

    void Options::reset_status()
    {
        this->state = Scene::Status::nothing;
        this->next_scene = nullptr;
    }
};
