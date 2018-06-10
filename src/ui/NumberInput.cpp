#include "NumberInput.h"

#define LABEL_WIDTH 250

namespace ui {
    NumberInput::NumberInput(sf::Vector2i pos, sf::String label, int max, int min, int step) :
        l(sf::IntRect(pos.x + 50, pos.y, LABEL_WIDTH, 50), label),
        left(ui::left(sf::IntRect(pos.x, pos.y, 50, 50))),
        right(ui::right(sf::IntRect(pos.x + LABEL_WIDTH + 50, pos.y, 50, 50))),
        label_string(label),
        v(min),
        min(min),
        max(max),
        step(step)
    {
        update_label();
    }

    void NumberInput::add(std::string name, ButtonGroup &group)
    {
        this->name = name;
        group.add_button(name + "_left", &left);
        group.add_button(name + "_right", &right);
    }

    void NumberInput::update(std::string pressed)
    {
        if (pressed == name+"_left") {
            v -= step;
            if (v < min) {
                v = min;
            }
            update_label();
        } else if (pressed == name+"_right") {
            v += step;
            if (v > max) {
                v = max;
            }
            update_label();
        }
    }

    void NumberInput::draw(sf::RenderWindow &window)
    {
        // left and right will be drawn by the button group
        l.draw(window);
    }

    int NumberInput::value() const
    {
        return v;
    }

    void NumberInput::set_value(int v)
    {
        this->v = v;
        update_label();
    }

    void NumberInput::set_fmt_string(std::string fmt)
    {
        fmt_string = fmt;
        update_label();
    }

    void NumberInput::update_label()
    {
        char new_label[50];
        sprintf(new_label, fmt_string.c_str(), v);
        sf::String ls = label_string + Strings::utf8_to_sfml(new_label);
        l.set_string(ls);
    }
};
