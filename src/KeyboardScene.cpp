#include "KeyboardScene.h"

KeyboardScene::KeyboardScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    next_scene(nullptr),
    text_input(""),
    input_label(sf::IntRect(50,50,300,50), text_input),
    current(0)
{
    const int start_y = 100;
    const int step_y = 50;
    const int start_x = 50;
    const int step = size.x / 10;
    add_button_range('0', half_width*2, start_x, start_y);
    add_button_range('a', half_width, start_x, start_y + step_y);
    add_button_range('A', half_width, start_x + (half_width * step), start_y + step_y);
    add_button_range('a'+half_width, half_width, start_x, start_y + (step_y*2));
    add_button_range('A'+half_width, half_width, start_x + (half_width * step), start_y + (step_y*2));
    add_button_range('a'+(half_width*2), half_width, start_x, start_y + (step_y*3));
    add_button_range('A'+(half_width*2), half_width, start_x + (half_width * step), start_y + (step_y*3));
    add_button_range('a'+(half_width*3), half_width, start_x, start_y + (step_y*4));
    add_button_range('A'+(half_width*3), half_width, start_x + (half_width * step), start_y + (step_y*4));
    add_button_range('a'+(half_width*4), half_width, start_x, start_y + (step_y*5));
    add_button_range('A'+(half_width*4), half_width, start_x + (half_width * step), start_y + (step_y*5));
    add_button_range('a'+(half_width*5), 1, start_x, start_y + (step_y*6));
    add_button_range(' ', 1, start_x + step, start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*2), start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*3), start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*4), start_y + (step_y*6));
    add_button_range('A'+(half_width*5), 1, start_x + (half_width * step), start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*6), start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*7), start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*8), start_y + (step_y*6));
    add_button_range(' ', 1, start_x + (step*9), start_y + (step_y*6));
    add_button_range((char) 32, (half_width*2), start_x, start_y + (step_y*7));
    add_button_range((char) 42, 6, start_x, start_y + (step_y*8));
    buttons.push_back(KeyButton(sf::IntRect(100, size.y - 100, 300, 50), StringProvider::get("keyboard.backspace")));
    buttons.push_back(KeyButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("keyboard.back")));
}

KeyboardScene::~KeyboardScene()
{

}

void KeyboardScene::update(int delta, sf::RenderWindow &window)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition();
    if (last_mouse_pos != mouse_pos) {
        gamepad = false;
        for (auto &i : this->buttons) {
            i.reset_hover_override();
        }
    }
    last_mouse_pos = mouse_pos;

    auto down = app_container.get_input()->is_key_pressed(app_container.get_input()->down);
    if (down && !last_down) {
        gamepad = true;
        current = std::min(current + full_width, int(buttons.size()) - 1);
    }
    last_down = down;

    auto up = app_container.get_input()->is_key_pressed(app_container.get_input()->up);
    if (up && !last_up) {
        gamepad = true;
        current = std::max(current - full_width, 0);
    }
    last_up = up;

    auto left = app_container.get_input()->is_key_pressed(app_container.get_input()->left);
    if (left&& !last_left) {
        gamepad = true;
        current = std::max(current - 1, 0);
    }
    last_left = left;

    auto right = app_container.get_input()->is_key_pressed(app_container.get_input()->right);
    if (right && !last_right) {
        gamepad = true;
        current = std::min(current + 1, int(buttons.size()) - 1);
    }
    last_right  = right;

    if (gamepad) {
        for (auto &i : this->buttons) {
            i.set_hover(false);
        }

        buttons[current].set_hover(true);
    }

    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].update(delta, app_container.get_input(), window);

        auto pressed = buttons[i].pressed();
        if (!pressed && last_pressed[i]) {
            const auto backspace = buttons.size() - 2;
            const auto back = backspace+1;
            if (i == backspace) {
                if (this->text_input.getSize() > 0) {
                    this->text_input.erase(this->text_input.getSize() - 1);
                }
            } else if (i == back) {
                this->state = Scene::Status::switch_scene;
            } else {
                auto label = buttons[i].get_label();
                if (label == '_') {
                    label = ' ';
                }
                this->text_input += label;
            }
            this->input_label.set_string(this->text_input);
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

void KeyboardScene::reset_status()
{
    this->state = Scene::Status::nothing;
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
    this->text_input = input;
    this->input_label.set_string(this->text_input);
}

sf::String KeyboardScene::get_input()
{
    return this->text_input;
}

void KeyboardScene::add_button_range(char start, int count, int start_x, int start_y)
{
    const int step = size.x / 10;
    for (char i = start; i < start + count; ++i) {
        if (i == ' ') {
            buttons.push_back(KeyButton(sf::IntRect(((i - start) * step) + start_x, start_y, 50, 50), '_'));
        } else {
            buttons.push_back(KeyButton(sf::IntRect(((i - start) * step) + start_x, start_y, 50, 50), i));
        }
        last_pressed.push_back(false);
    }
}
