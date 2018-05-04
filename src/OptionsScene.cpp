#include "OptionsScene.h"
#include "MainMenuScene.h"

OptionsScene::OptionsScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    next_scene(nullptr),
    lang_label(sf::IntRect(60, 100, 300, 50), "eng"),
    lang_button_left(ui::left(sf::IntRect(10, 100, 50, 50))),
    lang_button_right(ui::right(sf::IntRect(410, 100, 50, 50))),
    back_button(sf::Rect<int>(10, size.y - 100, 300, 50), StringProvider::get("optionsmenu.back_button")),
    menu(),
    last_pressed(""),
    langs(),
    current_lang(0)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    menu.add_button("lang_left", &lang_button_left);
    menu.add_button("lang_right", &lang_button_right);
    menu.add_button("back", &back_button);

    load_supported_langs();
    //@todo: set current lang from loaded langs
}

void OptionsScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    this->menu.update(delta, input, window);
    
    std::string pressed = this->menu.pressed_button();
    if (pressed == "back") {
        this->next_scene = new MainMenuScene(this->size);
        this->state = Scene::Status::switch_scene;
    }

    if (pressed == "lang_left" && last_pressed != "lang_left") {
        if (current_lang == 0) {
            current_lang = langs.size();
        } 
        --current_lang;
        set_language();
    }
    if (pressed == "lang_right" && last_pressed != "lang_right") {
        current_lang = (current_lang + 1) % langs.size();
        set_language();
    }
    lang_label.set_string(langs[current_lang].second);

    last_pressed = pressed;
}

void OptionsScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->menu.draw(window);
    this->lang_label.draw(window);
}

Scene::Status OptionsScene::status()
{
    return this->state;
}

Scene *OptionsScene::new_scene()
{
    return this->next_scene;
}

void OptionsScene::load_supported_langs()
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

void OptionsScene::set_language()
{
    StringProvider::load(langs[current_lang].first);
    back_button.set_label(StringProvider::get("optionsmenu.back_button"));
}
