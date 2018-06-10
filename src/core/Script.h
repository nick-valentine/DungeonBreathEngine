#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

#include "Macros.h"
#include "Exceptions.h"
#include "Container.h"
#include "lua.h"

namespace core {
    // @todo: merge into lua.h
    class Script
    {
    public:
        Script() = default;
        Script(std::string filename);
        ~Script();

        void call();
        /* assumes that the table is at the stack top */
        std::string get_field(std::string key);

        std::string name;
        lua_State * s = nullptr;
    };
};

#endif //SCRIPT_H

