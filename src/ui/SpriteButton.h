#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H

#include "render.h"
#include "Button.h"

namespace ui {
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
};

#endif //SPRITEBUTTON_H
