#include "l_play.h"
#include "play.h"

namespace lua {
    namespace world {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                { "change_level", change_level },
                { "get_actorman", get_actorman },
                { "draw", draw },
                { "draw_layer", draw_layer },
                { "draw_actors", draw_actors },
                { "set_edit_mode", set_edit_mode },
                { "save_edits", save_edits },
                { "add_actor", add_actor },
                { "add_collision", add_collision },
                { "set_tile", set_tile },
                { "remove_tile", remove_tile },
                { "get_size", get_size },
                { "get_tileset", get_tileset },
                { "get_script_name", get_script_name },
                { NULL, NULL}
            };
            lua::add_lib(L, "world", lib);
        }

        int change_level(lua_State *L) {
            play::World *w = (play::World *)lua::get_lightuserdata(L, -3);
            auto name = lua::get_string(L, -2);
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            core::app_container.get_logger()->info("requesting level load");

            w->request_level_load(name, sf::Vector2i(x, y));

            return 0;
        }

        int get_actorman(lua_State *L) {
            play::World *w = (play::World *)lua::get_lightuserdata(L, -1);
            auto a = w->get_actorman();
            lua_pushlightuserdata(L, a);
            return 1;
        }

        int draw(lua_State *L) {
            auto w = (play::World *)lua::get_lightuserdata(L, -2);
            auto win = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
            w->render(*win);
            return 0;
        }

        int draw_layer(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -3);
            auto win = (sf::RenderWindow *)lua::get_lightuserdata(L, -2);
            auto l = (int) lua::get_num(L, -1);
            w->render_layer(*win, l);
            return 0;
        }

        int draw_actors(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -2);
            auto win = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
            w->render_actors(*win);
            return 0;
        }

        int set_edit_mode(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -2);
            auto e = (int) lua::get_num(L, -1);
            w->set_edit_mode(e);
            return 0;
        }

        int save_edits(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -1);
            w->save();
            return 0;
        }

        int add_actor(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -3);
            auto n = lua::get_string(L, -2);
            auto p = lua::get_vec(L, -1);
            sf::Vector2i pos(p.x, p.y);
            w->add_actor(n, pos);
            return 0;
        }

        int add_collision(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -3);
            auto t = (int) lua::get_num(L, -2);
            auto p = lua::get_vec(L, -1);
            sf::Vector2i pos(p.x, p.y);
            w->add_collision(t, pos);
            return 0;
        }

        int set_tile(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -4);
            auto t = (render::Tile *)lua::get_lightuserdata(L, -3);
            auto l = (int) lua::get_num(L, -2);
            auto p = lua::get_vec(L, -1);
            sf::Vector2i pos(p.x, p.y);
            w->set_tile(t, l, pos);
            return 0;
        }

        int remove_tile(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -3);
            auto l = (int) lua::get_num(L, -2);
            auto p = lua::get_vec(L, -1);
            sf::Vector2i pos(p.x, p.y);
            w->remove_tile(l, pos);
            return 0;
        }

        int get_size(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -1);
            auto s = w->get_size();
            sf::Vector2f sf(s.x, s.y);
            lua::put_vec(L, sf);
            return 1;
        }

        int get_tileset(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -1);
            auto t = w->get_tileset();
            lua_pushstring(L, t.c_str());
            return 1;
        }

        int get_script_name(lua_State *L)
        {
            auto w = (play::World *)lua::get_lightuserdata(L, -1);
            auto s = w->get_script_name();
            lua_pushstring(L, s.c_str());
            return 1;
        }
    };

    namespace actor {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                { "get_rect", get_rect },
                { "set_scale", set_scale },
                { "set_origin", set_origin },
                { "set_collision_bounds", set_collision_bounds },
                { "get_velocity", get_velocity },
                { "set_velocity", set_velocity },
                { "set_tileset", set_tileset },
                { "pause_anim", pause_anim },
                { "play_anim", play_anim },
                { "reset_anim", reset_anim },
                { "draw", draw },
                { "attack", attack },
                { NULL, NULL }
            };
            lua::add_lib(L, "actor", lib);
        }

        int get_rect(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -1);
            sf::FloatRect rect;
            if (a != nullptr) {
                rect = a->get_rect();
            }
            lua::put_rect(L, rect);
            return 1;
        }

        int set_scale(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -2);
            if (a == nullptr) {
                return 0;
            }
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            a->set_scale(sf::Vector2f(x, y));
            return 0;
        }

        int set_origin(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -2);
            if (a == nullptr) {
                return 0;
            }
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            a->set_origin(sf::Vector2f(x, y));
            return 0;
        }

        int set_collision_bounds(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -2);
            if (a == nullptr) {
                return 0;
            }
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            auto rect = a->get_rect();
            rect.width = x;
            rect.height = y;
            a->set_rect(rect);
            return 0;
        }

        int get_velocity(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -1);
            sf::Vector2f vel;
            if (a != nullptr) {
                vel = a->get_velocity();
            }
            lua_newtable(L);
            auto table = lua_gettop(L);
            lua_pushnumber(L, vel.x);
            lua_setfield(L, table, "x");
            lua_pushnumber(L, vel.y);
            lua_setfield(L, table, "y");
            return 1;
        }

        int set_velocity(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -2);
            if (a == nullptr) {
                return 0;
            }
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            a->set_velocity(sf::Vector2f(x, y));
            return 0;
        }

        int set_tileset(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -2);
            if (a == nullptr) {
                return 0;
            }
            auto i = (int) lua::get_num(L, -1);
            a->set_tileset(i);
            return 0;
        }

        int pause_anim(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -1);
            if (a == nullptr) {
                return 0;
            }
            a->get_tile()->pause();
            return 0;
        }

        int play_anim(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -1);
            if (a == nullptr) {
                return 0;
            }
            a->get_tile()->play();
            return 0;
        }

        int reset_anim(lua_State *L)
        {
            play::Actor *a = (play::Actor *)lua::get_lightuserdata(L, -1);
            if (a == nullptr) {
                return 0;
            }
            a->get_tile()->reset();
            return 0;
        }

        int draw(lua_State *L)
        {
            auto a = (play::Actor *)lua::get_lightuserdata(L, -2);
            auto w = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
            a->render(*w);
            return 0;
        }

        int attack(lua_State *L)
        {
            auto t = lua_gettop(L);
            auto a = (play::Actor *)lua::get_lightuserdata(L, -2);
            auto dmg = (int) lua::get_num_field(L, -1, "raw_damage");
            lua_pushstring(L, "force");
            lua_gettable(L, t);
            auto force = lua::get_vec(L, -1);
            lua_settop(L, t);
            lua_pushstring(L, "attacker");
            lua_gettable(L, t);
            auto attacker = (play::Actor *)lua::get_lightuserdata(L, -1);
            a->hurt(play::pain{dmg, force, attacker});
            return 0;
        }
    };

    namespace actorman {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                { "spawn", spawn },
                { "remove", remove },
                { "get", get },
                { "clear", clear },
                { "set_camera_target", set_camera_target },
                { "get_camera_target", get_camera_target },
                { "set_player", set_player },
                { "get_player", get_player },
                { NULL, NULL }
            };
            lua::add_lib(L, "actor_manager", lib);
        }

        int spawn(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -3);
            std::string name = lua_tostring(L, -2);
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            auto h = a->spawn(name, sf::Vector2i(x, y));
            lua_pushnumber(L, h);
            return 1;
        }

        int remove(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -2);
            if (!lua_isnumber(L, -1)) {
                lua::error(L, "param 1 not number");
            }
            auto h = (int) lua::get_num(L, -1);
            a->remove(h);
            return 0;
        }

        int get(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -2);
            auto h = (int) lua::get_num(L, -1);
            auto a_ptr = a->get(h);
            lua_pushlightuserdata(L, a_ptr.get());
            return 1;
        }

        int clear(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -1);
            a->clear();
            return 0;
        }

        int set_camera_target(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -2);
            auto h = (int)lua::get_num(L, -1);
            a->set_camera_target(h);
            core::app_container.get_logger()->info("setting camera target %i", h);
            return 0;
        }

        int get_camera_target(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -1);
            auto t = a->get_camera_target();
            lua_pushlightuserdata(L, t.get());
            return 1;
        }

        int set_player(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -2);
            auto i = (int)lua::get_num(L, -1);
            core::app_container.get_logger()->info("setting player %i", i);
            a->set_player(i);
            return 0;
        }

        int get_player(lua_State *L)
        {
            auto a = (play::ActorManager *)lua::get_lightuserdata(L, -1);
            if (a == nullptr) {
                core::app_container.get_logger()->debug("get_player called with null actor_manager");
                lua_pushlightuserdata(L, nullptr);
            } else {
                auto p = a->get_player();
                lua_pushlightuserdata(L, p.get());
            }
            return 1;
        }
    };
};
