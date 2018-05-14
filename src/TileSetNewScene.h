#ifndef TILESETNEWSCENE_H
#define TILESETNEWSCENE_H

#include <vector>
#include <fstream>

#include "Macros.h"
#include "Exceptions.h"
#include "Strings.h"
#include "Scene.h"
#include "TextButton.h"
#include "FreeText.h"
#include "ButtonGroup.h"
#include "StringProvider.h"

class TileSetNewScene : public Scene
{
public:
    TileSetNewScene(sf::Vector2i size);
    ~TileSetNewScene();

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    ButtonGroup menu;
    FreeText name;
    TextButton proceed;
    TextButton back;
};


#endif //TILESETNEWSCENE_H
