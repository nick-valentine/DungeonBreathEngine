#include "Menu.h"

namespace ui {
    MenuItem::MenuItem(std::string tag, Element *me) : Element(sf::IntRect(0, 0, 0, 0)), tag(tag), me(me)
    {
        for (int i = 0; i < side::count; ++i) {
            sides[i] = nullptr;
        }
    }

    MenuItem::~MenuItem()
    {
        delete this->me;
    }

    void MenuItem::update(int delta, sf::RenderWindow &window)
    {
        me->update(delta, window);
    }

    void MenuItem::draw(sf::RenderTarget &window)
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

    Element *MenuItem::raw()
    {
        return me;
    }

    void MenuItem::set_up(Element *x)
    {
        set_side(side::up, x);
    }

    void MenuItem::set_down(Element *x)
    {
        set_side(side::down, x);
    }

    void MenuItem::set_left(Element *x)
    {
        set_side(side::left, x);
    }

    void MenuItem::set_right(Element *x)
    {
        set_side(side::right, x);
    }

    std::string MenuItem::get_tag() const
    {
        return tag;
    }

    void MenuItem::set_side(side s, Element *x)
    {
        auto i = dynamic_cast<MenuItem*>(x);
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

    void pair_items(Element *a, Element *b, MenuItem::side dir)
    {
        auto x = dynamic_cast<MenuItem*>(a);
        auto y = dynamic_cast<MenuItem*>(b);
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

    Menu::~Menu()
    {
        for (size_t i = 0; i < menu_items.size(); ++i) {
            delete menu_items[i];
        }
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
                auto b = dynamic_cast<Button*>(i->raw());
                if (b != nullptr) {
                    b->set_hover(false);
                }
            }
            if (current != nullptr && current->raw() != nullptr) {
                auto curr = dynamic_cast<Button*>(current->raw());
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
                signal_caught = true;
                tag_signal = i->tag;
                switch (s.type) {
                    case EType::INT:
                        int_signal = s.iVal;
                        break;
                    case EType::STRING:
                        core::app_container.get_logger()->warn(s.sVal.c_str());
                        str_signal = s.sVal;
                }
            }
        }
    }

    void Menu::draw(sf::RenderTarget &window)
    {
        for (const auto &i : menu_items) {
            i->draw(window);
        }
    }

    void Menu::set_current(Element *x)
    {
        auto m = dynamic_cast<MenuItem*>(x);
        current = m;
    }

    MenuItem *Menu::add_sprite_button(std::string tag, sf::IntRect pos, std::string tex_name, sf::IntRect normal, sf::IntRect hover, sf::IntRect press)
    {
        tex_name = IMGDIR + tex_name;
        auto x = new MenuItem(tag,
            new SpriteButton(pos, render::TextureMap::request(tex_name), normal, hover, press)
        );
        menu_items.push_back(x);
        return x;
    }

    MenuItem *Menu::add_label(sf::IntRect pos, std::string content_key)
    {
        auto x = new MenuItem("",
            new Label(pos, core::StringProvider::get(content_key))
        );
        menu_items.push_back(x);
        return x;
    }

    MenuItem *Menu::add_label_raw(sf::IntRect pos, std::string contents)
    {
        auto x = new MenuItem("", new Label(pos, contents));
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

    std::vector<MenuItem *> *Menu::get()
    {
        return &this->menu_items;
    }

    void Menu::clear()
    {
        for (size_t i = 0; i < menu_items.size(); ++i) {
            delete menu_items[i];
        }
        menu_items.clear();
    }

    void Menu::move_side(MenuItem::side s)
    {
        if (current == nullptr) {
            if (menu_items.size() > 0) {
                current = menu_items[0];
            }
            return;
        }

        auto next = current->sides[s];
        if (next == nullptr) {
            return;
        }

        current = next;
    }
};
