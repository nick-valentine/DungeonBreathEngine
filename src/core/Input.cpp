#include "Input.h"

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

Input::Input() : key_map(), buttons()
{
    populate_key_map();
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
    return buttons[k]->is_pressed();
}

std::vector<bool> Input::poll_all()
{
    std::vector<bool> presses;
    for (int i = up; i < num_keys; ++i) {
        presses.push_back(is_key_pressed(Key(i)));
    }
    return presses;
}

/**
 * The dsn for keyboard inputs should be trivially simple:
 * <input device>:[<input number>]:[<axis or button>]:[min value]:<specific button>
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
    if (key_map.find(key) != key_map.end()) {
        return new KeyboardButton(sf::Keyboard::Key(key_map[key]));
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
    ss>>device>>number>>axis>>min_value>>button;
    return new JoystickButton(number, axis, min_value, button);
}

// @todo: there's probably a better way to do this
void Input::populate_key_map()
{
    key_map["a"] = sf::Keyboard::A;
    key_map["b"] = sf::Keyboard::B;
    key_map["c"] = sf::Keyboard::C;
    key_map["d"] = sf::Keyboard::D;
    key_map["e"] = sf::Keyboard::E;
    key_map["f"] = sf::Keyboard::F;
    key_map["g"] = sf::Keyboard::G;
    key_map["h"] = sf::Keyboard::H;
    key_map["i"] = sf::Keyboard::I;
    key_map["j"] = sf::Keyboard::J;
    key_map["k"] = sf::Keyboard::K;
    key_map["l"] = sf::Keyboard::L;
    key_map["m"] = sf::Keyboard::M;
    key_map["n"] = sf::Keyboard::N;
    key_map["o"] = sf::Keyboard::O;
    key_map["p"] = sf::Keyboard::P;
    key_map["q"] = sf::Keyboard::Q;
    key_map["r"] = sf::Keyboard::R;
    key_map["s"] = sf::Keyboard::S;
    key_map["t"] = sf::Keyboard::T;
    key_map["u"] = sf::Keyboard::U;
    key_map["v"] = sf::Keyboard::V;
    key_map["w"] = sf::Keyboard::W;
    key_map["x"] = sf::Keyboard::X;
    key_map["y"] = sf::Keyboard::Y;
    key_map["z"] = sf::Keyboard::Z;
    key_map["num0"] = sf::Keyboard::Num0;
    key_map["num1"] = sf::Keyboard::Num1;
    key_map["num2"] = sf::Keyboard::Num2;
    key_map["num3"] = sf::Keyboard::Num3;
    key_map["num4"] = sf::Keyboard::Num4;
    key_map["num5"] = sf::Keyboard::Num5;
    key_map["num6"] = sf::Keyboard::Num6;
    key_map["num7"] = sf::Keyboard::Num7;
    key_map["num8"] = sf::Keyboard::Num8;
    key_map["num9"] = sf::Keyboard::Num9;
    key_map["esc"] = sf::Keyboard::Escape;
    key_map["numpad0"] = sf::Keyboard::Numpad0;
    key_map["numpad1"] = sf::Keyboard::Numpad1;
    key_map["numpad2"] = sf::Keyboard::Numpad2;
    key_map["numpad3"] = sf::Keyboard::Numpad3;
    key_map["numpad4"] = sf::Keyboard::Numpad4;
    key_map["numpad5"] = sf::Keyboard::Numpad5;
    key_map["numpad6"] = sf::Keyboard::Numpad6;
    key_map["numpad7"] = sf::Keyboard::Numpad7;
    key_map["numpad8"] = sf::Keyboard::Numpad8;
    key_map["numpad9"] = sf::Keyboard::Numpad9;
    key_map["up"] = sf::Keyboard::Up;
    key_map["down"] = sf::Keyboard::Down;
    key_map["left"] = sf::Keyboard::Left;
    key_map["right"] = sf::Keyboard::Right;
    key_map["space"] = sf::Keyboard::Space;
    key_map["enter"] = sf::Keyboard::Return;
}


void lua::input::add(Input *i, lua_State *s)
{
	static const struct luaL_Reg mylib[] = {
		{ "is_key_pressed", is_key_pressed },
		{ NULL, NULL }
	};
	lua_getglobal(s, "input");
	if (lua_isnil(s, -1)) {
		lua_pop(s, 1);
		lua_newtable(s);
	}
	luaL_setfuncs(s, mylib, 0);

	lua_pushlightuserdata(s, i);
	lua_setfield(s, -2, "device");

	lua_pushnumber(s, Input::up);
	lua_setfield(s, -2, "up");

	lua_pushnumber(s, Input::down);
	lua_setfield(s, -2, "down");

	lua_pushnumber(s, Input::left);
	lua_setfield(s, -2, "left");

	lua_pushnumber(s, Input::right);
	lua_setfield(s, -2, "right");

	lua_pushnumber(s, Input::escape);
	lua_setfield(s, -2, "escape");

	lua_pushnumber(s, Input::accept);
	lua_setfield(s, -2, "accept");

	lua_pushnumber(s, Input::fire);
	lua_setfield(s, -2, "fire");

	lua_pushnumber(s, Input::alt_fire);
	lua_setfield(s, -2, "alt_fire");

	lua_pushnumber(s, Input::num_keys);
	lua_setfield(s, -2, "num_keys");

	lua_setglobal(s, "input");
}

int lua::input::is_key_pressed(lua_State *s)
{
	Input *i = (Input *)lua_touserdata(s, 1);
	if (!lua_isnumber(s, 2)) {
		error(s, "arg 2 expected to be number");
	}
	auto key = (int) lua_tonumber(s, 2);
	
	auto pressed = i->is_key_pressed(Input::Key(key));

	lua_pushnumber(s, pressed);

	return 1;
}
