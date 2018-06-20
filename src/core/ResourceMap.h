#ifndef RESOURCE_MAP_H
#define RESOURCE_MAP_H

#include <string>
#include <map>

namespace core {

    template <class T, T(* instance)(std::string)>
    class ResourceMap
    {
    public:
        ResourceMap() = delete;

        static T *request(std::string file_name);
        static void clear();
    private:
        static std::map<std::string, T> vals;
    };

    template <class T, T(* instance)(std::string)>
    std::map<std::string, T> ResourceMap<T, instance>::vals;

    template <class T, T(* instance)(std::string)>
    T *ResourceMap<T, instance>::request(std::string file_name)
    {
        if (vals.find(file_name) == vals.end()) {
            T tmp = instance(file_name);
            vals[file_name] = tmp;
        }
        return &vals[file_name];
    }

    template <class T, T(* instance)(std::string)>
    void ResourceMap<T, instance>::clear()
    {
        vals.clear();
    }

};

#endif // RESOURCE_MAP_H
