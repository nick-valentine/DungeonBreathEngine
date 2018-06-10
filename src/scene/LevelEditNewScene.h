#ifndef LEVELEDITNEWSCENE_H
#define LEVELEDITNEWSCENE_H

#include "Container.h"
#include "KeyboardScene.h"
#include "StringProvider.h"
#include "ui.h"
#include "Scene.h"
#include "Index.h"

class LevelEditNewScene : public Scene
{
public:
    enum player_state {
        in_menu = 0,
        in_keyboard
    };
    LevelEditNewScene(sf::Vector2i size);
    ~LevelEditNewScene() = default;

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    void update_menu(int delta, sf::RenderWindow &window);
    void draw_menu(sf::RenderWindow &window);
    void update_keyboard(int delta, sf::RenderWindow &window);
    void draw_keyboard(sf::RenderWindow &window);

    void write_level_meta();
    sf::View main_window;

    Index index = Index(LEVELDIR);

    Scene::Status state = Scene::nothing;
    Scene *next_scene = nullptr;

    Label name_label = Label(sf::IntRect(100, 100, 300, 50), StringProvider::get("levelnewmenu.name"));
    Label spritesheet_label = Label(sf::IntRect(100, 160, 300, 50), StringProvider::get("levelnewmenu.spritesheet"));

    TextButton *current_button = nullptr;
    
    ButtonGroup menu;
    TextButton name = TextButton(sf::IntRect(400, 100, 300, 50), "");
    TextButton spritesheet = TextButton(sf::IntRect(400, 160, 300, 50), "");

    TextButton proceed = TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), StringProvider::get("levelnewmenu.proceed"));
    TextButton back = TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("levelnewmenu.back"));

    player_state pl_state = in_menu;
    KeyboardScene keyboard;
};

#endif //LEVELEDITNEWSCENEE_H
