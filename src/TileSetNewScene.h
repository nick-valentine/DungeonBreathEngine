#ifndef TILESETNEWSCENE_H
#define TILESETNEWSCENE_H

#include <vector>
#include <fstream>

#include "Macros.h"
#include "Exceptions.h"
#include "Strings.h"
#include "Scene.h"
#include "KeyboardScene.h"
#include "TextButton.h"
#include "ButtonGroup.h"
#include "StringProvider.h"

class TileSetNewScene : public Scene
{
public:
    enum player_state {
        in_menu = 0,
        in_keyboard
    };
    TileSetNewScene(sf::Vector2i size);
    ~TileSetNewScene();

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    void update_menu(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw_menu(sf::RenderWindow &window);
    void update_keyboard(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw_keyboard(sf::RenderWindow &window);

    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    ButtonGroup menu;
    TextButton name;
    TextButton proceed;
    TextButton back;

    player_state pl_state;
    KeyboardScene keyboard;
};


#endif //TILESETNEWSCENE_H
