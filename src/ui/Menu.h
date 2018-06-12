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

        EReturn signal();

        virtual void set_mode(InputMode mode);

        element_ptr raw();

        void set_up(element_ptr x);
        void set_down(element_ptr x);
        void set_left(element_ptr x);
        void set_right(element_ptr x);

        std::string get_tag() const;
    private:
        void set_side(side s, element_ptr x, bool recurse = true);
        inline side opposite(side s);
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

        menu_item_ptr add_text_button(std::string tag, sf::Vector2i pos, sf::String content_key);

        bool has_signal();
        std::string signal_str();
        std::string signal_tag();
        int signal_int();

        std::vector<menu_item_ptr> *get();

    private:
        void move_side(MenuItem::side s);
        std::vector<menu_item_ptr> menu_items = std::vector<menu_item_ptr>();
        menu_item_ptr current = nullptr;

        std::vector<bool> last_input;

        sf::Vector2i last_mouse_pos = sf::Vector2i();

        bool signal_caught = false;
        std::string str_signal = "";
        std::string tag_signal = "";
        int int_signal = -1;
    };
};

#endif //MENU_H
