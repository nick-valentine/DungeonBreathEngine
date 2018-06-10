#include "Script.h"

namespace core {
    Script::Script(std::string filename)
    {
        this->name = filename;
        s = luaL_newstate();
        luaL_openlibs(s);
        lua::container::add(s);
        std::string full_path = SCRIPTDIR;
        full_path += filename;
        app_container.get_logger()->info("loading script %s", full_path.c_str());
        if (luaL_loadfile(s, full_path.c_str()) != 0) {
            throw FileNotReadableException();
        }
    }

    Script::~Script()
    {
        lua_close(s);
    }

    void Script::call()
    {
        lua_pcall(s, 0, 0, 0);
    }

    std::string Script::get_field(std::string key)
    {
        lua_pushstring(s, key.c_str());
        lua_gettable(s, -2);
        if (!lua_isstring(s, -1)) {
            lua::error(s, "value at key not string");
        }
        std::string str = lua_tostring(s, -1);
        lua_pop(s, 1);
        return str;
    }
};
