#include "ActorManager.h"
#include "Actor.h"

namespace play {
    ActorManager::ActorManager()
    {
        // @todo: make this use index instead
        std::fstream ifile(SCRIPTDIR ACTORDIR "index.txt");
        std::string temp;
        ifile >> temp;
        while (ifile.good()) {
            available_actors.push_back(temp);
            ifile >> temp;
        }
        ifile.close();
    }

    void ActorManager::update(int delta)
    {
        for (auto &i : actors) {
            i.second->update(delta);
            this->check_collision(i.second);
            i.second->commit_update(delta);
        }
    }

    void ActorManager::draw(sf::RenderWindow &window)
    {
        for (auto &i : actors) {
            i.second->draw(window);
        }

#if DEBUG
        for (auto &i : collision_boxes) {
            auto x = sf::RectangleShape(sf::Vector2f(i.rect.width, i.rect.height));
            x.setPosition(sf::Vector2f(i.rect.left, i.rect.top));
            x.setFillColor(sf::Color::Transparent);
            x.setOutlineColor(sf::Color::White);
            x.setOutlineThickness(5);

            window.draw(x);

        }
#endif //DEBUG
    }

    int ActorManager::spawn(std::string name, sf::Vector2i pos)
    {
        if (!check_available(name)) {
            throw new play::UnavailableActorException();
        }
        actor_ptr tmp(new Actor(this, max_id, pos, sf::Vector2f(64, 64), name));
        actors[max_id] = tmp;
        actors[max_id]->init();
        max_id++;
        return max_id-1;
    }

    void ActorManager::add_collision_type(int type, std::string action, std::string target, sf::Vector2i loc)
    {
        collision_types[type] = CType{type, action, target, loc};
    }

    void ActorManager::add_collision_rect(int type, sf::FloatRect rect)
    {
        this->collision_boxes.push_back(Collision{type, rect});
    }

    void ActorManager::remove(int handle)
    {
        actors.erase(handle);
    }

    void ActorManager::clear()
    {
        actors.clear();
    }

    void ActorManager::set_init_player_pos(sf::Vector2i pos)
    {
        this->init_player_pos = pos;
        auto p = get_player();
        if (pos.x != 0 && pos.y != 0) {
            p->set_location(sf::Vector2f(pos.x, pos.y));
        }
    }

    sf::Vector2i ActorManager::get_init_player_pos()
    {
        return this->init_player_pos;
    }

    void ActorManager::set_camera_target(int handle)
    {
        this->camera_target = actors[handle];
    }

    ActorManager::actor_ptr ActorManager::get_camera_target()
    {
        return this->camera_target;
    }

    collision_ptr ActorManager::get_event()
    {
        auto x = std::move(this->event);
        this->event.reset(nullptr);
        return std::move(x);
    }

    CType ActorManager::get_collision_type(int type)
    {
        return collision_types[type];
    }

    void ActorManager::set_player(int handle)
    {
        this->player = actors[handle];
    }

    ActorManager::actor_ptr ActorManager::get_player()
    {
        return this->player;
    }

    std::string ActorManager::get_actor_data() const
    {
        std::stringstream ss;
        for (const auto &i : actors) {
            auto rect = i.second->get_rect();
            ss<<i.second->get_name()<<" "<<rect.left<<" "<<rect.top<<"\n";
        }
        return ss.str();
    }

    std::vector<Collision> ActorManager::get_collision_boxes() const
    {
        return this->collision_boxes;
    }

    bool ActorManager::check_available(std::string name)
    {
        for (size_t i = 0; i < available_actors.size(); ++i) {
            core::app_container.get_logger()->info(available_actors[i].c_str());
            if (available_actors[i] == name) {
                return true;
            }
        }
        return false;
    }

    void ActorManager::check_collision(actor_ptr a)
    {
        // @todo: potentially move from O(N^2) op to spatial trees
        auto rect = a->get_rect();
        auto vel = a->get_velocity();
        rect.top += vel.y;
        rect.left += vel.x;
        auto intersection = sf::FloatRect();
        for (const auto &i : collision_boxes) {
            if (i.rect.intersects(rect, intersection)) {
                if (i.type == 1) {
                    resolve_collision(rect, i.rect, intersection);
                } else {
                    trigger_event(a, i, intersection);
                }
            }
        }
        for (const auto &i : actors) {
            if (i.second == a) {
                // note: intentionally comparing addresses here
                // don't collide with self
                continue;
            }
            auto other = i.second->get_rect();
            if (other.intersects(rect, intersection)) {
                resolve_collision(rect, other, intersection);
            }
        }
        a->set_rect(rect);
    }

    void ActorManager::resolve_collision(sf::FloatRect &a_rect, const sf::FloatRect &with, const sf::FloatRect &intersect)
    {
        if (intersect.height < intersect.width) {
            // resolve y intersection
            if (a_rect.top < with.top) {
                // actor on top, move up
                a_rect.top -= intersect.height;
            } else {
                // otherwise move down
                a_rect.top += intersect.height;
            }
        } else {
            // resolve x intersection
            if (a_rect.left < with.left) {
                // actor on left, move left
                a_rect.left -= intersect.width;
            } else {
                // otherwise move right
                a_rect.left += intersect.width;
            }
        }
    }

    inline void ActorManager::trigger_event(actor_ptr a, Collision c, const sf::FloatRect &intersect)
    {
        this->event = collision_ptr(new Collision{
            type: c.type,
            rect: intersect,
            collider: a
        });
    }
};

