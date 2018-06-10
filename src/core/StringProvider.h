#ifndef STRINGPROVIDER_H
#define STRINGPROVIDER_H

#include <SFML/System.hpp>

#include "Strings.h"

#include <string>
#include <fstream>
#include <map>
#include <vector>

class StringProvider
{
public:
    StringProvider() = delete;

    static void load(std::string lang);

    static sf::String get(std::string key);
private:

    static std::map<std::string, sf::String> strings;
};

#endif //STRINGPROVIDER_H
