#include "FreeText.h"

FreeText::FreeText(sf::IntRect pos) : TextButton(pos, "")
{

}

void FreeText::update(int delta, Input *input, sf::RenderWindow &window)
{
    TextButton::update(delta, input, window);
}

void FreeText::draw(sf::RenderWindow &window)
{
    TextButton::draw(window);
}
