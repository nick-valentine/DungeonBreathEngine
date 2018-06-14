#ifndef SCRIPT_CORE_H
#define SCRIPT_CORE_H

#include "lua.h"
#include "core.h"

namespace lua {
    namespace config {
        void add(lua_State *L);
        int get_int(lua_State *L);
        int get_string(lua_State *L);
        int set(lua_State *L);
        int save(lua_State *L);
    };

    namespace container {
        void add(lua_State *L);
    };

    namespace input {
        void add(lua_State *L);
        int is_key_pressed(lua_State *L);
    };

    namespace lang {
        void add(lua_State *L);
        int next(lua_State *L);
        int prev(lua_State *L);
    }

    namespace logger {
        void add(lua_State *s);
        int debug(lua_State *s);
        int info(lua_State *s);
        int warn(lua_State *s);
        int error(lua_State *s);
        // log is to help the other functions, not to be added to lua
        int log(core::Logger::LogLevel level, lua_State *s);
    };

};

#endif //SCRIPT_CORE_H

