#ifndef NUMBERINPUT_H
#define NUMBERINPUT_H

#include "Label.h"
#include "Strings.h"
#include "SpriteButton.h"
#include "ButtonGroup.h"

class NumberInput
{
public:
    NumberInput(sf::Vector2i pos, sf::String label, int max, int min, int step = 1);

    void add(std::string name, ButtonGroup &group);
    // as is it meant to be used by a ButtonGroup
    // update takes the output of functions such as
    // neg_edge_button
    // it is expected that left and right will be externally
    // updated
    void update(std::string pressed);
    void draw(sf::RenderWindow &window);

    int value() const;
    void set_value(int v);

    void set_fmt_string(std::string fmt);
private:
    void update_label();
    Label l;
    SpriteButton left;
    SpriteButton right;
    std::string name;
    std::string fmt_string = ": %d";

    sf::String label_string;
    int v;
    int min;
    int max;
    int step;
};

#endif //NUMBERINPUT_H
