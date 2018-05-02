#include "StringProvider.h"

#include <iostream>

std::map<std::wstring, sf::String> StringProvider::strings;

void StringProvider::load(std::wstring lang)
{
    strings.clear();
    auto p = sf::String("./GameData/lang/") 
        + sf::String(lang) 
        + sf::String(".txt");
    std::wifstream ifile(p.toAnsiString().c_str());
    while (ifile.good()) {
        std::wstring line;
        std::getline(ifile, line);

        auto split = line.find_first_of(L"=");
        if (split != line.npos) {
            auto key = line.substr(0, split);
            auto val = line.substr(split+1);
            strings[key] = val;
        }
    }
}

sf::String StringProvider::get(std::wstring key)
{
    auto s = strings.find(key);
    if (s == strings.end()) {
        return sf::String("?");
    }
    return s->second;
}
