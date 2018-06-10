#ifndef KeyBUTTON_H
#define KeyBUTTON_H

#include "render.h"
#include "Button.h"
#include "Label.h"

class KeyButton : public Button
{
public:
    KeyButton(sf::Rect<int> pos, sf::String contents);
    void draw(sf::RenderWindow &window);

    void set_label(sf::String contents);
    sf::String get_label();
private:
    Label label;
};


#endif //KEYBUTTON_H
