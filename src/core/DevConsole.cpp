#include "DevConsole.h"

#define MAX_BUFFER_SIZE 512
#define MAX_LINES 20

void DevConsole::write(std::string content)
{
    buffer.push_back(content);
    if (buffer.size() > MAX_LINES) {
        buffer.pop_front();
    }
}

void DevConsole::imgui_draw()
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
    ImGui::InputTextMultiline("", buff, idx);
    ImGui::End();
}
