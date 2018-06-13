#ifndef MENU_H
#define MENU_H

#include <memory>
#include <vector>
#include <string>

#include "Element.h"
#include "TextButton.h"

#include "core.h"

namespace ui {
    class Menu;

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
        MenuItem(std::string tag, Element *me);
        virtual ~MenuItem();

        MenuItem(const MenuItem &other) = delete;
        MenuItem(const MenuItem &&other) = delete;
        MenuItem &operator=(const MenuItem &other) = delete;
        MenuItem &operator=(const MenuItem &&other) = delete;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        EReturn signal();

        virtual void set_mode(InputMode mode);

        Element *raw();

        void set_up(Element *x);
        void set_down(Element *x);
        void set_left(Element *x);
        void set_right(Element *x);
        void set_side(side s, Element *x);
        inline side opposite(side s);

        std::string get_tag() const;
    private:
        std::string tag;
        Element *me;
        MenuItem *sides[side::count];
    };

    void pair_items(Element * a, Element * b, MenuItem::side dir = MenuItem::side::down);

    class Menu : public Element
    {
    public:
        Menu();
        virtual ~Menu();

        Menu(const Menu &other) = delete;
        Menu(const Menu &&other) = delete;
        Menu &operator=(const Menu &other) = delete;
        Menu &operator=(const Menu &&other) = delete;

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        void set_current(Element * x);

        MenuItem *add_text_button(std::string tag, sf::Vector2i pos, sf::String content_key);

        bool has_signal();
        std::string signal_str();
        std::string signal_tag();
        int signal_int();

        std::vector<MenuItem *> *get();

    private:
        void move_side(MenuItem::side s);
        std::vector<MenuItem *> menu_items = std::vector<MenuItem *>();
        MenuItem *current = nullptr;

        std::vector<bool> last_input;

        sf::Vector2i last_mouse_pos = sf::Vector2i();

        bool signal_caught = false;
        std::string str_signal = "";
        std::string tag_signal = "";
        int int_signal = -1;
    };
};

#endif //MENU_H
