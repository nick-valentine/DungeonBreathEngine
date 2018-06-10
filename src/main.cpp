#include <SFML/Graphics.hpp>

#include <stack>
#include <memory>

#include "core.h"
#include "scene.h"

// Global container instance
core::Container core::app_container;

void handleEvents(sf::RenderWindow &window);

typedef std::unique_ptr<Scene> StackItem;
typedef std::stack<StackItem> GameStack;

int main()
{
    core::ConfigLoader::load();
    std::string lang = core::ConfigLoader::get_string_option("language", "eng");
    core::StringProvider::load(lang);

    core::app_container.init();
    core::Script s("main.lua");
    s.call();

    int resolution_x = core::ConfigLoader::get_int_option("resolution_x", 200);
    int resolution_y = core::ConfigLoader::get_int_option("resolution_y", 200);

    core::app_container.get_logger()->info("resolution: %d, %d", resolution_x, resolution_y);

    const int frame_frequency = 33333; // 1/30 of a second

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "DungeonBreath");

    GameStack stack;
    stack.push(StackItem(new MainMenuScene(sf::Vector2i(resolution_x, resolution_y))));
    sf::Clock timer;

    int delta = 0;
    while (window.isOpen()) {

        delta = int(timer.restart().asMicroseconds());
        sf::sleep(sf::microseconds(sf::Int64(std::max(frame_frequency - float(delta), 0.0f))));

        handleEvents(window);
        stack.top()->update(delta, window);

        window.clear(sf::Color::Black);
        stack.top()->draw(window);
        window.display();

        Scene::Status state = stack.top()->status();
        if (state == Scene::Status::exit_program) {
            break;
        } else if (state == Scene::Status::push_scene) {
            Scene *next = stack.top()->new_scene();
            stack.top()->reset_status();
            stack.push(StackItem(next));
        } else if (state == Scene::Status::pop_scene) {
            stack.pop();
            if (stack.empty()) {
                break;
            }
        }
    }
    return 0;
}

void handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
