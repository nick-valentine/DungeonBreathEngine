#include "l_imgui.h"

namespace lua {
    namespace l_imgui {
        void add(lua_State *L) {
            LUALIB(lib) = {
                { "start", begin },
                { "stop", end },
                { "button", button },
                { "checkbox", checkbox },
                { "progressbar", progressbar},
                { NULL, NULL},
            };
            lua::add_lib(L, "imgui", lib);
        }

        int begin(lua_State *L) {
            auto s = lua::get_string(L, -1);
            ImGui::Begin(s.c_str());
            return 0;
        }

        int end(lua_State *L) {
            ImGui::End();
            return 0;
        }

        int button(lua_State *L) {
            auto l = lua::get_string(L, -1);
            auto p = ImGui::Button(l.c_str());
            lua_pushnumber(L, p);
            return 1;
        }

        int checkbox(lua_State *L) {
            auto l = lua::get_string(L, -2);
            auto checked = (bool) lua::get_num(L, -1);
            ImGui::Checkbox(l.c_str(), &checked);
            lua_pushnumber(L, checked);
            return 1;
        }

        int progressbar(lua_State *L) {
            auto f = lua::get_num(L, -1);
            ImGui::ProgressBar(f);
            return 0;
        }
    };
};
