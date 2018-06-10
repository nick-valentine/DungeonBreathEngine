#include "DeviceButton.h"

KeyboardButton::KeyboardButton(sf::Keyboard::Key k) : DeviceButton(), key(k)
{
}

bool KeyboardButton::is_pressed()
{
    return sf::Keyboard::isKeyPressed(key);
}

JoystickButton::JoystickButton(int number, bool is_axis, int min_value, int button) :
    DeviceButton(), number(number), is_axis(is_axis), min_value(min_value), button(button)
{
}

bool JoystickButton::is_pressed()
{
    if (is_axis) {
        if (min_value < 0) {
            return sf::Joystick::getAxisPosition(number, sf::Joystick::Axis(button)) < min_value;
        }
        return sf::Joystick::getAxisPosition(number, sf::Joystick::Axis(button)) > min_value;
    }
    return sf::Joystick::isButtonPressed(number, button);
}
