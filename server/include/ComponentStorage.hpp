#ifndef COMPONENT_STORAGE_HPP
#define COMPONENT_STORAGE_HPP

#include "Snitch.hpp"

#include <any>
#include <unordered_map>
#include <memory>
#include <string>
#include <optional>
#include <vector>
#include <functional>
#include <typeindex>

class ComponentStorage {
class EntityBuilder;
private:
    std::unordered_map<std::type_index, std::any> m_storage;
    unsigned m_entityCount;

public:
    ComponentStorage();
    template<typename T>
    void registerComponent()
    {
        std::unordered_map<unsigned, T> new_row;

        m_storage.emplace(typeid(T), std::move(new_row));
    }
    template<typename T>
    std::unordered_map<unsigned, T> getComponents()
    {
        for (auto &[storage_type, storage] : m_storage) {
            if (storage_type == typeid(T)) {
                return std::any_cast<std::unordered_map<unsigned, T>>(storage);
            }
        }
        Snitch::warn() << "Trying to find unregistered components '" << typeid(T).name() << "'" << Snitch::endl;
        return {};
    }
    EntityBuilder buildEntity();
    ~ComponentStorage();

private:
    template<typename T>
    void storeComponent(T componenent, unsigned index)
    {
        for (auto &[storage_type, storage] : m_storage) {
            if (storage_type == typeid(T)) {
                std::unordered_map<unsigned, T> &map = std::any_cast<std::unordered_map<unsigned, T>&>(storage);
                map.emplace(index, componenent);
                return;
            }
        }
        Snitch::warn() << "Couldn't store unregistered component '" << typeid(T).name() << "'" << Snitch::endl;;
    }
    unsigned getNextFreeId() const;


private:

    friend EntityBuilder;
    class EntityBuilder {
    private:
        unsigned m_id;
        ComponentStorage &m_dest;
    public:
        EntityBuilder(ComponentStorage &dest);
        EntityBuilder(EntityBuilder &other);
        template<typename T>
        EntityBuilder &withComponent(T component)
        {
            m_dest.storeComponent<T>(component, m_id);
            return *this;
        }
        unsigned build();
        unsigned buildAsOrphan();
    };
};

#endif
