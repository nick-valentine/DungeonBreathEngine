#ifndef FREETEXT_H
#define FREETEXT_H

#include "Input.h"
#include "TextButton.h"

// Refrain from using free text in any non-dev tools.
// @todo: Implement on screen keyboard for those.
class FreeText : public TextButton
{
public:
    FreeText(sf::IntRect pos);
    virtual ~FreeText() = default;

    virtual void update(int delta, Input *input, sf::RenderWindow &window);
    virtual void draw(sf::RenderWindow &window);
private:
    sf::String text;
};

#endif //FREETEXT_H
