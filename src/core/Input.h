#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "ConfigLoader.h"
#include "DeviceButton.h"
#include "Exceptions.h"

namespace core {
    class Input
    {
    public:
        enum Key {
            up = 0,
            down,
            left,
            right,
            escape,
            accept,
            fire,
            alt_fire,
            next,
            prev,
            num_keys
        };

        Input();
        ~Input();

        Input(const Input &other) = delete;
        Input operator=(const Input &other) = delete;
        Input(const Input &&other) = delete;
        Input operator=(const Input &&other) = delete;

        bool is_key_pressed(Key k);
        std::vector<bool> poll_all();
    private:
        const static std::vector<std::string> config_options;
        const static std::vector<std::string> config_options_defaults;

        DeviceButton* parse_dsn(std::string dsn);
        DeviceButton* parse_keyboard_dsn(std::string dsn);
        DeviceButton* parse_joystick_dsn(std::string dsn);
        void populate_key_map();

        std::map<std::string, int> key_map;
        std::vector<DeviceButton*> buttons;
    };
};

#endif // INPUT_H
