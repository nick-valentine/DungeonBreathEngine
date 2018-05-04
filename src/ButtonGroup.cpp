#include "ButtonGroup.h"

void ButtonGroup::add_button(std::string name, Button *b) 
{
	this->buttons.push_back(id_button(name, b));
}

void ButtonGroup::update(int delta, Input *input, sf::RenderWindow &window)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition();
	if (last_mouse_pos != mouse_pos) {
		gamepad = false;
		for (const auto &i : this->buttons) {
			i.second->reset_hover_override();
		}
	}
	last_mouse_pos = mouse_pos;

    auto down = input->is_key_pressed(input->down);
	if (down && !last_down) {
		gamepad = true;
		selected = std::min(selected + 1, int(buttons.size()) - 1);
	}
    last_down = down;

    auto up = input->is_key_pressed(input->up);
	if (up && !last_up) {
		gamepad = true;
		selected = std::max(selected - 1, 0);
	}
    last_up = up;

	if (gamepad) {
		for (const auto &i : this->buttons) {
			i.second->set_hover(false);
		}

		buttons[selected].second->set_hover(true);
	}

	for (const auto &i : this->buttons) {
		i.second->update(delta, input, window);
	}
}

void ButtonGroup::draw(sf::RenderWindow &window)
{
	for (const auto &i : this->buttons) {
		i.second->draw(window);
	}
}

std::string ButtonGroup::pressed_button()
{
	for (const auto &i : this->buttons) {
		if (i.second->pressed()) {
			return i.first;
		}
	}
	return "";
}
