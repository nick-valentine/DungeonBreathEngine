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
                { "image_button", image_button },
                { "listbox", listbox},
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
            strncpy(input, s.c_str(), s.size()+1);
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

        int image_button(lua_State *L) {
            auto spr = (sf::Sprite *)lua::get_lightuserdata(L, -1);
            auto b = ImGui::ImageButton(*spr, sf::Vector2f(40, 40));
            lua_pushnumber(L, b);
            return 1;
        }

        int listbox(lua_State *L) {
            auto label = lua::get_string(L, -3);
            auto current = (int)lua::get_num(L, -2);
            auto items = lua::get_string_array(L, -1);
            char **items_c = new char*[items.size()];
            for (size_t i = 0; i < items.size(); ++i) {
                items_c[i] = new char[INPUT_BUFF_SIZE];
                strncpy(items_c[i], items[i].c_str(), items[i].size());
            }
            ImGui::ListBox(label.c_str(), &current, items_c, items.size());
            for (int i = 0; i < items.size(); ++i) {
                delete items_c[i];
            }
            delete items_c;
            lua_pushnumber(L, current);
            return 1;
        }
    };
};
