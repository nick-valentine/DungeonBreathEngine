#ifndef TILESETSCENE_H
#define TILESETSCENE_H

#include <vector>
#include <fstream>
#include <filesystem>

#include "Macros.h"
#include "Exceptions.h"
#include "Strings.h"
#include "Scene.h"
#include "TextButton.h"
#include "ButtonGroup.h"
#include "StringProvider.h"

class TileSetScene : public Scene
{
public:
    TileSetScene(sf::Vector2i size);
    ~TileSetScene();

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
	void reset_status();
private:
    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    ButtonGroup menu;
    std::vector<TextButton> tilesets;
    TextButton new_set;
    TextButton back;
};

#endif //TILESETSCENE_H
