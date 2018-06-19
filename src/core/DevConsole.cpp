#include "DevConsole.h"

#define MAX_BUFFER_SIZE 1024
#define MAX_LINES 40

namespace core {
    void DevConsole::write(std::string content)
    {
        buffer.push_back(content);
        if (buffer.size() > MAX_LINES) {
            buffer.pop_front();
        }
    }

    void DevConsole::imgui_draw(sf::Vector2i size)
    {
        char buff[MAX_BUFFER_SIZE];
        int idx = 0;
        for (auto i = buffer.rbegin(); i != buffer.rend(); ++i) {
            if (i->size() + idx >= MAX_BUFFER_SIZE) {
                break;
            }
            strncpy(&buff[idx], i->c_str(), i->size());
            idx += i->size();
            buff[idx++] = '\n';
        }
        buff[idx+1] = '\0';
        ImGui::Begin("Dev Console:");
        ImGui::InputTextMultiline("", buff, idx, ImVec2(size.x, size.y/3));
        ImGui::End();
    }
};
