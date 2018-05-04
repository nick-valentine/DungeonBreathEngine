#include "StringProvider.h"

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
            auto val = Strings::utf8_to_sfml(val_part);

            strings[key] = val;
        }
    }
    ifile.close();
}

sf::String StringProvider::get(std::string key)
{
    auto s = strings.find(key);
    if (s == strings.end()) {
        return sf::String("?");
    }
    return s->second;
}

