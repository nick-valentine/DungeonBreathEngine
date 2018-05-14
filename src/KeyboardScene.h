#ifndef KEYBOARDSCENE_H
#define KEYBOARDSCENE_H

#include <string>

#include "Scene.h"
#include "KeyButton.h"
#include "Label.h"

class KeyboardScene : public Scene
{
public:
    KeyboardScene(sf::Vector2i size);
    ~KeyboardScene();

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();

    void set_input(sf::String input);
    sf::String get_input();
private:
    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    sf::String input;
    Label input_label;

    std::vector<KeyButton> buttons;
    std::vector<bool> last_pressed;
};

#endif ///KEYBOARDSCENE_H
