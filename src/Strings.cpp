#include "Strings.h"

#if DEBUG
#include <iostream>
#endif

sf::String Strings::utf8_to_sfml(std::string s)
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
            #if DEBUG
            std::cout<<"encoding error\n";
            #endif
            break;
        }
        if(rc == (std::size_t)-2) {
            #if DEBUG
            std::cout<<"no read\n";
            #endif
            break;
        }
        ptr += rc;
    }
    return out;
}
