#include "OptionsScene.h"
#include "MainMenuScene.h"

OptionsScene::OptionsScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    next_scene(nullptr),
    lang_label(sf::IntRect(60, 100, 300, 50), ConfigLoader::get_string_option("language", "eng")),
    lang_button_left(ui::left(sf::IntRect(10, 100, 50, 50))),
    lang_button_right(ui::right(sf::IntRect(410, 100, 50, 50))),
    volume_label(sf::IntRect(60, 150, 300, 50), ""),
    volume_button_left(ui::left(sf::IntRect(10, 150, 50, 50))),
    volume_button_right(ui::right(sf::IntRect(410, 150, 50, 50))),
    back_button(sf::Rect<int>(10, size.y - 100, 300, 50), StringProvider::get("optionsmenu.back_button")),
    key_bind_button(sf::Rect<int>(10, 200, 300, 50), StringProvider::get("optionsmenu.key_bind_button")),
    menu(),
    langs(),
    current_lang(0),
    current_volume(ConfigLoader::get_int_option("volume"))
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    set_volume();
    menu.add_button("lang_left", &lang_button_left);
    menu.add_button("lang_right", &lang_button_right);
    menu.add_button("volume_left", &volume_button_left);
    menu.add_button("volume_right", &volume_button_right);
    menu.add_button("key_bind", &key_bind_button);
    menu.add_button("back", &back_button);

    auto lang = ConfigLoader::get_string_option("language");
    load_supported_langs();
    for (size_t i = 0; i < langs.size(); ++i) {
        if (langs[i].first == lang) {
            current_lang = i;
            break;
        }
    }
}

OptionsScene::~OptionsScene()
{
    MusicManager::stop();
}

void OptionsScene::update(int delta, sf::RenderWindow &window)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::main_menu);
    }
    this->menu.update(delta, app_container.get_input(), window);
    
    std::string pressed = this->menu.neg_edge_button();
    if (pressed == "back") {
        ConfigLoader::save();
        this->next_scene = new MainMenuScene(this->size);
        this->state = Scene::Status::push_scene;
    }

    if (pressed == "key_bind") {
		app_container.get_logger()->info("todo: implement key bind state");
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
        current_volume+=5;
        if (current_volume > 100) {
            current_volume = 100;
        }
        set_volume();
    }
    if (pressed == "volume_left") {
        current_volume-=5;
        if (current_volume < 0) {
            current_volume = 0;
        }
        set_volume();
    }
    lang_label.set_string(langs[current_lang].second);
}

void OptionsScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->menu.draw(window);
    this->lang_label.draw(window);
    this->volume_label.draw(window);
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
    ConfigLoader::mutate_option("language", langs[current_lang].first);
    back_button.set_label(StringProvider::get("optionsmenu.back_button"));
    key_bind_button.set_label(StringProvider::get("optionsmenu.key_bind_button"));
    set_volume();
}

void OptionsScene::set_volume()
{
    MusicManager::set_volume(current_volume);
    ConfigLoader::mutate_option("volume", current_volume);
    char volume[50];
    sprintf(volume, ": %d%%", current_volume);
    sf::String volumeString = StringProvider::get("optionsmenu.volume_label");
    volumeString += Strings::utf8_to_sfml(volume);
    volume_label.set_string(volumeString);
}

void OptionsScene::reset_status()
{
	this->state = Scene::Status::nothing;
	this->next_scene = nullptr;
}