#include "l_scene.h"

namespace lua {
    namespace l_scene {
        void add(lua_State *L)
        {
            static const struct luaL_Reg mylib[] = {
                { "push", push },
                { "pop", pop },
                { NULL, NULL },
            };
            lua_getglobal(L, "scene");
            if (lua_isnil(L, -1)) {
                lua_pop(L, 1);
                lua_newtable(L);
            }
            luaL_setfuncs(L, mylib, 0);

            lua_setglobal(L, "scene");
        }

        int push(lua_State *L)
        {
            scene::Scene *s = (scene::Scene *)lua_touserdata(L, -2);
            auto name = lua::get_string(L, -1);
            s->indicate_push(name);
            return 0;
        }

        int pop(lua_State *L)
        {
            scene::Scene *s = (scene::Scene *)lua_touserdata(L, -1);
            s->indicate_pop();
            return 0;
        }
    }
};
