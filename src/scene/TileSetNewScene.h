#ifndef TILESETNEWSCENE_H
#define TILESETNEWSCENE_H

#include <vector>
#include <fstream>

#include "Macros.h"
#include "Exceptions.h"
#include "Strings.h"
#include "Scene.h"
#include "KeyboardScene.h"
#include "ui.h"
#include "StringProvider.h"
#include "Index.h"

class TileSetNewScene : public Scene
{
public:
    enum player_state {
        in_menu = 0,
        in_keyboard
    };
    TileSetNewScene(sf::Vector2i size);
    ~TileSetNewScene() = default;

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

    void write_tileset_meta();

    sf::View main_window;

    Index index = Index(TILESETDIR);

    Scene::Status state = Scene::nothing;
    Scene *next_scene = nullptr;

    Label name_label = Label(sf::IntRect(100,100,300,50), StringProvider::get("tilesetnewmenu.name"));
    Label spritesheet_label = Label(sf::IntRect(100, 160, 300, 50), StringProvider::get("tilesetnewmenu.spritesheet"));
    Label base_size_label = Label(sf::IntRect(100, 220, 300, 50), StringProvider::get("tilesetnewmenu.base_size"));

    TextButton *current_button = nullptr;

    ButtonGroup menu;
    TextButton name = TextButton(sf::IntRect(400, 100, 300, 50), "");
    TextButton spritesheet = TextButton(sf::IntRect(400, 160, 300, 50), "");
    TextButton base_size = TextButton(sf::IntRect(400, 220, 300, 50), "");
    TextButton proceed = TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), StringProvider::get("tilesetnewmenu.proceed"));
    TextButton back = TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("tilesetnewmenu.back"));

    player_state pl_state = in_menu;
    KeyboardScene keyboard;
};


#endif //TILESETNEWSCENE_H
