#include "Stats.h"

namespace core {
    void Stats::push_delta(int delta)
    {
        delta_idx++;
        delta_idx %= STATS_KEEP_FRAMES;
        frame_deltas[delta_idx] = delta;
    }

    void Stats::push_update(int delta)
    {
        update_idx++;
        update_idx %= STATS_KEEP_FRAMES;
        update_deltas[update_idx] = delta;
    }

    void Stats::push_draw(int delta)
    {
        draw_idx++;
        draw_idx %= STATS_KEEP_FRAMES;
        draw_deltas[draw_idx] = delta;
    }

    void Stats::imgui_draw(sf::Vector2i size)
    {
        ImGui::Begin("Stats:");
        ImGui::Text("FPS: %f", 1e6/frame_deltas[delta_idx]);
        ImGui::Text("Update time: %f", update_deltas[update_idx]);
        ImGui::Text("Draw time: %f", draw_deltas[draw_idx]);
        ImGui::PlotHistogram("frames: ", frame_deltas, STATS_KEEP_FRAMES);
        ImGui::PlotHistogram("updates: ", update_deltas, STATS_KEEP_FRAMES);
        ImGui::PlotHistogram("draws: ", draw_deltas, STATS_KEEP_FRAMES);
        ImGui::End();
    }
}
