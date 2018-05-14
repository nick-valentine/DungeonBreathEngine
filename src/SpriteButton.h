#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H

#include "TextureMap.h"
#include "Button.h"

class SpriteButton : public Button
{
public:
    SpriteButton(
        sf::Rect<int> pos, 
        sf::Texture *tex,
        sf::IntRect normal,
        sf::IntRect hover,
        sf::IntRect press
    );

    void draw(sf::RenderWindow &window);
private:
    sf::Texture *tex;
    sf::Sprite normal;
    sf::Sprite hover;
    sf::Sprite press;
};

namespace ui {
    SpriteButton left(sf::IntRect pos);
    SpriteButton right(sf::IntRect pos);
};

#endif //SPRITEBUTTON_H
