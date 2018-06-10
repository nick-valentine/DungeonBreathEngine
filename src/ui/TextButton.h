#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "render.h"
#include "Button.h"
#include "Label.h"

class TextButton : public Button
{
public:
    TextButton(sf::Rect<int> pos, sf::String contents);
    void draw(sf::RenderWindow &window);

    sf::String get_label();
    void set_label(sf::String contents);
private:
    Label label;

    sf::Texture *background;
    sf::Sprite back;
    sf::Sprite back_hover;
    sf::Sprite back_press;

};


#endif //TEXTBUTTON_H
