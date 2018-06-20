#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <fstream>

#include "core.h"
#include "script.h"
#include "render.h"

#include "Actor.h"
#include "ActorManager.h"
#include "WorldGenerator.h"

namespace play {
    class World
    {
    public:
        enum state {
            playing = 0,
            change
        };
        World(std::string tile_set, std::unique_ptr<WorldGenerator> &&gen);
        ~World();

        void set_tile(render::Tile *tile, int layer, sf::Vector2i pos); 
        void remove_tile(int layer, sf::Vector2i pos);

        void set_init_player_pos(sf::Vector2i pos);

        void add_actor(std::string name, sf::Vector2i pos);
        void add_collision(int type, sf::Vector2i pos);

        void save();
        void set_size(sf::Vector2i size);
        sf::Vector2i get_size();
        std::string get_tileset();
        std::string get_script_name();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void render(sf::RenderWindow &window);
        void render_layer(sf::RenderWindow &window, int layer);
        void render_actors(sf::RenderWindow &window);

        void set_edit_mode(bool edit_mode);

        void request_level_load(std::string name, sf::Vector2i player_pos);

        state status();
        std::string next_level();
        sf::Vector2i next_player_pos();

        ActorManager::actor_ptr get_camera_target();
        ActorManager *get_actorman();
    private:
        void add_layer(int num_layers = 1);
        std::string convert_collision_boxes();

        bool update_actors =  true;
        static constexpr int world_height = 20;
        static constexpr int world_width = 20;
        std::unique_ptr<render::TileSet> tile_set;
        std::string name;
        std::string filename;
        std::string tileset;
        std::shared_ptr<ActorManager> actor_man;
        Dimension::Room world;

        state game_state = playing;
        std::string request_level = "";
        sf::Vector2i load_player_pos = sf::Vector2i(0, 0);

        sf::Vector2i size;

        std::string script_name;
        lua::Script *s = nullptr;
    };
};


#endif //WORLD_H