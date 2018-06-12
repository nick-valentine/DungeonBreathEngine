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

    EReturn MenuItem::signal()
    {
        return me->signal();
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

    std::string MenuItem::get_tag() const
    {
        return tag;
    }

    void MenuItem::set_side(side s, element_ptr x)
    {
        auto i = std::dynamic_pointer_cast<MenuItem>(x);
        if (i == nullptr) {
            std::cout<<"attempting to set side as nil ptr: "<<s;
            return;
        }
        sides[s] = i;
    }

    MenuItem::side MenuItem::opposite(side s)
    {
        switch (s) {
        case up:
            return down;
        case down:
            return up;
        case left:
            return right;
        case right:
            return left;
        }
        return count;
    }

    void pair_items(element_ptr a, element_ptr b, MenuItem::side dir)
    {
        auto x = std::dynamic_pointer_cast<MenuItem>(a);
        auto y = std::dynamic_pointer_cast<MenuItem>(b);
        if (x == nullptr || y == nullptr) {
            return;
        }
        x->set_side(dir, b);
        y->set_side(y->opposite(dir), a);
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

        signal_caught = false;
        for (const auto &i : menu_items) {
            i->update(delta, window);
            auto s = i->signal();
            if (s.type != EType::NONE) {
                if (s.type != EType::NONE) {
                    signal_caught = true;
                    tag_signal = i->tag;
                    switch (s.type) {
                        case EType::INT:
                            int_signal = s.iVal;
                            break;
                        case EType::STRING:
                            str_signal = s.sVal;
                    }
                }
            }
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

    menu_item_ptr Menu::add_text_button(std::string tag, sf::Vector2i pos, sf::String content_key)
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

    bool Menu::has_signal()
    {
        return signal_caught;
    }

    std::string Menu::signal_str()
    {
        return str_signal;
    }

    std::string Menu::signal_tag()
    {
        return tag_signal;
    }

    int Menu::signal_int()
    {
        return int_signal;
    }

    std::vector<menu_item_ptr> *Menu::get()
    {
        return &this->menu_items;
    }

    void Menu::move_side(MenuItem::side s)
    {
        if (current == nullptr) {
            return;
        }

        auto next = current->sides[s].lock();
        if (next == nullptr) {
            return;
        }

        current = next;
    }
};
