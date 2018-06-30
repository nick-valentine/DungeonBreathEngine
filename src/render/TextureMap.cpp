#include "TextureMap.h"

namespace render {
    sf::Texture instance(std::string file_name) {
        sf::Texture temp;
        if (!temp.loadFromFile(file_name)) {
            throw core::FileNotFoundException();
        }
        return temp;
    }
};
