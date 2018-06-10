#ifndef KEYBOARDSCENE_H
#define KEYBOARDSCENE_H

#include <string>

#include "core.h"

#include "Scene.h"
#include "ui.h"

namespace scene {
    class Keyboard : public Scene
    {
    public:
        Keyboard(sf::Vector2i size);
        ~Keyboard();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        void reset_status();
        Scene::Status status();
        Scene *new_scene();

        void set_input(sf::String input);
        sf::String get_input();
    private:
        constexpr static int half_width = 5;
        constexpr static int full_width = half_width+half_width;
        void add_button_range(char start, int count, int start_x, int start_y);
        sf::View main_window;

        Scene::Status state;
        Scene *next_scene;

        sf::String text_input;
        Label input_label;

        bool gamepad = false;

        bool last_up = false;
        bool last_down = false;
        bool last_left = false;
        bool last_right = false;

        int current;
        sf::Vector2i last_mouse_pos;

        std::vector<KeyButton> buttons;
        std::vector<bool> last_pressed;
    };
};

#endif ///KEYBOARDSCENE_H
