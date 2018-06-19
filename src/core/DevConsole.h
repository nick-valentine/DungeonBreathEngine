#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

#include <SFML/Graphics.hpp>

#include <list>
#include <string>
#include "imgui.h"

namespace core {
    class DevConsole
    {
    public:
        DevConsole() = default;

        void write(std::string content);

        void imgui_draw(sf::Vector2i size);
    private:
        std::list<std::string> buffer = std::list<std::string>();
    };
};

#endif // DEVCONSOLE_H
