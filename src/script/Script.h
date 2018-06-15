#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

#include "Macros.h"
#include "core.h"
#include "lua.h"
#include "l_core.h"
#include "l_imgui.h"
#include "l_ui.h"
#include "l_scene.h"
#include "l_audio.h"
#include "l_play.h"

namespace lua {
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

