#ifndef SCRIPT_CORE_H
#define SCRIPT_CORE_H

#include "Container.h"
#include "core.h"
#include "lua.h"

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
		int get_input(lua_State *L);
		int set_active_joystick(lua_State *L);
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

    namespace index {
        extern Container<core::Index> container;
        void add(lua_State *L);

        int get(lua_State *L);
        int release(lua_State *L);
        int insert(lua_State *L);
        int remove(lua_State *L);
        int save(lua_State *L);
        int all(lua_State *L);
    };

};

#endif //SCRIPT_CORE_H

