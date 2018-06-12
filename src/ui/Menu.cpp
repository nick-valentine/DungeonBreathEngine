#include "Menu.h"

namespace ui {
    MenuItem::MenuItem(std::string tag, element_ptr me) : Element(sf::IntRect(0, 0, 0, 0)), tag(tag), me(me)
    {
    }

    void MenuItem::update(int delta, sf::RenderWindow &window)
    {
        me->update(delta, window);
    }

    void MenuItem::draw(sf::RenderWindow &window)
    {
        me->draw(window);
    }

    void MenuItem::set_mode(InputMode mode)
    {
        me->set_mode(mode);
        Element::set_mode(mode);
    }

    element_ptr MenuItem::raw()
    {
        return me;
    }

    void MenuItem::set_up(element_ptr x)
    {
        set_side(side::up, x);
    }

    void MenuItem::set_down(element_ptr x)
    {
        set_side(side::down, x);
    }

    void MenuItem::set_left(element_ptr x)
    {
        set_side(side::left, x);
    }

    void MenuItem::set_right(element_ptr x)
    {
        set_side(side::right, x);
    }

    void MenuItem::set_side(side s, element_ptr x)
    {
        auto i = std::dynamic_pointer_cast<MenuItem>(x);
        sides[s] = i;
    }

    Menu::Menu() : Element(sf::IntRect(0, 0, 0, 0))
    {
        last_input = std::vector<bool>(core::Input::Key::num_keys, false);
    }

    void Menu::update(int delta, sf::RenderWindow &window)
    {
        // check for mouse movement
        sf::Vector2i mouse_pos = sf::Mouse::getPosition();
        if (last_mouse_pos != mouse_pos) {
            this->set_mode(InputMode::mouse);
            for (const auto &i : this->menu_items) {
                i->set_mode(InputMode::mouse);
            }
        }
        last_mouse_pos = mouse_pos;

        // check pad movement
        auto input = core::app_container.get_input()->poll_all();
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] && !last_input[i]) {
                this->set_mode(InputMode::pad);
                switch (i) {
                case core::Input::Key::up:
                    move_side(MenuItem::side::up);
                    break;
                case core::Input::Key::down:
                    move_side(MenuItem::side::down);
                    break;
                case core::Input::Key::left:
                    move_side(MenuItem::side::left);
                    break;
                case core::Input::Key::right:
                    move_side(MenuItem::side::right);
                    break;
                }
            }
        }
        last_input = input;

        if (this->get_mode() == InputMode::pad) {
            for (const auto &i : this->menu_items) {
                i->set_mode(InputMode::pad);
                auto b = std::dynamic_pointer_cast<Button>(i->raw());
                if (b != nullptr) {
                    b->set_hover(false);
                }
            }
            if (current != nullptr) {
                auto curr = std::dynamic_pointer_cast<Button>(current->raw());
                if (curr != nullptr) {
                    curr->set_hover(true);
                }
            }
        }

        for (const auto &i : menu_items) {
            i->update(delta, window);
        }
    }

    void Menu::draw(sf::RenderWindow &window)
    {
        for (const auto &i : menu_items) {
            i->draw(window);
        }
    }

    void Menu::set_current(element_ptr x)
    {
        auto m = std::dynamic_pointer_cast<MenuItem>(x);
        current = m;
    }

    element_ptr Menu::add_text_button(std::string tag, sf::Vector2i pos, sf::String content_key)
    {
        auto x = menu_item_ptr(
            new MenuItem(tag, element_ptr(
                new TextButton(
                    sf::IntRect(pos.x, pos.y, 300, 50), 
                    core::StringProvider::get(content_key))
            ))
        );
        menu_items.push_back(x);
        return x;
    }

    void Menu::move_side(MenuItem::side s)
    {
        auto i = std::dynamic_pointer_cast<MenuItem>(current);
        if (i == nullptr) {
            return;
        }

        current = i->sides[s];
    }
};
