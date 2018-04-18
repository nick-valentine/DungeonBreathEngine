#include "ButtonGroup.h"

void ButtonGroup::add_button(std::string name, Button *b) 
{
	this->buttons.push_back(id_button(name, b));
}

void ButtonGroup::update(int delta, Input *input, sf::RenderWindow &window)
{
	for (const auto &i : this->buttons) {
		i.second->update(delta, window);
	}

	if (input->is_key_pressed(input->down)) {
		gamepad = true;
		selected = std::min(selected + 1, int(buttons.size()) - 1);
	}
	if (input->is_key_pressed(input->up)) {
		gamepad = true;
		selected = std::max(selected - 1, 0);
	}

	if (gamepad) {
		for (const auto &i : this->buttons) {
			i.second->set_hover(false);
		}

		buttons[selected].second->set_hover(true);
		if (input->is_key_pressed(input->accept)) {
			buttons[selected].second->set_pressed(true);
		}
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