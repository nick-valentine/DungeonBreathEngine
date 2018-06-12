#include "Element.h"

namespace ui {
    Element::Element(sf::IntRect pos) : rect(pos)
    {
    }

    void Element::set_pos(sf::IntRect pos)
    {
        this->rect = pos;
    }

    sf::IntRect Element::get_pos() const
    {
        return this->rect;
    }


    void Element::set_mode(InputMode mode)
    {
        this->mode = mode;
    }

    InputMode Element::get_mode() const
    {
        return this->mode;
    }

    EReturn Element::signal()
    {
        EReturn r;
        r.type = EType::NONE;
        r.iVal = 0;
        return r;
    }

};
