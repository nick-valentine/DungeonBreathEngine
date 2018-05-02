#ifndef STRINGPROVIDER_H
#define STRINGPROVIDER_H

#include <SFML/System.hpp>

#include <string>
#include <fstream>
#include <map>
#include <vector>

class StringProvider
{
public:
    StringProvider() = delete;

    static void load(std::wstring lang);

    static sf::String get(std::wstring key);
private:

    static std::map<std::wstring, sf::String> strings;
};

#endif //STRINGPROVIDER_H
