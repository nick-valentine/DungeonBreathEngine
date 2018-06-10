#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "core.h"
#include "audio.h"
#include "Scene.h"
#include "ui.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene(sf::Vector2i size);
    ~MainMenuScene();

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
	void reset_status();
private:
    sf::View main_window;

    Scene::Status state = Scene::Status::nothing;
    Scene* next_scene = nullptr;

    TextButton level_edit_button = TextButton(sf::Rect<int>(10, size.y - 340, 300, 50), core::StringProvider::get("mainmenu.level_editor_button"));
    TextButton tile_editor_button = TextButton(sf::Rect<int>(10, size.y - 280, 300, 50), core::StringProvider::get("mainmenu.tile_editor_button"));
    TextButton play_button = TextButton(sf::Rect<int>(10, size.y - 220, 300, 50), core::StringProvider::get("mainmenu.new_game_button"));
    TextButton options_button = TextButton(sf::Rect<int>(10, size.y - 160, 300, 50), core::StringProvider::get("mainmenu.options_button"));
    TextButton exit_button = TextButton(sf::Rect<int>(10, size.y - 100, 300, 50), core::StringProvider::get("mainmenu.exit_button"));
    ButtonGroup menu;

    bool first_loop = true;
};

#endif // MAINMENUSCENE_H
