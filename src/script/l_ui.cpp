#include "l_ui.h"

void lua::l_ui::add(lua_State *L)
{
    LUALIB(lib) = {
        { "set_current", menu::set_current },
        { NULL, NULL },
    };

    lua::add_lib(L, "menu", lib);
}

namespace lua {
    namespace l_ui {
        namespace menu {
            int set_current(lua_State *L) {
                return 0;
            }
        };
    };

};
