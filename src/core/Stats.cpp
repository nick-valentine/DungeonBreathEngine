#include "Stats.h"

namespace core {
    void Stats::push_delta(int delta)
    {
        delta_idx++;
        delta_idx %= STATS_KEEP_FRAMES;
        frame_deltas[delta_idx] = delta;
    }

    void Stats::imgui_draw(sf::Vector2i size)
    {
        ImGui::Begin("Stats:");
        ImGui::Text("FPS: %f", 1e6/frame_deltas[delta_idx]);
        ImGui::PlotHistogram("frames: ", frame_deltas, STATS_KEEP_FRAMES);
        ImGui::End();
    }
}
