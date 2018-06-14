#ifndef STRINGPROVIDER_H
#define STRINGPROVIDER_H

#include <SFML/System.hpp>

#include "Strings.h"

#include <string>
#include <fstream>
#include <map>
#include <vector>

namespace core {
    typedef std::pair<std::string, sf::String> langpair;

    class StringProvider
    {
    public:
        StringProvider() = delete;

        static void load(std::string lang);
        static std::string next_lang();
        static std::string prev_lang();

        static sf::String get(std::string key);
    private:
        static void load_available();
        static void load_lang(std::string lang);
        static std::map<std::string, sf::String> strings;
        static std::vector<langpair> languages;
        static int current;
    };
};

#endif //STRINGPROVIDER_H
