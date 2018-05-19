#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include <fstream>
#include <stdlib.h>

#include "Container.h"

#include "StringProvider.h"
#include "MusicManager.h"
#include "Scene.h"
#include "ButtonGroup.h"
#include "TextButton.h"
#include "SpriteButton.h"
#include "ConfigLoader.h"

class OptionsScene : public Scene
{
public:
    OptionsScene(sf::Vector2i size);
    ~OptionsScene();

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
	void reset_status();
private:
    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    Label lang_label;
    SpriteButton lang_button_left;
    SpriteButton lang_button_right;
    Label volume_label;
    SpriteButton volume_button_left;
    SpriteButton volume_button_right;
    TextButton key_bind_button;
    TextButton back_button;
    ButtonGroup menu;

    bool first_loop = true;

    typedef std::pair<std::string, sf::String> langpair;
    std::vector<langpair> langs;
    size_t current_lang;

    int current_volume;

    void load_supported_langs();
    void set_language();
    void set_volume();
};

#endif //OPTIONSSCENE_H
