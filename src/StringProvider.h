#ifndef STRINGPROVIDER_H
#define STRINGPROVIDER_H

#include <SFML/System.hpp>

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <codecvt>
#include <cuchar>
#include <cassert>

class StringProvider
{
public:
    StringProvider() = delete;

    static void load(std::string lang);

    static sf::String get(std::string key);
private:

    static std::map<std::string, sf::String> strings;

    static sf::String build_string(std::string s);
};

#endif //STRINGPROVIDER_H
