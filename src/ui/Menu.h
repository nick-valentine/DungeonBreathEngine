#ifndef MENU_H
#define MENU_H

#include <memory>
#include <vector>
#include <string>

#include "Element.h"
#include "TextButton.h"

#include "core.h"

namespace ui {
    class MenuItem;
    class Menu;

    typedef std::shared_ptr<Element> element_ptr;
    typedef std::shared_ptr<MenuItem> menu_item_ptr;

    class MenuItem : public Element
    {
    friend class Menu;
    public:
        enum side {
            up = 0,
            down,
            left,
            right,
            count,
        };
        MenuItem(std::string tag, element_ptr me);
        virtual ~MenuItem() = default;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        virtual void set_mode(InputMode mode);

        element_ptr raw();

        void set_up(element_ptr x);
        void set_down(element_ptr x);
        void set_left(element_ptr x);
        void set_right(element_ptr x);
    private:
        void set_side(side s, element_ptr x);
        std::string tag;
        element_ptr me;
        menu_item_ptr sides[side::count];
    };

    class Menu : public Element
    {
    public:
        Menu();
        virtual ~Menu() = default;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        void set_current(element_ptr x);

        element_ptr add_text_button(std::string tag, sf::Vector2i pos, sf::String content_key);

    private:
        void move_side(MenuItem::side s);
        std::vector<menu_item_ptr> menu_items;
        menu_item_ptr current = nullptr;

        std::vector<bool> last_input;

        sf::Vector2i last_mouse_pos = sf::Vector2i();

        std::string str_return;
    };
};

#endif //MENU_H
