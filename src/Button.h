#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "TextureMap.h"
#include "FontMap.h"

class Button
{
public:
    Button() = default;
    Button(sf::Rect<int> pos, std::string contents);
    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    bool pressed();
	void set_hover(bool hover);
	void set_pressed(bool pressed);
private:
    bool was_pressed;
	bool is_hover;
    sf::Font *font;
    sf::Text text;
    sf::Rect<int> rect;

	sf::Texture *background;
	sf::Sprite back;
	sf::Sprite back_hover;
	sf::Sprite back_press;

    sf::RectangleShape debug_draw;
};

#endif // BUTTON_H
