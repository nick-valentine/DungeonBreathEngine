#include "l_scene.h"

namespace lua {
    namespace l_scene {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                { "push", push },
                { "pop", pop },
                { NULL, NULL },
            };

            lua::add_lib(L, "scene", lib);
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
