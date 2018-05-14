#include "KeyboardScene.h"

KeyboardScene::KeyboardScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    next_scene(nullptr),
    input(""),
    input_label(sf::IntRect(10,10,300,50), input)
{
    for (char i = '0'; i <= '9'; ++i) {
        buttons.push_back(KeyButton(sf::IntRect(((i-'0') * 50) + 10, 100, 50, 50), i));
        last_pressed.push_back(false);
    }
}

KeyboardScene::~KeyboardScene()
{

}

void KeyboardScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].update(delta, input, window);

        auto pressed = buttons[i].pressed();
        if (!pressed && last_pressed[i]) {
            this->input += buttons[i].get_label();
            this->input_label.set_string(this->input);
        }
        last_pressed[i] = pressed;
    }
}

void KeyboardScene::draw(sf::RenderWindow &window)
{
    for (auto &i : buttons) {
        i.draw(window);
    }
    input_label.draw(window);
}

Scene::Status KeyboardScene::status()
{
    return this->state;
}

Scene *KeyboardScene::new_scene()
{
    return this->next_scene;
}

void KeyboardScene::set_input(sf::String input)
{
    this->input = input;
}

sf::String KeyboardScene::get_input()
{
    return this->input;
}
