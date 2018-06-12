#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>

#include "core.h"

namespace ui {
    enum InputMode {
        pad = 0,
        mouse,
    };

    enum EType {
        NONE = 0,
        INT,
        STRING,
    };

    struct EReturn {
        EType type;
        int iVal;
        std::string sVal;
    };

    class Element
    {
    public:
        Element(sf::IntRect pos);
        virtual ~Element() = default;

        virtual void update(int delta, sf::RenderWindow &window) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;

        virtual void set_pos(sf::IntRect pos);
        virtual sf::IntRect get_pos() const;

        virtual void set_mode(InputMode mode);
        virtual InputMode get_mode() const;

        virtual EReturn signal();
    private:
        sf::IntRect rect;
        InputMode mode = InputMode::pad;
    };
};

#endif //ELEMENT_H
