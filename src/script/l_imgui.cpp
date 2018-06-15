#include "l_imgui.h"

#define INPUT_BUFF_SIZE 64

namespace lua {
    namespace l_imgui {
        void add(lua_State *L) {
            LUALIB(lib) = {
                { "start", begin },
                { "stop", end },
                { "button", button },
                { "checkbox", checkbox },
                { "progressbar", progressbar },
                { "text", text },
                { "input_text", input_text },
                { "input_int", input_int },
                { "input_float", input_float },
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

        int text(lua_State *L) {
            auto s = lua::get_string(L, -1);
            ImGui::TextUnformatted(s.c_str());
            return 0;
        }

        int input_text(lua_State *L) {
            char input[INPUT_BUFF_SIZE];
            auto label = lua::get_string(L, -2);
            auto s = lua::get_string(L, -1);
            strncpy(input, s.c_str(), s.size());
            ImGui::InputText(label.c_str(), input, INPUT_BUFF_SIZE);
            lua_pushstring(L, input);
            return 1;
        }

        int input_int(lua_State *L) {
            auto label = lua::get_string(L, -2);
            auto i = (int)lua::get_num(L, -1);
            ImGui::InputInt(label.c_str(), &i);
            lua_pushnumber(L, i);
            return 1;
        }

        int input_float(lua_State *L) {
            auto label = lua::get_string(L, -2);
            auto f = lua::get_num(L, -1);
            ImGui::InputFloat(label.c_str(), &f);
            lua_pushnumber(L, f);
            return 1;
        }
    };
};
