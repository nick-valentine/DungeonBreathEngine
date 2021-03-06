#ifndef STATS_H
#define STATS_H

#define STATS_KEEP_FRAMES 30

#include <SFML/Graphics.hpp>
#include "imgui.h"

namespace core {
    class Stats
    {
    public:
        Stats() = default;

        void push_delta(int delta);
        void push_update(int delta);
        void push_draw(int delta);

        void imgui_draw(sf::Vector2i size);
    private:
        float frame_deltas[STATS_KEEP_FRAMES];
        int delta_idx = 0;

        float update_deltas[STATS_KEEP_FRAMES];
        int update_idx = 0;

        float draw_deltas[STATS_KEEP_FRAMES];
        int draw_idx = 0;
    };
};

#endif //STATS_H
