#ifndef COMPONENT_STORAGE_HPP
#define COMPONENT_STORAGE_HPP

#include "Snitch.hpp"

#include <any>
#include <map>
#include <memory>
#include <string>
#include <optional>
#include <tuple>
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
        std::map<unsigned, T> new_row;

        m_storage.emplace(typeid(T), std::move(new_row));
    }
    template<typename T>
    std::map<unsigned, T> getComponents()
    {
        for (auto &[storage_type, storage] : m_storage) {
            if (storage_type == typeid(T)) {
                return std::any_cast<std::map<unsigned, T>>(storage);
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
                std::map<unsigned, T> &map = std::any_cast<std::map<unsigned, T>&>(storage);
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

template<typename T1, typename T2>
std::map<unsigned, std::tuple<T1&, T2&>> join_components
(std::map<unsigned, T1>& map1, std::map<unsigned, T2>& map2)
{
    std::map<unsigned, std::tuple<T1&, T2&>> output;

    auto i1 = map1.begin();
    auto i2 = map2.begin();

    while (i1 != map1.end() && i2 != map2.end()) {
        if (i1->first > i2->first) {
            i2++;
            continue;
        } else if (i1->first < i2->first) {
            i1++;
            continue;
        }
        output.emplace(i1->first, std::tuple<T1&, T2&>{i1->second, i2->second});
        i1++;
        i2++;
    }
    return output;
}

/*template<typename... Ts>
std::map<unsigned, std::tuple<Ts...>> join_components
(std::map<unsigned, Ts...> maps...)
{

}*/

#endif

