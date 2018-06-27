#ifndef DEVICEBUTTON_H
#define DEVICEBUTTON_H

#include <SFML/Window.hpp>

namespace core {
    /**
     * This file defines strategies for gathering inputs from various devices
     * and turning them into game inputs. All device buttons must derive from
     * DeviceButton and provide a status on if a game input should be considered
     * activated or not in the is_pressed function.
     */

    class DeviceButton
    {
    public:
        DeviceButton() = default;
        virtual ~DeviceButton() = default;

        virtual bool is_pressed(int dev_id) = 0;
    private:
    };

    class KeyboardButton : public DeviceButton
    {
    public:
        KeyboardButton(sf::Keyboard::Key k);
        virtual ~KeyboardButton() = default;

        virtual bool is_pressed(int dev_id);
    private:
        sf::Keyboard::Key key;
    };

    class JoystickButton : public DeviceButton
    {
    public:
        JoystickButton(int number, bool is_axis, int min_value, int button);
        virtual ~JoystickButton() = default;

        virtual bool is_pressed(int dev_id);
    private:
        bool is_axis;
        int min_value;
        int button;
    };
};

#endif // DEVICEBUTTON_H
