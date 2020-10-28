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
        std::vector<T> new_row;

        m_storage.emplace(typeid(T), std::move(new_row));
    }
    EntityBuilder buildEntity();
    ~ComponentStorage();

private:
    template<typename T>
    void storeComponent(std::type_index type, T componenent, unsigned index)
    {
        for (auto &[storage_type, storage] : m_storage) {
            if (storage_type == type) {
                auto vector = std::any_cast<std::vector<T>>(storage);
                vector.insert(vector.begin() + index, componenent);
                return;
            }
        }
        Snitch::warn() << "Couldn't store unregistered componenent '" << typeid(T).name() << "'" << Snitch::endl;;
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
            m_dest.storeComponent<T>(typeid(T), component, m_id);
            return *this;
        }
        unsigned build();
        unsigned buildAsOrphan();
    };
};

#endif
