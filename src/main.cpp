#include <SFML/Graphics.hpp>

#include <stack>
#include <memory>

#include "core.h"
#include "play.h"
#include "script.h"
#include "audio.h"

#include "imgui.h"
#include "imgui-SFML.h"

// Global container instance
core::Container core::app_container;

void handleEvents(sf::RenderWindow &window);

typedef std::unique_ptr<play::Scene> StackItem;
typedef std::stack<StackItem> GameStack;

int main()
{
    auto stats = core::Stats();
    auto console_open = false;
    bool last_tilde_pressed = false;

	audio::MusicManager::init();

    core::ConfigLoader::load();
    std::string lang = core::ConfigLoader::get_string_option("language", "eng");
    core::StringProvider::load(lang);

    core::app_container.init();

    int resolution_x = core::ConfigLoader::get_int_option("resolution_x", 200);
    int resolution_y = core::ConfigLoader::get_int_option("resolution_y", 200);

    core::app_container.get_logger()->info("resolution: %d, %d", resolution_x, resolution_y);

    const int frame_frequency = 33333; // 1/30 of a second

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "DungeonBreath");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    GameStack stack;
    stack.push(StackItem(new play::Scene("entry", sf::Vector2i(resolution_x, resolution_y))));
    stack.top()->wakeup("");
    sf::Clock timer;
    sf::Clock update_timer;
    sf::Clock draw_timer;

    int delta = 0;
    while (window.isOpen()) {

        auto sfml_delta = timer.restart();
        delta = int(sfml_delta.asMicroseconds());
        stats.push_delta(delta);

        update_timer.restart();
        handleEvents(window);
        ImGui::SFML::Update(window, sfml_delta);
        stack.top()->update(delta, window);
        auto update_delta = update_timer.restart();
        delta = int(update_delta.asMicroseconds());
        stats.push_update(delta);

        if (console_open) {
            core::app_container.get_console()->imgui_draw(sf::Vector2i(resolution_x, resolution_y));
            stats.imgui_draw(sf::Vector2i(resolution_x, resolution_y));
        }
        {
            auto tilde_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);
            if (last_tilde_pressed && !tilde_pressed) {
                console_open = !console_open;
            }
            last_tilde_pressed = tilde_pressed;
        }

        draw_timer.restart();
        window.clear(sf::Color::Black);
        stack.top()->draw(window);
        ImGui::SFML::Render(window);
        window.display();
        auto draw_delta = draw_timer.restart();
        delta = int(draw_delta.asMicroseconds());
        stats.push_draw(delta);

        play::Scene::Status state = stack.top()->status();
        if (state == play::Scene::Status::exit_program) {
            break;
        } else if (state == play::Scene::Status::push_scene) {
            play::Scene *next = stack.top()->new_scene();
            stack.top()->reset_status();
            auto m = stack.top()->sleep();
            next->wakeup(m);
            stack.push(StackItem(next));
        } else if (state == play::Scene::Status::pop_scene) {
            auto m = stack.top()->pop();
            stack.pop();
            if (stack.empty()) {
                break;
            }
            stack.top()->wakeup(m);
        }
    }
	audio::MusicManager::close();
    ImGui::SFML::Shutdown();
    return 0;
}

void handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
