#include "StringProvider.h"

#include <iostream>

std::map<std::string, sf::String> StringProvider::strings;

void StringProvider::load(std::string lang)
{
    strings.clear();
    auto p = sf::String("./GameData/lang/") 
        + sf::String(lang) 
        + sf::String(".txt");
    std::ifstream ifile(p.toAnsiString().c_str());
    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);

        auto split = line.find_first_of(u8"=");
        if (split != line.npos) {
            auto key = line.substr(0, split);
            auto val_part = line.substr(split+1);
            auto val = StringProvider::build_string(val_part);

            strings[key] = val;
        }
    }
}

sf::String StringProvider::get(std::string key)
{
    auto s = strings.find(key);
    if (s == strings.end()) {
        return sf::String("?");
    }
    return s->second;
}

sf::String StringProvider::build_string(std::string s)
{
    std::setlocale(LC_ALL, "en_US.utf8");

    std::mbstate_t state{}; // zero-initialized to initial state
    char32_t c32;
    const char *ptr = s.c_str(), *end = s.c_str() + s.size() + 1;
    sf::String out;

    while(std::size_t rc = std::mbrtoc32(&c32, ptr, end - ptr, &state))
    {
        out += sf::String(c32);
        assert(rc != (std::size_t)-3); // no surrogates in UTF-32
        if(rc == (std::size_t)-1) {
            std::cout<<"encoding error\n";
            break;
        }
        if(rc == (std::size_t)-2) {
            std::cout<<"no read\n";
            break;
        }
        ptr += rc;
    }
    return out;
}
