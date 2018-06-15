#ifndef SCRIPT_CONTAINER_H
#define SCRIPT_CONTAINER_H

#include <vector>

namespace lua {
    template<class T>
    class Container {
    public:
        Container() = default;
        ~Container();

        void add(T *item);
        void remove(T *item);
    private:
        std::vector<T*> items;
    };

    template<class T>
    Container<T>::~Container()
    {
        for (const auto &i : items) {
            delete i;
        }
    }

    template<class T>
    void Container<T>::add(T *item)
    {
        items.push_back(item);
    }

    template<class T>
    void Container<T>::remove(T *item)
    {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i] == item) {
                items[i] = items[items.size() - 1];
                items.pop_back();
            }
        }
    }
};

#endif // SCRIPT_CONTAINER_H
