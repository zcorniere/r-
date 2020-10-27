#ifndef COMPONENT_STORAGE_HPP
#define COMPONENT_STORAGE_HPP

#include <any>
#include <unordered_map>
#include <string>
#include <vector>
#include <initializer_list>
#include <iostream>

class ComponentStorage {
private:
    std::unordered_multimap<std::string, std::any> m_storage;
public:
    ComponentStorage();
    template<typename T>
    void registerComponent(T &sample)
    {
        std::vector<T> new_row;

        m_storage.emplace(typeid(T).name(), std::move(new_row));
    }
    ~ComponentStorage();
};

#endif
