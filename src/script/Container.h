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

        size_t size() const;
        T *get(int i);
    private:
        std::vector<T*> items;
    };

    template<class T>
    Container<T>::~Container()
    {
        for (auto &i : items) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        }
        items.clear();
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
                delete items[i];
                items[i] = items[items.size() - 1];
                items.pop_back();
            }
        }
    }

    template<class T>
    size_t Container<T>::size() const
    {
        return items.size();
    }

    template<class T>
    T *Container<T>::get(int i)
    {
        return items[i];
    }
};

#endif // SCRIPT_CONTAINER_H
