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
};
