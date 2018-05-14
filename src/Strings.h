#ifndef STRINGS_H
#define STRINGS_H

#include <SFML/System.hpp>

#include "Macros.h"

#include <string>
#include <cuchar>
#include <cassert>

namespace Strings {
    sf::String utf8_to_sfml(std::string s);
};

#endif //STRINGS_H
