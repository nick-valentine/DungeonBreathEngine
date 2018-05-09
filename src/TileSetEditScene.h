#ifndef TILESETEDITSCENE_H
#define TILESETEDITSCENE_H

#include <vector>
#include <fstream>

#include "Macros.h"
#include "Exceptions.h"
#include "Strings.h"
#include "Scene.h"
#include "TextButton.h"
#include "ButtonGroup.h"
#include "StringProvider.h"
#include "Label.h"

class TileSetEditScene : public Scene
{
public:
    TileSetEditScene(sf::Vector2i size, std::string tileset);
    ~TileSetEditScene();

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    ButtonGroup menu;
    std::string tileset;
    Label tileset_label;
    TextButton back;
};

#endif //TILESETEDITSCENE_H
