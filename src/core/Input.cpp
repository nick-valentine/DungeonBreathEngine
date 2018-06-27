#include "Input.h"

#define MIN_AXIS_TRIGGER 40

namespace core {

    const std::vector<std::string> Input::config_options = {
        "move_up",
        "move_down",
        "move_left",
        "move_right",
        "escape",
        "accept",
        "fire",
        "alt_fire",
        "next",
        "prev"
    };

    const std::vector<std::string> Input::config_options_defaults = {
        "k:w",
        "k:s",
        "k:d",
        "k:a",
        "k:esc",
        "k:enter",
        "k:space",
        "k:num1",
        "k:num2",
        "k:num3"
    };

    Input::Input() : buttons()
    {
        // these buttons must be inserted in the same order as the key enum
        // for the update function to work properly
        for (size_t i = 0; i < config_options.size(); ++i) {
            std::string key = ConfigLoader::get_string_option(
                config_options[i],
                config_options_defaults[i]
            );
            buttons.push_back(parse_dsn(key));
        }
    }

    Input::~Input()
    {
        for (size_t i = 0; i < buttons.size(); ++i) {
            delete buttons[i];
        }
    }

    bool Input::is_key_pressed(Key k)
    {
        return buttons[k]->is_pressed(this->active_joystick);
    }

    std::vector<bool> Input::poll_all()
    {
        std::vector<bool> presses;
        for (int i = up; i < num_keys; ++i) {
            presses.push_back(is_key_pressed(Key(i)));
        }
        return presses;
    }

	void Input::set_active_joystick(int stick)
	{
		this->active_joystick = stick;
	}

	std::string Input::get_input()
	{
		for (auto i = sf::Keyboard::Key(0); i < sf::Keyboard::KeyCount; i = sf::Keyboard::Key(i+1)) {
			if (sf::Keyboard::isKeyPressed(i)) {
				std::stringstream ss;
				ss << "k:" << i;
				return ss.str();
			}
		}

		for (auto i = 0; i < sf::Joystick::Count; ++i) {
			if (!sf::Joystick::isConnected(i)) {
				continue;
			}
			for (auto j = 0; j < sf::Joystick::ButtonCount; ++j) {
				if (sf::Joystick::isButtonPressed(i, j)) {
					std::stringstream ss;
					ss << "j:b:" << j;
					this->set_active_joystick(i);
					return ss.str();
				}
			}
			for (auto j = sf::Joystick::Axis(0); j <= sf::Joystick::PovY; j = sf::Joystick::Axis(j+1)) {
				if (sf::Joystick::hasAxis(i, j)) {
					auto pos = sf::Joystick::getAxisPosition(i, j);
					if (pos > MIN_AXIS_TRIGGER) {
						std::stringstream ss;
						ss << "j:a:40:" << j;
						this->set_active_joystick(i);
						return ss.str();
					} else if (pos < -MIN_AXIS_TRIGGER) {
						std::stringstream ss;
						ss << "j:a:-40:" << j;
						this->set_active_joystick(i);
						return ss.str();
					}
				}
			}
		}
		return "";
	}

    /**
     * The dsn for keyboard inputs should be trivially simple:
     * <input device>:[<axis or button>]:[min value]:<specific button>
     * input device:
     *  - k: keyboard
     *  - j: joystick
     * axis or button:
     *  - a: axis
     *  - b: button
     * min value: smallest acceptable value to trigger a press for axis
     * input number: when more than one input device of a type can exist, this denotes which one to use
     * specific button: either number or letter defining which button to listen to
     */
    DeviceButton *Input::parse_dsn(std::string dsn)
    {
        if (dsn[0] == 'k') {
            return parse_keyboard_dsn(dsn);
        }

        if (dsn[0] == 'j') {
            return parse_joystick_dsn(dsn);
        }
        return nullptr;
    }


    DeviceButton *Input::parse_keyboard_dsn(std::string dsn)
    {
        std::string key = dsn.substr(dsn.find(':') + 1);
		int k;
		std::stringstream ss(key);
		ss >> k;
        if (k >= 0 && k < sf::Keyboard::KeyCount) {
            return new KeyboardButton(sf::Keyboard::Key(k));
        }
        throw InvalidConfigException();
    }

    DeviceButton *Input::parse_joystick_dsn(std::string dsn)
    {
        for (size_t i = 0; i < dsn.size(); ++i) {
            if (dsn[i] == ':') {
                dsn[i] = ' ';
            }
        }
        std::stringstream ss;
        ss.str(dsn);
        char device, axis;
        int number, button, min_value;
        ss>>device>>axis>>min_value>>button;
        return new JoystickButton(number, axis, min_value, button);
    }
};



