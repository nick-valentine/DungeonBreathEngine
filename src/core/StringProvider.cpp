#include "StringProvider.h"

namespace core {
    std::map<std::string, sf::String> StringProvider::strings;

    std::vector<langpair> StringProvider::languages;
    int StringProvider::current = 0;

    void StringProvider::load(std::string lang)
    {
        load_available();
        load_lang(lang);
    }

    sf::String StringProvider::get(std::string key)
    {
        auto s = strings.find(key);
        if (s == strings.end()) {
            return sf::String("?");
        }
        return s->second;
    }

    std::string StringProvider::next_lang()
    {
        current++;
        if (current == languages.size()) {
            current = 0;
        }
        load_lang(languages[current].first);
        return languages[current].first;
    }

    std::string StringProvider::prev_lang()
    {
        current--;
        if (current < 0) {
            current = languages.size() - 1;
        }
        load_lang(languages[current].first);
        return languages[current].first;
    }

    void StringProvider::load_available()
    {
        if (languages.size() == 0) {
            std::ifstream ifile(LANGDIR "supported.txt");
            while (ifile.good()) {
                std::string key, label;
                ifile>>key>>label;
                if (label != "") {
                    languages.push_back(langpair(key, Strings::utf8_to_sfml(label)));
                }
            }
            ifile.close();
        }
    }

    void StringProvider::load_lang(std::string lang)
    {
        strings.clear();
        std::string p("./GameData/lang/");
        p += lang;
        p += ".txt";
        std::ifstream ifile(p.c_str());
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
};
