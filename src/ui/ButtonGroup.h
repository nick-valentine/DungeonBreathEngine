#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "Button.h"
#include "core.h"

// @todo: delete
namespace ui {
    class ButtonGroup
    {
    public:
        ButtonGroup() = default;
        ~ButtonGroup() = default;

        ButtonGroup(const ButtonGroup &o) = delete;
        ButtonGroup *operator=(const ButtonGroup &o) = delete;
        ButtonGroup(const ButtonGroup &&o) = delete;
        ButtonGroup *operator=(const ButtonGroup &&o) = delete;


        void add_button(std::string name, Button *b);

        void update(int delta, core::Input *input, sf::RenderWindow &window);
        void draw(sf::RenderTarget &window);

        std::string pressed_button();
        std::string neg_edge_button();
    private:
        typedef std::pair<std::string, Button*> id_button;
        // vector of pair used here rather than map to preserve ordering
        std::vector<id_button> buttons;

        bool gamepad = false;
        int selected = 0;

        bool last_up = false;
        bool last_down = false;

        sf::Vector2i last_mouse_pos;
    };
};

#endif //BUTTONGROUP_H
